#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "anytimer.h"

static void f1(void *p)
{
    printf("f1():%s\n", (char *)p);
}

static void f2(void *p)
{
    printf("f2():%s\n", (char *)p);
}

int main(int argc, char *argv[])
{
    int job1;

    job1 = at_addjob_repeat(5, f1, "aaa");
    if (job1 < 0)
    {
        fprintf(stderr, "at_addjob():%s\n", strerror(-job1));
    }

#if 0
    int job1, job2, job3;
    puts("Begin!");

    job1 = at_addjob(5, f1, "aaa");
    if (job1 < 0)
    {
        fprintf(stderr, "at_addjob():%s\n", strerror(-job1));
    }
    job2 = at_addjob(2, f2, "bbb");
    if (job2 < 0)
    {
        fprintf(stderr, "at_addjob():%s\n", strerror(-job2));
    }
    job3 = at_addjob(7, f1, "ccc");
    if (job3 < 0)
    {
        fprintf(stderr, "at_addjob():%s\n", strerror(-job3));
    }

    puts("End!");
#endif

    while (1)
    {
        write(STDOUT_FILENO, ".", 1);
        sleep(1);
    }

    exit(0);
}