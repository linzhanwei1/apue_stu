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