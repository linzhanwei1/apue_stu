#ifndef __PROTO_H__
#define __PROTO_H__

#define KEYPATH "/etc/services"
#define KEYPROJ 'g'
#define NAMESIZE 32

struct msg_st
{
    long mytype;
    char name[NAMESIZE];
    int math;
    int chinese;
};

#endif /* __PROTO_H__ */