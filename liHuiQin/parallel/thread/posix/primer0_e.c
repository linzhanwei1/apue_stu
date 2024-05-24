#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT - LEFT + 1)

struct thr_arg_st
{
    int n;
};

static void *th_prime(void *p)
{
    int i, j, mark;
    i = ((struct thr_arg_st *)p)->n;
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
        printf("%d is a primer\n", i);

    pthread_exit(p);
}

int main(int argc, char **argv)
{
    pthread_t tid[THRNUM];
    int err;
    struct thr_arg_st *p;
    void *ptr;

    for (int i = LEFT; i <= RIGHT; i++)
    {
        if (!(p = malloc(sizeof(*p))))
        {
            perror("malloc()");
            exit(1);
        }
        p->n = i;

        err = pthread_create(tid + (i - LEFT), NULL, th_prime, p);
        if (err)
        {
            fprintf(stderr, "pthread_create:%s", strerror(err));
            exit(1);
        }
    }

    for (int i = LEFT; i <= RIGHT; i++)
    {
        pthread_join(tid[i - LEFT], &ptr);
        free(ptr); // 回收资源
    }

    exit(0);
}