#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    printf("[%d]:Begin!\n", getpid());

    fflush(NULL); // fork()之前，需刷新所有正常打开的流
    pid = fork();
    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }

    if (pid == 0)
    { // child
        printf("[%d]:Child is working!\n", getpid());
    }
    else
    { // parent
        printf("[%d]:Parent is working!\n", getpid());
    }

    printf("[%d]:End!\n", getpid());

    exit(0);
}