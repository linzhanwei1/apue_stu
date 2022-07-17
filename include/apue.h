/* Our own header, to be included before all standard system headers. */

#ifndef __APUE_H__
#define __APUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE 4096                            /* max line length */



void err_msg(const char *fmt, ...);             /* App misc_source */
void err_dump(const char *fmt, ...) __attribute__((noreturn));
void err_quit(const char *fmt, ...);
void err_cont(int error, const char *fmt, ...);
void err_exit(int error, const char *fmt, ...) __attribute__((noreturn));
void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...) __attribute__((noreturn));

#endif /* __APUE_H__ */