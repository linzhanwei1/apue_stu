# 进程间通信IPC
## 管道
- 内核提供，单工，自同步机制
    1. 匿名管道，适用于有亲缘关系的进程
        - int pipe(int pipefd[2]);
    2. 命名管道
        - int mkfifo(const char *pathname, mode_t mode);
## XSI -> systemV
- IPC -> Inter-Process Communication
    - 主动端:先发包的一方
    - 被动端:先收包的一方(先运行等待收包)
- key：key_t ftok(const char *pathname, int proj_id);
- xxxget xxxop xxxctl (xxx=msg|sem|shm)
- ipcs - provide information on ipc facilities
- ipcrm - remove a message queue, semaphore set or shared memory id
- Message Queues
    - int msgget(key_t key, int msgflg);
    - int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
    - ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
                      int msgflg);
    - int msgctl(int msqid, int cmd, struct msqid_ds *buf);
- Semaphore Arrays
    - int semget(key_t key, int nsems, int semflg);
    - int semop(int semid, struct sembuf *sops, unsigned nsops);
    - int semctl(int semid, int semnum, int cmd, ...);
- Shared Memory Segments
## 网络套接字socket
- 跨主机的传输需要注意的问题
    1. 字节序问题:
        - 大端:低地址处放高字节
        - 小端:低地址处放低字节
        - 主机字节序:host
        - 网络字节序:network
        - _to _ _:htons,htonl,ntohs,ntohl
    2. 对齐:
    3. 类型长度的问题:int32_t uint32_t
- netstat -anu
- 报式套接字(UDP):
    - 被动端(先运行):
        1. 取得socket
        2. 给socket取得地址
        3. 收/发消息
        4. 关闭socket
    - 主动端:
        1. 取得socket
        2. 给socket取得地址(可省略)
        3. 发/收消息
        4. 关闭socket
    - 相关API:
        - int socket(int domain, int type, int protocol);
        - int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        - ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);
        - ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);
        - int inet_pton(int af, const char *src, void *dst);
        - const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
        -int getsockopt(int sockfd, int level, int optname,
                      void *optval, socklen_t *optlen);<br>
       int setsockopt(int sockfd, int level, int optname,
                      const void *optval, socklen_t optlen);
    - 多点通讯:
        - 广播(全网广播，子网广播)
        - 多播/组播
- 流式套接字(TCP):
    - Client(主动端):
        1. 获取socket
        2. 给socket取得地址(可省略)
        3. 发送连接
        4. 收/发消息
        5. 关闭
    - Server(被动端):
        1. 获取socket
        2. 给socket取得地址
        3. 将socket置为监听模式
        4. 接受连接
        5. 收/发消息
        6. 关闭
    - 相关API
        - int socket(int domain, int type, int protocol);
        - int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        - int listen(int sockfd, int backlog);
        - int accept(int socket, struct sockaddr *restrict address,
              socklen_t *restrict address_len);
        - ssize_t send(int socket, const void *buffer, size_t length, int flags);
        - ssize_t recv(int sockfd, void *buf, size_t len, int flags);
        - int connect(int socket, const struct sockaddr *address,
              socklen_t address_len);
    - 动态进程池
    ```sh
    while true; do (./client 127.0.0.1 &); sleep 1; done
    ```
