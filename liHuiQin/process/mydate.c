#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define TIMESTRSIZE 1024
#define FMTSTRSIZE 1024

/*
 * -y : year
 * -m : month
 * -d : day
 * -H : hour
 * -M : minute
 * -S : second
 */

int main(int argc, char *argv[])
{
    time_t stamp;
    struct tm *tm;
    char timestr[TIMESTRSIZE];
    int c;
    char fmtstr[FMTSTRSIZE];
    FILE *fp = stdout;

    fmtstr[0] = '\0';

    stamp = time(NULL);
    tm = localtime(&stamp);

    while (1)
    {
        /* :带参数选项 -非选项的传参 */
        if ((c = getopt(argc, argv, "-H:MSy:md")) < 0)
            break;

        switch (c)
        {
        case 1: // 非选项传参,仅处理第一个非选项参数
            if (fp == stdout)
            {
                if ((fp = fopen(argv[optind - 1], "w")) == NULL)
                {
                    perror("fopen()");
                    fp = stdout;
                }
            }

            break;
        case 'H':
            if (strcmp(optarg, "12") == 0)
                strncat(fmtstr, "%I(%P) ", FMTSTRSIZE - 1);
            else if (strcmp(optarg, "24") == 0)
                strncat(fmtstr, "%H ", FMTSTRSIZE - 1);
            else
                fprintf(stderr, "Invalid argument of -H\n");
            break;
        case 'M':
            strncat(fmtstr, "%M ", FMTSTRSIZE - 1);
            break;
        case 'S':
            strncat(fmtstr, "%S ", FMTSTRSIZE - 1);
            break;
        case 'y':
            if (strcmp(optarg, "2") == 0)
                strncat(fmtstr, "%y ", FMTSTRSIZE - 1);
            else if (strcmp(optarg, "4") == 0)
                strncat(fmtstr, "%Y ", FMTSTRSIZE - 1);
            else
                fprintf(stderr, "Invalid argument of -y\n");
            break;
        case 'm':
            strncat(fmtstr, "%m ", FMTSTRSIZE - 1);
            break;
        case 'd':
            strncat(fmtstr, "%d ", FMTSTRSIZE - 1);
            break;
        default:
            break;
        }
    }

    strncat(fmtstr, "\n", FMTSTRSIZE - 1);
    strftime(timestr, TIMESTRSIZE, fmtstr, tm);
    fputs(timestr, fp);

    if (fp != stdout)
        fclose(fp);
    exit(0);
}