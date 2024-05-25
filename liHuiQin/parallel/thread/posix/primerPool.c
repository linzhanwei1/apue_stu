#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 4

static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_num = PTHREAD_COND_INITIALIZER;

static void *th_prime(void *p)
{
    int i, j, mark;

    while (1)
    {
        pthread_mutex_lock(&mut_num);

        /* 等待下发任务 轮询忙等 */
        while (num == 0)
        {
            /* 轮询忙等 */
            // pthread_mutex_unlock(&mut_num);
            // sched_yield();
            // pthread_mutex_lock(&mut_num);
            pthread_cond_wait(&cond_num, &mut_num);
        }
        if (num == -1)
        {
            pthread_mutex_unlock(&mut_num); // 先解锁再退出
            break;
        }
        i = num;
        num = 0;

        pthread_cond_broadcast(&cond_num);
        pthread_mutex_unlock(&mut_num);

        mark = 1;
        for (j = 2; j < i / 2; j++)
        {
            if (i % j == 0)
            {
                mark = 0;
                break;
            }
        }
        if (mark)
            printf("[%d]%d is a primer\n", (int)p, i);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t tid[THRNUM];
    int err;

    for (int i = 0; i < THRNUM; i++)
    {
        err = pthread_create(tid + i, NULL, th_prime, (void *)i);
        if (err)
        {
            fprintf(stderr, "pthread_create:%s", strerror(err));
            exit(1);
        }
    }

    for (int i = LEFT; i <= RIGHT; i++)
    {
        pthread_mutex_lock(&mut_num);

        while (num != 0)
        {
            /* 轮询忙等 */
            // pthread_mutex_unlock(&mut_num);
            // sched_yield(); // 让出CPU
            // pthread_mutex_lock(&mut_num);

            /* 通知 */
            pthread_cond_wait(&cond_num, &mut_num);
        }
        num = i;
        pthread_cond_signal(&cond_num);
        pthread_mutex_unlock(&mut_num);
    }

    pthread_mutex_lock(&mut_num); // 确保最后一个任务被取走了
    while (num != 0)
    {
        /* 轮询忙等 */
        // pthread_mutex_unlock(&mut_num);
        // sched_yield(); // 让出CPU
        // pthread_mutex_lock(&mut_num);

        /* 通知 */
        pthread_cond_wait(&cond_num, &mut_num);
    }
    num = -1;
    pthread_cond_broadcast(&cond_num);
    pthread_mutex_unlock(&mut_num);

    for (int i = 0; i < THRNUM; i++)
        pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&mut_num);
    pthread_cond_destroy(&cond_num);
    exit(0);
}