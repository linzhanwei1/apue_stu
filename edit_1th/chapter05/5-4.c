/* tmpnam tmpfile函数实例 */
#include "ourhdr.h"

int main(int argc, char *argv[])
{
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    printf("%s\n", tmpnam(NULL)); /* first temp name */

    tmpnam(name); /* second temp name */
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL) /* create temp file */
        err_sys("tmpfile error");
    fputs("one line if output\n", fp);
    rewind(fp);
    if (fgets(line, sizeof(line), fp) == NULL)
        err_sys("fgets error");
    fputs(line, stdout);

    exit(0);
}