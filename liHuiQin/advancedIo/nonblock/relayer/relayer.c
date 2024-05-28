#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#include "relayer.h"

#define BUFSIZE 1024

enum
{
    STATE_R = 1, // 读
    STATE_W,     // 写
    STATE_EX,    // 异常
    STATE_T      // 终止
};

struct rel_fsm_st
{
    int state;
    int sfd;
    int dfd;
    int len;
    int pos;
    char *errstr;
    char buf[BUFSIZE];
    int64_t count;
};

struct rel_job_st
{
    int job_state;
    int fd1;
    int fd2;
    struct rel_fsm_st fsm12, fsm21;
    int fd1_save, fd2_save;
    // struct timerval start, end;
};

static struct rel_job_st *rel_job[REL_JOBMAX];
static pthread_mutex_t mut_rel_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

static void fsm_driver(struct rel_fsm_st *fsm)
{
    int ret;

    switch (fsm->state)
    {
    case STATE_R:
        fsm->len = read(fsm->sfd, fsm->buf, BUFSIZE);
        if (fsm->len == 0)
            fsm->state = STATE_T;
        else if (fsm->len < 0)
        {
            if (errno == EAGAIN)
                fsm->state = STATE_R;
            else
            {
                fsm->errstr = "read()";
                fsm->state = STATE_EX;
            }
        }
        else
        {
            fsm->pos = 0;
            fsm->state = STATE_W;
        }
        break;
    case STATE_W:
        ret = write(fsm->dfd, fsm->buf + fsm->pos, fsm->len);
        if (ret < 0)
        {
            if (errno == EAGAIN)
                fsm->state = STATE_W;
            else
            {
                fsm->errstr = "write()";
                fsm->state = STATE_EX;
            }
        }
        else
        {
            fsm->pos += ret;
            fsm->len -= ret;
            if (fsm->len == 0)
                fsm->state = STATE_R;
            else
                fsm->state = STATE_W;
        }
        break;
    case STATE_EX:
        perror(fsm->errstr);
        fsm->state = STATE_T;
        break;
    case STATE_T:
        /* do sth 终止 */
        break;
    default:
        abort();
        break;
    }
}

static void *thr_relayer(void *arg)
{

    while (1)
    {
        pthread_mutex_lock(&mut_rel_job);
        for (int i = 0; i < REL_JOBMAX; i++)
        {
            if (rel_job[i] != NULL)
            {
                if (rel_job[i]->job_state == STATE_RUNNING)
                {
                    fsm_driver(&rel_job[i]->fsm12);
                    fsm_driver(&rel_job[i]->fsm21);
                    if (rel_job[i]->fsm12.state == STATE_T && rel_job[i]->fsm21.state == STATE_T)
                    {
                        rel_job[i]->job_state = STATE_OVER;
                    }
                }
            }
        }
        pthread_mutex_unlock(&mut_rel_job);
    }

    pthread_exit(NULL);
}

// module_unload()

static void module_load(void)
{
    pthread_t tid_realyer;
    int err;

    err = pthread_create(&tid_realyer, NULL, thr_relayer, NULL);
    if (err)
    {
        fprintf(stderr, "pthread_create():%s\n", strerror(err));
        exit(1);
    }
}

static int get_free_pos_unlocked(void)
{
    for (int i = 0; i < REL_JOBMAX; i++)
    {
        if (rel_job[i] == NULL)
            return i;
    }

    return -1;
}

int rel_addjob(int fd1, int fd2)
{
    struct rel_job_st *me;
    int pos;

    // 单例
    pthread_once(&init_once, module_load);

    if (!(me = malloc(sizeof(*me))))
    {
        return -ENOMEM;
    }
    me->fd1 = fd1;
    me->fd2 = fd2;
    me->job_state = STATE_RUNNING;

    me->fd1_save = fcntl(me->fd1, F_GETFL);
    fcntl(me->fd1, F_SETFL, me->fd1_save | O_NONBLOCK);
    me->fd2_save = fcntl(me->fd2, F_GETFL);
    fcntl(me->fd2, F_SETFL, me->fd2_save | O_NONBLOCK);

    me->fsm12.sfd = me->fd1;
    me->fsm12.dfd = me->fd2;
    me->fsm12.state = STATE_R;

    me->fsm21.sfd = me->fd2;
    me->fsm21.dfd = me->fd1;
    me->fsm21.state = STATE_R;

    pthread_mutex_lock(&mut_rel_job);
    pos = get_free_pos_unlocked();
    if (pos < 0)
    {
        pthread_mutex_unlock(&mut_rel_job);
        fcntl(me->fd1, F_SETFL, me->fd1_save);
        fcntl(me->fd2, F_SETFL, me->fd2_save);
        free(me);
        return -ENOSPC;
    }
    rel_job[pos] = me;
    pthread_mutex_unlock(&mut_rel_job);

    return pos;
}