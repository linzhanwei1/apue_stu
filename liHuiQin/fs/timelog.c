#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FNAME "/tmp/out"
#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    FILE *fp;
    int count = 0;
    char buf[BUFSIZE];
    time_t stamp;
    struct tm *tm;

    if ((fp = fopen(FNAME, "a+")) == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    while (fgets(buf, BUFSIZE, fp) != NULL)
    {
        count++; // 数一下有多少行
    }

    while (1)
    {
        time(&stamp);
        tm = localtime(&stamp);
        fprintf(fp, "%-4d%d-%d-%d %d:%d:%d\n", ++count, tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                tm->tm_hour, tm->tm_min, tm->tm_sec);
        fflush(fp);
        sleep(1);
    }

    fclose(fp);
    exit(0);
}
