#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mypipe.h"

struct mypipe_st
{
    int head;
    int tail;
    char data[PIPESIZE];
    int datasize;
    int count_rd;
    int count_wr;
    pthread_mutex_t mut;
    pthread_cond_t cond;
};

mypipe_t *mypipe_init(void)
{
    struct mypipe_st *me;

    me = malloc(sizeof(*me));
    if (me == NULL)
        return NULL;

    me->head = 0;
    me->tail = 0;
    me->datasize = 0;
    me->count_rd = 0;
    me->count_wr = 0;
    pthread_mutex_init(&me->mut, NULL);
    pthread_cond_init(&me->cond, NULL);

    return me;
}

int mypipe_register(mypipe_t *ptr, int opmap)
{
    struct mypipe_st *me = ptr;

    pthread_mutex_lock(&me->mut);

    if (opmap & MYPIPE_READ)
        me->count_rd++;
    if (opmap & MYPIPE_WRITE)
        me->count_wr++;

    // 读写双方不全
    while (me->count_rd <= 0 || me->count_wr <= 0)
        pthread_cond_wait(&me->cond, &me->mut);

    pthread_cond_broadcast(&me->cond); // 读写双方凑齐
    pthread_mutex_unlock(&me->mut);

    return 0;
}
int mypipe_unregister(mypipe_t *ptr, int opmap)
{
    struct mypipe_st *me = ptr;

    pthread_mutex_lock(&me->mut);

    if (opmap & MYPIPE_READ)
        me->count_rd--;
    if (opmap & MYPIPE_WRITE)
        me->count_wr--;

    // 唤醒其他管道读写方检查读写者的数量
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);
}

static int mypipe_readbyte_unlocked(struct mypipe_st *me, char *datap)
{
    // 管道无数据
    if (me->datasize <= 0)
        return -1;

    // 管道有数据 读取一个限制管道的读端数据，用data保存
    *datap = me->data[me->head];
    me->head = (me->head++) % PIPESIZE;
    me->datasize--;
    return 0;
}

static int mypipe_writebyte_unlocked(struct mypipe_st *me, const char *datap)
{
    // 管道数据满
    if (me->datasize >= PIPESIZE)
        return -1;

    // 管道有数据， 读取一个限制管道的读端数据，用data保存
    me->data[me->tail + 1] = *datap;
    me->tail = (me->tail++) % PIPESIZE;
    me->datasize++;

    return 0;
}
int mypipe_read(mypipe_t *ptr, void *buf, size_t count)
{
    struct mypipe_st *me = ptr;
    int i;

    pthread_mutex_lock(&me->mut);

    while (me->datasize <= 0 || me->count_wr > 0)
        pthread_cond_wait(&me->cond, &me->mut); // 解锁，在临界区外等待

    // 管道空且没有写者
    if (me->datasize <= 0 && me->count_wr <= 0)
    {
        pthread_mutex_unlock(&me->mut);
        return 0;
    }

    // 管道种有数据了
    for (i = 0; i < count; i++)
    {
        if (mypipe_readbyte_unlocked(me, buf + i) < 0)
            break;
    }
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);

    return i;
}

int mypipe_write(mypipe_t *ptr, const void *buf, size_t size)
{
    struct mypipe_st *me = ptr;

    pthread_mutex_lock(&me->mut);

    while (me->datasize >= PIPESIZE && me->count_rd > 0)
    {
        pthread_cond_wait(&me->cond, &me->mut);
    }

    // 管道空且没有读者
    if (me->datasize <= 0 && me->count_rd <= 0)
    {
        pthread_mutex_unlock(&me->mut);
        return 0;
    }

    // 管道中有空间了
    for (int i = 0; i < size; i++)
    {
        if (mypipe_writebyte_unlocked(me, buf + i) < 0)
        {
            break;
        }
    }

    pthread_mutex_unlock(&me->mut);

    return 0;
}

int mypipe_destroy(mypipe_t *ptr)
{
    struct mypipe_st *me = ptr;

    pthread_mutex_destroy(&me->mut);
    pthread_cond_destroy(&me->cond);
    free(ptr);

    return 0;
}