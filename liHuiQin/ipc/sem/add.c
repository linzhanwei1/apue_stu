#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define PROCNUM 20
#define FNAME "/tmp/out"
#define LINESIZE 1024

static int semid;

static void p(void)
{
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;
    while (semop(semid, &op, 1) < 0)
    {
        if (errno != EINTR || errno != EAGAIN)
        {
            perror("semop()");
            exit(1);
        }
    }
}
static void v(void)
{
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;
    while (semop(semid, &op, 1) < 0)
    {
        if (errno != EINTR || errno != EAGAIN)
        {
            perror("semop()");
            exit(1);
        }
    }
}

static void func_add(void)
{
    FILE *fp;
    char linebuf[LINESIZE];

    fp = fopen(FNAME, "r+"); // r+必须保证文件存在，又读又写
    if (fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    p();
    fgets(linebuf, LINESIZE, fp);
    rewind(fp);
    sleep(1);
    fprintf(fp, "%d\n", atoi(linebuf) + 1);
    fflush(fp);
    v();

    fclose(fp);
}

int main(int argc, char **argv)
{
    int err;
    pid_t pid;

    /* get key (匿名ipc不需要key) */

    /* get sem */
    semid = semget(IPC_PRIVATE, 1, 0600);
    if (semid < 0)
    {
        perror("semget()");
        exit(1);
    }

    if (semctl(semid, 0, SETVAL, 1) < 0)
    {
        perror("semctl()");
        exit(1);
    }

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
        wait(NULL);

    if (semctl(semid, 0, IPC_RMID) < 0)
    {
        perror("semctl()");
        exit(1);
    }

    exit(0);
}