/* 将所有命令行参数回显到标准输出 */
#include "ourhdr.h"

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++)
        printf("argv[%d]: %s\n", i, argv[i]);
    exit(0);
}