#ifndef __ANY_TIMER_H__
#define __ANY_TIMER_H__

#define JOB_MAX 1024
typedef void at_jobfunc_t(void *);

/*
 *  return  >= 0        成功，返回任务ID
 *          == -EINVAL  失败，参数非法
 *          == -ENOSPC  失败，数组满
 *          == -ENOMEM  失败，内存空间不足
 */
int at_addjob(int sec, at_jobfunc_t *jobp, void *arg);

/*
 *  return  >= 0        成功，返回任务ID
 *          == -EINVAL  失败，参数非法
 *          == -ENOSPC  失败，数组满
 *          == -ENOMEM  失败，内存空间不足
 */
int at_addjob_repeat();
/*
 *  return  == 0        成功，指定任务成功取消
 *          == -EINVAL  失败，参数非法
 *          == -EBUSY   失败，指定任务已经完成
 *          == -ECANCELED  失败，指定任务重复取消
 */
int at_canceljob(int id);

/*
 *  return  == 0        成功，指定任务成功释放
 *          == -EINVAL  失败，参数非法
 *          == -EBUSY   失败，指定任务为周期性任务
 */
int at_waitjob(int id);

// at_pausejob();
// at_resumejob();

#endif /* __ANY_TIMER_H__ */