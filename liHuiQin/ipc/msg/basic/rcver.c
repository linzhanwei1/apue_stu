#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "proto.h"

int main(int argc, char **argv)
{
    key_t key;
    int msgid;
    struct msg_st rbuf;

    /* get key */
    if ((key = ftok(KEYPATH, KEYPROJ)) < 0)
    {
        perror("ftok()");
        exit(1);
    }

    /* get Message Queues */
    if ((msgid = msgget(key, IPC_CREAT | 0600)) < 0)
    {
        perror("msgid()");
        exit(1);
    }

    /* recv message */
    while (1)
    {
        if (msgrcv(msgid, &rbuf, sizeof(rbuf) - sizeof(long), 0, 0) < 0)
        {
            perror("msgrcv()");
            exit(1);
        }
        printf("NAME = %s\n", rbuf.name);
        printf("MATH = %d\n", rbuf.math);
        printf("CHINESE = %d\n", rbuf.chinese);
    }

    /* destroy Message Queues */
    msgctl(msgid, IPC_RMID, NULL);
    exit(0);
}