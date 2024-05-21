/* 程序1-8 从标准输入读命令并执行 */
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "ourhdr.h"

void sig_int(int signo)
{
    printf("interrupt\n%%");
}

int main(int argc, char *argv[])
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    /* print prompt (printf requires %% to print %) */
    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        buf[strlen(buf) - 1] = '\0';

        if ((pid = fork()) < 0)
            err_sys("fork error");

        /* child */
        else if (pid == 0)
        {
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%%");
    }

    exit(0);
}