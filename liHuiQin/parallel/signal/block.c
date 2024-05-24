#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void int_handler(int s)
{
    write(1, "!", 1);
}

int main(int argc, char *argv[])
{
    sigset_t set, oldset, saveset;

    signal(SIGINT, int_handler);

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    /* 保存现场 */
    sigprocmask(SIG_UNBLOCK, &set, &saveset);
    for (int j = 0; j < 1000; j++)
    {
        sigprocmask(SIG_BLOCK, &set, NULL); // 不关心旧的信号集
        // sigprocmask(SIG_BLOCK, &set, &oldset); // 关心旧的信号集
        for (int i = 0; i < 5; i++)
        {
            write(1, "*", 1);
            sleep(1); // 信号会打断阻塞的系统调用，响应信号后，进程已经参与调度了
        }
        write(1, "\n", 1);
        sigprocmask(SIG_UNBLOCK, &set, NULL); // 不关心旧的信号集
        // sigprocmask(SIG_SETMASK, &oldset, NULL); // 恢复旧的信号集
    }
    sigprocmask(SIG_SETMASK, &saveset, NULL);

    exit(0);
}