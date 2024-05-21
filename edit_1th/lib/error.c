#include <errno.h>  /* for definition of errno */
#include <stdarg.h> /* ANSI C header file */

#include "ourhdr.h"

/* caller can set this from argv[0] */
char *pname = NULL;

/* Print a message and return to caller. Caller specifies "errnoflag." */
static void err_doit(int errnoflag, const char *fmt, va_list ap)
{
    int errno_save;
    char buf[MAXLINE];

    /* value caller might want printed */
    errno_save = errno;
    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    if (errnoflag)
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(errno_save));
    strcat(buf, "\n");
    /* in case stdout and stderr are the same */
    fflush(stdout);
    fputs(buf, stderr);
    /* flushes all stdio output streams */
    fflush(NULL);
    return;
}

/* Nonfatal error related to a system call. Print a message and return. */
void err_ret(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
}

/* Fatal error related to a system call. Print a message and terminate. */
void err_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    exit(1);
}

/* Fatal error related to a system call. Print a message, fump core, and terminate. */
void err_dump(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    abort(); /* dump core and terminate */
    exit(1); /* shouldn't get here */
}

/* Nonfatal error unrelated to a  system call. Print a message and return. */
void err_msg(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, fmt, ap);
    va_end(ap);
    return;
}

/* Fatal error unrelated to a system call. Print a message and terminate. */
void err_quit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, fmt, ap);
    va_end(ap);
    exit(1);
}
