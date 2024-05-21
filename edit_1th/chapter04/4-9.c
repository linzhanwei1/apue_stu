/* getcwd函数实例 */
#include "ourhdr.h"

int main(int argc, char *argv[])
{
    char *ptr;
    int size;

    // if (chdir("/usr/spool/uucppublic") < 0)
    //     err_sys("chdir failed");

    ptr = path_alloc(&size);
    if (getcwd(ptr, size) == NULL)
        err_sys("getcwd failed");

    printf("cwd = %s\n", ptr);

    free(ptr);
    exit(0);
}