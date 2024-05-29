#ifndef __PROTO_H__
#define __PROTO_H__

#include <stdint.h>

#define NAMESIZE 11
#define RCVPORT "1989"

struct msg_st
{
    uint8_t name[NAMESIZE];
    uint32_t math;
    uint32_t chinese;
} __attribute__((packed));

#endif /* __PROTO_H__ */