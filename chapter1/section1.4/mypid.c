#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello world from process ID %ld\n", (long)getpid());

    exit(0);
}