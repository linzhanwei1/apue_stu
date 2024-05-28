#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define BUFSIZE 1024

int main(int argc, char **argv)
{
    int pd[2];
    pid_t pid;
    char buf[BUFSIZE];
    int len;

    if (pipe(pd) < 0)
    {
        perror("pipe()");
        exit(1);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }

    if (pid == 0) // child read
    {
        close(pd[1]); // 关闭写端
        len = read(pd[0], buf, BUFSIZE);
        write(STDOUT_FILENO, buf, len);
        close(pd[0]);
        exit(0);
    }
    else
    {
        // parent write
        close(pd[0]);
        write(pd[1], "Hello!\n", 7);
        close(pd[1]);
        wait(NULL);
        exit(0);
    }
}