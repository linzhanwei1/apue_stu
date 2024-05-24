#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

/* 漏桶实现 */

#define CPS 10
#define BUFSIZE CPS

static volatile int loop = 0;

static void alrm_handler(int s)
{
    // alarm(1);
    loop = 1;
}

int main(int argc, char *argv[])
{
    int sfd, len, ret, pos;
    char buf[BUFSIZE];
    struct itimerval itv;

    if (argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    signal(SIGALRM, alrm_handler);
    // alarm(1);
    itv.it_interval.tv_sec = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &itv, NULL) < 0)
    {
        perror("setitimer()");
        exit(1);
    }

    do
    {
        if ((sfd = open(argv[1], O_RDONLY)) < 0)
        {
            if (errno != EINTR)
            {
                perror("open");
                exit(1);
            }
        }
    } while (sfd < 0);

    while (1)
    {
        while (!loop)
            pause();
        loop = 0;

        while ((len = read(sfd, buf, BUFSIZE)) < 0)
        {
            if (errno == EINTR)
                continue;
            perror("read()");
            break;
        }

        if (len == 0)
            break;

        pos = 0;
        while (len > 0)
        {
            if ((ret = write(STDOUT_FILENO, buf + pos, len)) < 0)
            {
                if (errno == EINTR)
                    continue;
                perror("write()");
                exit(1);
            }
            pos += ret;
            len -= ret;
        }
    }

    write(STDOUT_FILENO, "\n", 1);

    close(sfd);

    exit(0);
}