#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static void *func(void *arg)
{
    puts("Thread is working!");
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t tid;
    int err;

    puts("Begin!");

    if (err = pthread_create(&tid, NULL, func, NULL) != 0)
    {
        fprintf(stderr, "pthread_create():%s\n", strerror(err));
        exit(1);
    }

    pthread_join(tid, NULL);
    puts("End!");
    exit(0);
}