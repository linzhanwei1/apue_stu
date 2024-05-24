#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MYRTSIG (SIGRTMIN + 6)

static void mysig_handler(int s)
{
    write(1, "!", 1);
}

int main(int argc, char *argv[])
{
    sigset_t set, oldset, saveset;

    signal(MYRTSIG, mysig_handler);

    sigemptyset(&set);
    sigaddset(&set, MYRTSIG);
    /* 保存现场 */
    sigprocmask(SIG_UNBLOCK, &set, &saveset);
    sigprocmask(SIG_BLOCK, &set, &oldset);
    for (int j = 0; j < 1000; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            write(1, "*", 1);
            sleep(1); // 信号会打断阻塞的系统调用，响应信号后，进程已经参与调度了
        }
        write(1, "\n", 1);
        sigsuspend(&oldset);
    }
    sigprocmask(SIG_SETMASK, &saveset, NULL);

    exit(0);
}