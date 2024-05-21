/* 测试标准输入能否被设置位移量 */
#include <sys/types.h>
#include "ourhdr.h"

int main(int argc, char *argv[])
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("cannot seek\n");
    else
        printf("seek OK\n");

    exit(0);
}