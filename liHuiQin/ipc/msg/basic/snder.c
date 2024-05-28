#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "proto.h"

int main(int argc, char **argv)
{
    key_t key;
    int msgid;
    struct msg_st sbuf;

    /* get key */
    if ((key = ftok(KEYPATH, KEYPROJ)) < 0)
    {
        perror("ftok()");
        exit(1);
    }

    /* get Message Queues */
    if ((msgid = msgget(key, 0)) < 0)
    {
        perror("msgid()");
        exit(1);
    }

    /* send message */
    sbuf.mytype = 1;
    strcpy(sbuf.name, "Alan");
    sbuf.math = rand() % 100;
    sbuf.chinese = rand() % 100;
    if (msgsnd(msgid, &sbuf, sizeof(sbuf) - sizeof(long), 0) < 0)
    {
        perror("msgrcv()");
        exit(1);
    }

    puts("ok!");
    exit(0);
}