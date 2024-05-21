/* chdir函数实例 */
#include "ourhdr.h"

int main(int argc, char *argv[])
{
    if (chdir("/tmp") < 0)
        err_sys("chdir failed");

    printf("chdir to /tmp succeeded\n");
    exit(0);
}