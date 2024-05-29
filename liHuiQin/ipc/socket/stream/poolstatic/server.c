#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

#include "proto.h"

#define PROCNUM 4

static void serverJob(int cd)
{
    char buf[1024];
    int len;

    len = sprintf(buf, FMT_STAMP, (long long)time(NULL));
    if (send(cd, buf, len, 0) < 0)
    {
        perror("send()");
        exit(1);
    }
}

static void server_loop(int sd)
{
    struct sockaddr_in raddr;
    socklen_t raddrLen;
    char ipstr[INET_ADDRSTRLEN];
    int cd;

    raddrLen = sizeof(raddr);
    while (1)
    {
        if ((cd = accept(sd, (struct sockaddr *)&raddr, &raddrLen)) < 0)
        {
            perror("accept()");
            exit(1);
        }

        inet_ntop(AF_INET, &raddr.sin_addr, ipstr, INET_ADDRSTRLEN);
        printf("[%d]Client:%s:%d\n", getpid(), ipstr, ntohs(raddr.sin_port));

        serverJob(cd);
        close(cd);
    }

    close(sd);
}

int main(int argc, char *argv[])
{
    int sd;
    struct sockaddr_in laddr;
    pid_t pid;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0 /* IPPROTO_TCP,IPPOROTO_SCTP */)) < 0)
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

    if (listen(sd, 10) < 0)
    {
        perror("listen()");
        exit(1);
    }

    for (int i = 0; i < PROCNUM; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork()");
            exit(1);
        }

        if (pid == 0)
        {
            // child
            server_loop(sd);
            exit(0);
        }
    }

    for (int i = 0; i < PROCNUM; i++)
        wait(NULL);

    close(sd);
    exit(0);
}