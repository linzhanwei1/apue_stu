#ifndef __MYPIPE_H__
#define __MYPIPE_H__

#define PIPESIZE 1024
#define MYPIPE_READ 0x00000001UL
#define MYPIPE_WRITE 0x00000002UL

typedef void mypipe_t;

mypipe_t *mypipe_init(void);
int mypipe_register(mypipe_t *, int opmap);
int mypipe_unregister(mypipe_t *, int opmap);
int mypipe_write(mypipe_t *ptr, const void *buf, size_t);
int mypipe_destroy(mypipe_t *ptr);
#endif /* __MYPIPE_H__ */