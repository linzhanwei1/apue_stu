#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <pthread.h>

#define PROCNUM 20
#define FNAME "/tmp/out"
#define LINESIZE 1024

static void func_add(void)
{
    FILE *fp;
    int fd;
    char linebuf[LINESIZE];

    fp = fopen(FNAME, "r+"); // r+必须保证文件存在，又读又写
    if (fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    fd = fileno(fp);
    lockf(fd, F_LOCK, 0);

    fgets(linebuf, LINESIZE, fp);
    rewind(fp);
    sleep(1);
    fprintf(fp, "%d\n", atoi(linebuf) + 1);
    fflush(fp);
    // fclose(fp); // 避免文件解锁异常问题
    lockf(fd, F_ULOCK, 0);
    fclose(fp);
}

int main(int argc, char **argv)
{
    int err;
    pid_t pid;

    for (int i = 0; i < PROCNUM; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork()");
            exit(1);
        }
        if (pid == 0)
        {
            func_add();
            exit(0);
        }
    }

    for (int i = 0; i < PROCNUM; i++)
    {
        wait(NULL);
    }

    exit(0);
}