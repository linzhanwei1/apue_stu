# 线程

## 基本API
<table border="1"  width="1000px" cellspacing="0px">
  <thead align="center">
    <td>API</td>
    <td>NAME</td>
  </thead>
  <tbody></tbody>
  <tr>
    <td>int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)</td>
    <td>pthread_create - create a new thread</td>
  </tr>
  <tr>
    <td>pthread_t pthread_self(void)</td>
    <td>pthread_self - obtain ID of the calling thread</td>
  </tr>
    <td>int pthread_equal(pthread_t t1, pthread_t t2)</td>
    <td>pthread_equal - compare thread IDs</td>
  </tr>
  <tr>
    <td>void pthread_exit(void *retval)</td>
    <td>pthread_exit - terminate calling thread</td>
  </tr>
  <tr>
    <td>int pthread_join(pthread_t thread, void **retval)</td>
    <td>pthread_join - join with a terminated thread</td>
  </tr>
  <tr>
    <td> void pthread_cleanup_push(void (*routine)(void *),
                                 void *arg);<br>
       void pthread_cleanup_pop(int execute);</td>
    <td>pthread_cleanup_push, pthread_cleanup_pop - push and pop thread cancellation clean-up handlers</td>
  </tr>
  <tr>
    <td> int pthread_setcancelstate(int state, int *oldstate);<br>
       int pthread_setcanceltype(int type, int *oldtype);</td>
    <td>pthread_setcancelstate, pthread_setcanceltype - set cancelability state and type</td>
  </tr>
  <tr>
    <td>void pthread_testcancel(void)</td>
    <td>pthread_testcancel - request delivery of any pending cancellation request</td>
  </tr>
  <tr>
    <td>int pthread_detach(pthread_t thread)</td>
    <td>pthread_detach - detach a thread</td>
  </tr>
  <tr>
    <td>int pthread_mutex_destroy(pthread_mutex_t *mutex);<br>
       int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);<br>
       pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;</td>
    <td>pthread_mutex_destroy, pthread_mutex_init — destroy and initialize a mutex</td>
  </tr>
  <tr>
    <td>int pthread_mutex_lock(pthread_mutex_t *mutex);<br>
       int pthread_mutex_trylock(pthread_mutex_t *mutex);<br>
       int pthread_mutex_unlock(pthread_mutex_t *mutex);</td>
    <td>pthread_mutex_lock, pthread_mutex_trylock, pthread_mutex_unlock — lock and unlock a mutex</td>
  </tr>
  <tr>
    <td>int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));<br>
       pthread_once_t once_control = PTHREAD_ONCE_INIT;</td>
    <td>pthread_once — dynamic package initialization</td>
  </tr>
  <tr>
    <td>int pthread_cond_destroy(pthread_cond_t *cond);<br>
       int pthread_cond_init(pthread_cond_t *restrict cond,
              const pthread_condattr_t *restrict attr);<br>
       pthread_cond_t cond = PTHREAD_COND_INITIALIZER;</td>
    <td>pthread_cond_destroy, pthread_cond_init - destroy and initialize condition variables</td>
  </tr>
  <tr>
    <td>int pthread_cond_broadcast(pthread_cond_t *cond);<br>
       int pthread_cond_signal(pthread_cond_t *cond);</td>
    <td>pthread_cond_broadcast, pthread_cond_signal - broadcast or signal a condition</td>
  </tr>
  <tr>
    <td>int pthread_cond_timedwait(pthread_cond_t *restrict cond,
              pthread_mutex_t *restrict mutex,
              const struct timespec *restrict abstime);<br>
       int pthread_cond_wait(pthread_cond_t *restrict cond,
              pthread_mutex_t *restrict mutex);</td>
    <td>pthread_cond_timedwait, pthread_cond_wait - wait on a condition</td>
  </tr>
  <tr>
    <td>int pthread_attr_init(pthread_attr_t *attr);<br>
       int pthread_attr_destroy(pthread_attr_t *attr);</td>
    <td>pthread_attr_init, pthread_attr_destroy - initialize and destroy thread attributes object</td>
  </tr>
  <tr>
    <td>int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);<br>
       int pthread_mutexattr_init(pthread_mutexattr_t *attr);</td>
    <td>pthread_mutexattr_destroy, pthread_mutexattr_init - destroy and initialize the mutex attributes object</td>
  </tr>
  <tr>
    <td>int pthread_mutexattr_getpshared(const pthread_mutexattr_t *
          restrict attr, int *restrict pshared);<br>
       int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr,
          int pshared);</td>
    <td>pthread_mutexattr_getpshared, pthread_mutexattr_setpshared - get and set the process-shared attribute</td>
  </tr>
  <tr>
    <td>int pthread_mutexattr_gettype(const pthread_mutexattr_t *restrict attr, int *restrict type);<br>
       int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
    </td>
    <td>pthread_mutexattr_getpshared, pthread_mutexattr_setpshared - get and set the process-shared attribute</td>
  </tr>
  <tr>
    <td>int pthread_condattr_destroy(pthread_condattr_t *attr);<br>
       int pthread_condattr_init(pthread_condattr_t *attr);
    </td>
    <td>pthread_condattr_destroy, pthread_condattr_init - destroy and initialize the condition variable attributes object</td>
  </tr>

</table>

## 线程的终止
- 线程从启动例程返回，返回值是线程的退出码
- 线程可以被同一进程中的其他线程取消
- 线程调用pthread_exit()函数
## 栈的清理
- pthread_cleanup_push()
- pthread_cleanup_pop()
## 线程的取消选项(先取消再收尸)
- pthread_cancel();
- 取消有2种状态:允许和不允许
    - 允许取消又分为:异步cancel,推迟cancel(默认)->推迟至cancel点再响应
- cancel点：POSIX定义的cancel点，都是可能引发阻塞的系统调用
    - pthread_setcancelstate():设置是否允许取消
    - pthread_setcanceltype():设置取消方式
    - pthread_testcancel():本函数什么都不做，就是一个取消点
- 线程分离
    pthread_detach();
- 线程同步
  - 互斥量:
    - pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
    - int pthread_mutex_destroy(pthread_mutex_t *mutex);
    - int pthread_mutex_lock(pthread_mutex_t *mutex);
    - int pthread_mutex_trylock(pthread_mutex_t *mutex);
    - int pthread_mutex_unlock(pthread_mutex_t *mutex);
  - 条件变量(通知法，改善忙等的消耗的特性):
    - pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    - int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
    - int pthread_cond_destroy(pthread_cond_t *cond);
    - int pthread_cond_broadcast(pthread_cond_t *cond);
    - int pthread_cond_signal(pthread_cond_t *cond);
    - int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
    - int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);  
  - 信号量:
  - 读写锁(避免写者饿死):
    - 读锁(共享锁)
    - 写锁(互斥锁)
  - 线程属性:
    - int pthread_attr_init(pthread_attr_t *attr);
    - int pthread_attr_destroy(pthread_attr_t *attr);
    - pthread_attr_setaffinity_np(3);
    - pthread_attr_setdetachstate(3);
    - pthread_attr_setguardsize(3);
    - pthread_attr_setinheritsched(3);
    - pthread_attr_setschedparam(3);
    - pthread_attr_setschedpolicy(3);
    - pthread_attr_setscope(3);
    - pthread_attr_setstack(3);
    - pthread_attr_setstackaddr(3);
    - pthread_attr_setstacksize(3);
    - pthread_getattr_np(3)
  - 线程同步的属性
    - 互斥量属性
      - int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
      - int pthread_mutexattr_init(pthread_mutexattr_t *attr);
      - int pthread_mutexattr_getpshared(const pthread_mutexattr_t *
              restrict attr, int *restrict pshared);
      - int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr,
              int pshared);
      - clone(); 使用系统调用时，互斥量是否跨进程起作用，以上2个API
      - int pthread_mutexattr_gettype(const pthread_mutexattr_t *restrict attr,
              int *restrict type);
      - int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
  - 条件变量属性
    - int pthread_condattr_destroy(pthread_condattr_t *attr);
    - int pthread_condattr_init(pthread_condattr_t *attr);
  - 读写锁属性
- 重入(线程安全):
  - 多线程种的io
  - 线程与信号
    - int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);
    - int sigwait(const sigset_t *set, int *sig);
    - int pthread_kill(pthread_t thread, int sig);


- 动态模块的单次初始化
  - int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));