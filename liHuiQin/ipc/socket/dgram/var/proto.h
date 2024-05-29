#ifndef __PROTO_H__
#define __PROTO_H__

#include <stdint.h>

#define NAMEMAX (512 - 8 - 8) // UDP包的推荐长度 512- (sizeof(math)+sizeof(chinese)) - 包头长度
#define RCVPORT "1989"

struct msg_st
{
    uint32_t math;
    uint32_t chinese;
    uint8_t name[1];
} __attribute__((packed));

#endif /* __PROTO_H__ */