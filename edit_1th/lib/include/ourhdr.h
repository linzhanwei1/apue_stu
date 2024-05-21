/* Our own header, to be included before all standard system headers. */

#ifndef __OURHDR_H__
#define __OURHDR_H__

#include <sys/types.h> // required for some of our prototypes
#include <stdio.h>     // for convenience
#include <stdlib.h>    // for convenience
#include <string.h>    // for convenience
#include <unistd.h>    // for convenience

#define MAXLINE 4096 // max line length

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)  // default file access permissions for nre files
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH) // default permissions for new directories

/* functions */
char *path_alloc(int *size);
void set_fl(int fd, int flags);
void clr_fl(int fd, int flags);

void err_msg(const char *fmt, ...); /* App misc_source */
void err_dump(const char *fmt, ...);
void err_quit(const char *fmt, ...);
void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);

#endif /* __OURHDR_H__ */