#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char **argv)
{
    for (int i = 0; environ[i]; i++)
        puts(environ[i]);

    exit(0);
}