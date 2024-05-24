#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static void cleanup_func(void *p)
{
    puts(p);
}

static void *func(void *p)
{
    puts("Thread is working!");
    /* 挂钩子函数 */
    pthread_cleanup_push(cleanup_func, "cleanup:1");
    pthread_cleanup_push(cleanup_func, "cleanup:2");
    pthread_cleanup_push(cleanup_func, "cleanup:3");

    puts("push over!");

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);

    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t tid;
    int err;

    puts("Begin!");

    if (err = pthread_create(&tid, NULL, func, NULL))
    {
        fprintf(stderr, "pthread_create():%s\n", strerror(err));
        exit(1);
    }

    pthread_join(tid, NULL);
    puts("End!");

    exit(0);
}