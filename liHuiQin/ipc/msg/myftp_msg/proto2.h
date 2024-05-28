#ifndef __PROTO_H__
#define __PROTO_H__

#define KEYPATH "/etc/services"
#define KEYPROJ 'a'

#define PATHMAX 1024
#define DATAMAX 1024

enum
{
    MSG_PATH = 1,
    MSG_DATA,
    MSG_EOT
};

typedef struct msg_path_st
{
    long mtype;         /* must be MSG_PATH */
    char path[PATHMAX]; /* ASCIIZ带尾0的串 */
} msg_path_t;

/* 不推荐
 * datalen  >   0 :data
 *          ==  0 :eot
 */
typedef struct msg_s2c_st
{
    long mtype; /* must be MSG_DATA or MSG_EOT */
    int datalen;
    char data[DATAMAX];
} msg_data_t;

#endif /* __PROTO_H__ */