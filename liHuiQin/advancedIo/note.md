# 高级I/O
## 非阻塞I/O
    - 非阻塞I/O
    - I/O多路复用(适用I/O密集型任务)
        - select(); =>以事件为单位组织文件描述符
        - poll(); => 以文件描述符为单位组织事件
        - epoll();
            - int epoll_create(int size);
            - int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
            - int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
    - 其他读写函数
        - ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
        - ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
        - readn();  apue作者自己封装
        - write();  apue作者自己封装
    - 存储映射I/O
        - void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
        - int munmap(void *addr, size_t length);
        - 具备亲缘关系的进程间通信
    - 文件锁
        fcntl();
        lockf();
        flock();
## 有限状态机
