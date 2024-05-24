#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include "mytbf.h"

typedef void (*sighandler_t)(int);

static struct mytbf_st *job[MYTBF_MAX];
static int inited;
static struct sigaction alrm_sa_save;

struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
};

void alrm_action(int s, siginfo_t *infop, void *unused)
{
    if (infop->si_code != SI_KERNEL)
        return;
    for (int i = 0; i < MYTBF_MAX; i++)
    {
        if (job[i] != NULL)
        {
            job[i]->token += job[i]->cps;
            if (job[i]->token > job[i]->burst)
                job[i]->token = job[i]->burst;
        }
    }
}

static void module_unload(void)
{
    struct sigaction sa;
    struct itimerval itv;

    sigaction(SIGALRM, &alrm_sa_save, NULL); // 回复信号相关配置

    itv.it_interval.tv_sec = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &itv, NULL);

    for (int i = 0; i < MYTBF_MAX; i++)
        free(job[i]);
}

static void module_load(void)
{
    struct sigaction sa;
    struct itimerval itv;

    sa.sa_sigaction = alrm_action;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO; // 使用三参回调函数指针
    sigaction(SIGALRM, &sa, &alrm_sa_save);
    /* if error */

    itv.it_interval.tv_sec = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &itv, NULL);
    /* if error */

    atexit(module_unload); // 钩子函数卸载模块
}

static int get_free_pos(void)
{
    for (int i = 0; i < MYTBF_MAX; i++)
    {
        if (job[i] == NULL)
            return i;
    }

    return -1;
}

static int min(int a, int b)
{
    return ((a < b) ? a : b);
}

mytbf_t *mytbf_init(int cps, int burst)
{
    struct mytbf_st *me;
    int pos = -1;

    if (!inited)
    {
        module_load();
        inited = 1;
    }

    if ((pos = get_free_pos()) < 0)
        return NULL;

    me = malloc(sizeof(*me));
    if (me == NULL)
        return NULL;

    me->token = 0;
    me->cps = cps;
    me->burst = burst;
    me->pos = pos;

    job[pos] = me;

    return me;
}

int mytbf_fetchtoken(mytbf_t *ptr, int size)
{
    struct mytbf_st *me = ptr;
    int n = -1;

    if (size <= 0)
        return -EINVAL;

    while (me->token <= 0)
        pause();

    n = min(me->token, size);
    me->token -= n;
    return n;
}

int mytbf_returntoken(mytbf_t *ptr, int size)
{
    struct mytbf_st *me = ptr;

    if (size <= 0)
        return -EINVAL;

    me->token += size;
    if (me->token > me->burst)
        me->token = me->burst;

    return size;
}

int mytbf_destroy(mytbf_t *ptr)
{
    struct mytbf_st *me = ptr;

    job[me->pos] = NULL;
    free(ptr);
}