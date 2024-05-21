#include "ourhdr.h"

int main(int argc, char *argv[])
{
    char buf[MAXLINE];

    while (fgets(buf, MAXLINE, stdin) != NULL)
        if (fputs(buf, stdout) == EOF)
            err_sys("output error");

    if (ferror(stdin))
        err_sys("input error");

    exit(0); // 没有显示地关闭标准IO流。我们指导exit函数将会刷新任何未写地数据，然后关闭所有打开的流
}