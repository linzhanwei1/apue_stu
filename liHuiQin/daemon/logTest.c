#include <syslog.h>
#include <syslog.h>
#include <stdarg.h>
#include <unistd.h>

int main(void)
{
    int log_test;

    openlog("log_test", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "PID information, pid=%d", getpid());
    syslog(LOG_DEBUG, "debug message ");
    closelog();
}