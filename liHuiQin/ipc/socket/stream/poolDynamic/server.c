#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>

#include "proto.h"

#define MINSPARESERVER 5
#define MAXSPARESERVER 10
#define MAXCLIENTS 20
#define LINEBUFSIZE 80

#define SIG_NOTIFY SIGUSR2

enum
{
    STATE_IDEL = 0,
    STATE_BUSY
};

struct server_st
{
    pid_t pid;
    int state;
    //  int resue;
};

static struct server_st *serverpool;
static int idle_count = 0, busy_count = 0;
static int sd;

static void usr2_handler(int s)
{
    return;
}

static void server_job(int pos)
{
    int ppid;
    struct sockaddr_in raddr;
    socklen_t raddrLen;
    int client_sd, len;
    long long stamp;
    char ipstr[INET_ADDRSTRLEN];
    char linebuf[LINEBUFSIZE];

    ppid = getppid();
    while (1)
    {
        serverpool[pos].state = STATE_IDEL;
        /* 通知父进程 */
        kill(ppid, SIG_NOTIFY);

        client_sd = accept(sd, (struct sockaddr *)&raddr, &raddrLen);
        if (client_sd < 0)
        {
            if (errno != EINTR || errno != EAGAIN)
            {
                perror("accept()");
                exit(1);
            }
        }
        serverpool[pos].state = STATE_BUSY;
        kill(ppid, SIG_NOTIFY);
        inet_ntop(AF_INET, &raddr.sin_addr, ipstr, INET_ADDRSTRLEN);
        //  printf("[%d]client:%s:%d\n", getpid(), ipstr, ntohs(raddr.sin_port));
        stamp = time(NULL);
        len = snprintf(linebuf, LINEBUFSIZE, FMT_STAMP, stamp);
        send(client_sd, linebuf, len, 0);
        /* if error */
        sleep(5);
        close(client_sd);
    }
}

static int add_1_server(void)
{
    int slot;
    pid_t pid;

    if (idle_count + busy_count >= MAXCLIENTS)
        return -1;

    for (slot = 0; slot < MAXCLIENTS; slot++)
    {
        if (serverpool[slot].pid == -1)
            break;
    }

    serverpool[slot].state = STATE_IDEL;
    pid = fork();
    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }

    if (pid == 0)
    {
        // child
        server_job(slot);
        exit(0);
    }
    else
    {
        // parent
        serverpool[slot].pid = pid;
        idle_count++;
    }
}

static int del_1_server(void)
{
    if (idle_count == 0)
        return -1;

    for (int i = 0; i < MAXCLIENTS; i++)
    {
        if (serverpool[i].pid != -1 && serverpool[i].state == STATE_IDEL)
        {
            kill(serverpool[i].pid, SIGTERM);
            serverpool[i].pid = -1;
            idle_count--;
            break;
        }
    }

    return 0;
}

static int scan_pool(void)
{
    int idle = 0, busy = 0;

    for (int i = 0; i < MAXCLIENTS; i++)
    {
        if (serverpool[i].pid == -1)
            continue;
        if (kill(serverpool[i].pid, 0))
        {
            // 监测当前进程是否存在
            serverpool[i].pid = -1;
            continue;
        }
        if (serverpool[i].state == STATE_IDEL)
            idle++;
        else if (serverpool[i].state == STATE_BUSY)
            busy++;
        else
        {
            fprintf(stderr, "Unknown state.\n");
            // _exit(1);
            abort();
        }
    }

    idle_count = idle;
    busy_count = busy;

    return 0;
}

int main(int argc, char *argv[])
{
    struct sigaction sa, oldsa;
    struct sockaddr_in laddr;
    socklen_t raddrLen;
    char ipstr[INET_ADDRSTRLEN];
    sigset_t set, oset;

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD, &sa, &oldsa);

    sa.sa_handler = usr2_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIG_NOTIFY, &sa, &oldsa);

    sigemptyset(&set);
    sigaddset(&set, SIG_NOTIFY);
    sigprocmask(SIG_BLOCK, &set, &oset);

    serverpool = mmap(NULL, sizeof(struct server_st) * MAXCLIENTS, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (serverpool == MAP_FAILED)
    {
        perror("mmap()");
        exit(1);
    }

    for (int i = 0; i < MAXCLIENTS; i++)
    {
        serverpool[i].pid = -1;
    }

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket()");
        exit(1);
    }

    // 配置socket
    int val = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
    {
        perror("setsockopt()");
        exit(1);
    }

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(SERVERPORT));
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
    if (bind(sd, (const struct sockaddr *)&laddr, sizeof(laddr)) < 0)
    {
        perror("bind()");
        exit(1);
    }

    if (listen(sd, 100) < 0)
    {
        perror("listen()");
        exit(1);
    }

    for (int i = 0; i < MINSPARESERVER; i++)
    {
        add_1_server();
    }

    while (1)
    {
        sigsuspend(&oset);
        scan_pool();
        // contrl the pool
        if (idle_count > MAXSPARESERVER)
        {
            for (int i = 0; i < (idle_count - MAXSPARESERVER); i++)
                del_1_server();
        }
        else if (idle_count < MINSPARESERVER)
        {
            for (int i = 0; i < (MINSPARESERVER - idle_count); i++)
                add_1_server();
        }

        // printf pool info
        for (int i = 0; i < MAXCLIENTS; i++)
        {
            if (serverpool[i].pid == -1)
                putchar(' ');
            else if (serverpool[i].state == STATE_IDEL)
                putchar('.');
            else
                putchar('x');
        }
        putchar('\n');
    }

    sigprocmask(SIG_SETMASK, &oset, NULL);

    exit(0);
}
