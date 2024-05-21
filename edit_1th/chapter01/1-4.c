/* 打印进程ID */
#include "ourhdr.h"

int main(int argc, char *argv[])
{
    printf("hello world from process ID %d\n", getpid());

    exit(0);
}