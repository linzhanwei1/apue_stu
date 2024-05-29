#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "proto.h"

int main()
{
    int sd;
    struct sockaddr_in laddr, raddr;
    struct msg_st rbuf;
    socklen_t addrlen;
    char ipstr[INET_ADDRSTRLEN];

    if ((sd = socket(AF_INET, SOCK_DGRAM, 0 /* IPPROTO_UDP */)) < 0)
    {
        perror("socket()");
        exit(1);
    }

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(RCVPORT));
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);

    if (bind(sd, (const struct sockaddr *)&laddr, sizeof(laddr)) < 0)
    {
        perror("bind()");
        exit(1);
    }

    /* 非常重要 */
    addrlen = sizeof(raddr);

    while (1)
    {
        recvfrom(sd, &rbuf, sizeof(rbuf), 0, (struct sockaddr *)&raddr, &addrlen);
        inet_ntop(AF_INET, &raddr.sin_addr, ipstr, INET_ADDRSTRLEN);
        printf("----------MESSAGE FROM %s:%d----------\n", ipstr, ntohs(raddr.sin_port));
        printf("NAME = %s\n", rbuf.name);
        printf("MATH = %d\n", ntohl(rbuf.math));
        printf("CHINESE = %d\n", ntohl(rbuf.chinese));
    }

    close(sd);
    exit(0);
}