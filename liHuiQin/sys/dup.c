#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FNAME "/tmp/out"

int main(int argc, char *argv[])
{
    int fd;

    if ((fd = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0600)) < 0)
    {
        perror("open()");
        exit(1);
    }

    if (STDOUT_FILENO != dup2(fd, STDOUT_FILENO))
        close(fd);

    /*===============================================*/
    puts("hello1234!");

    exit(0);
}