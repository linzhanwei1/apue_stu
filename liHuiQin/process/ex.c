#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * date +%s
 */
int main(int argc, char **argv)
{
    puts("Begins!");

    /* 先刷新缓冲区再进行execl */
    fflush(NULL);
    execl("/usr/bin/date", "date", "+%s", NULL);

    /* execl函数成功了就不会返回，返回就代表失败了 */
    perror("execl()");
    exit(1);
    puts("End!");

    exit(0);
}