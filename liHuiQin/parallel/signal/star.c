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

    // signal(SIGINT, SIG_IGN); // 忽略中断信号
    signal(SIGINT, int_handler);

    for (int i = 0; i < 10; i++)
    {
        write(1, "*", 1);
        sleep(1); // 信号会打断阻塞的系统调用，响应信号后，进程已经参与调度了
    }

    exit(0);
}