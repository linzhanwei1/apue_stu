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
