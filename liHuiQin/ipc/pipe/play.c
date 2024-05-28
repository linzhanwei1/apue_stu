#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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
        int fd;
        close(pd[1]); // 关闭写端
        dup2(pd[0], 0);
        close(pd[0]);
        fd = open("/dev/null", O_RDWR);
        dup2(fd, 1);
        dup2(fd, 2);
        execl("/usr/bin/mpg123", "mpg123", "-", NULL);
        perror("execl()");
        exit(1);
    }
    else
    {
        // parent write
        close(pd[0]); // 关闭读端
        /* 父进程从网上收数据，往管道中写 */

        close(pd[1]);
        wait(NULL);
        exit(0);
    }
}