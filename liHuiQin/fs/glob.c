#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

// #define PAT "/etc/a*.conf"
// #define PAT "/etc/*"  // 不包括隐藏文件
#define PAT "/etc/.*" // 包括隐藏文件

#if 0
static int errfunc_(const char *errpath, int eerrno)
{
    puts(errpath);
    fprintf(stderr, "ERROR MSG:%s\n", strerror(eerrno));
    return 0;
}
#endif

int main(int argc, char *argv[])
{
    glob_t globres;
    int err = glob(PAT, 0, NULL, &globres);
    if (err)
    {
        printf("Error code = %d\n", err);
        exit(1);
    }

    for (int i = 0; i < globres.gl_pathc; i++)
        puts(globres.gl_pathv[i]);

    globfree(&globres);
    exit(0);
}