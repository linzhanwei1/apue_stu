#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // execl("bin/sh", "sh", "-c", "date +%s", NULL);
    system("date +%s > /tmp/out");

    exit(0);
}