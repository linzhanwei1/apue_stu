#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LEFT 30000000
#define RIGHT 30000200
#define N 3

int main(int argc, char **argv)
{
    int i, j, mark, n;
    pid_t pid;

    for (n = 0; n < N; n++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork():");
            exit(1);
        }
        else if (pid == 0)
        {
            for (i = LEFT + n; i <= RIGHT; i += N)
            {

                // child
                mark = 1;
                for (j = 2; j < i / 2; j++)
                {
                    if (i % j == 0)
                    {
                        mark = 0;
                        break;
                    }
                }
                if (mark)
                    printf("[%d]%d is a primer\n", n, i); // 进程0永远拿不到任何质数
            }
            exit(0);
        }
        else
        {
            // parent
        }
    }

    for (n = 0; n < N; n++)
        wait(NULL);

    exit(0);
}