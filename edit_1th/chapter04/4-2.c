/* 4-2 access函数示例 */
#include <sys/types.h>
#include <fcntl.h>
#include "ourhdr.h"

/* 进程可以按其实际用户ID和实际组ID来测试其存取能力。 */
int main(int argc, char *argv[])
{
    if (argc != 2)
        err_quit("usage: a.out <pathname>");

    if (access(argv[1], R_OK) < 0)
        err_ret("access error for %s", argv[1]);
    else
        printf("read access OK\n");

    if (open(argv[1], O_RDONLY) < 0)
        err_ret("open error for %s", argv[1]);
    else
        printf("open for reading OK\n");

    exit(0);
}