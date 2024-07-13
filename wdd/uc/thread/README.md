# 互斥锁
## 互斥锁的类型
* `PTHREAD_MUTEX_FAST_NP`：（缺省），标准互斥锁
  * 同一个线程第一上锁成功，第二次上锁会阻塞。
  * 此类型的互斥锁不会检测死锁。
  * 如果线程在不受限解除互斥锁的情况下尝试重新加锁，则会产生死锁。
  * 尝试解除由其他线程锁定的互斥锁，会产生不确定行为。
  * 如果尝试解锁未锁定的互斥锁，也会产生不确定行为。
  * 一个线程在某一时间段，只能对一个互斥锁加锁一次，且解锁与上锁应由同一线程来完成，加锁和解锁是一一对应的。
* `PTHREAD_MUTEX_RECURSIVE_NP`：递归互斥锁
  * 同一个线程第一加锁成功，第二次加锁也能成功，上锁次数（内部计数）。
  * 如果线程在不首先解除互斥锁的情况下尝试重新加锁，可以加锁成功。
  * 多次加锁需要相同次数解锁才能释放锁，其他线程才能加锁。
  * 如果线程尝试解除其他线程的锁（如别人上锁，我来解锁），会返回错误码。
  * 如果线程尝试对未锁定的锁解锁，会返回错误码。
* `PTHREAD_MUTEX_ERRORCHECK_NP`：检错互斥锁。
  * 同一个线程第一次加锁成功，第二次加锁会返回错误。
  * 此类互斥锁可提供错误检查。
  * 如果线程在不首先解锁的情况下尝试加锁，会返回错误。
  * 如果线程尝试解除其他线程的锁，会返回错误。
  * 如果线程尝试解除未锁定的锁，会返回错误。

## 互斥锁的作用范围
```c
#include <pthread.h>

int pthread_mutexattr_getpshared(const pthread_mutexattr_t *restrict attr, int *restrict pshared);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
```
  * `PTHREAD_PROCESS_PRIVATE`：（缺省），一个进程中的多个线程。
  * `PTHREAD_PROCESS_SHARED`：进程间，`vfork`中才生效，`fork`中无效。

## 互斥锁的协议属性
```c
#include <pthread.h>

int pthread_mutexattr_setprotocol(pthread_mutexattr_t *attr, int protocol);
int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *restrict attr, int *restrict protocol);

// 互斥对象的优先级上限
int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *restrict attr, int *restrict prioceiling);
int pthread_mutexattr_setprioceiling(pthread_mutexattr *attr, int prioceiling);
```
* `PTHREAD_PRIO_INHERIT`：当高优先级的线程等待低优先级线程锁定的互斥锁时，低优先级线程以高优先级线程的优先级运行。这种方式以继承的形式传递，解锁后，恢复原优先级。
* `PTHREAD_PRIO_NONE`：线程的优先级和调用不会受到互斥锁的影响。
* `PTHREAD_PRIO_PROTECT`：具有该类型的互斥锁的线程将以自己的优先级和具有互斥锁的优先级的较高优先级运行，与等待互斥锁线程的优先级无关。
  * 只有当策略为`SCHED_FIFO`/`SCHED_RR`才有用。

## 互斥锁的健壮
```c
#include <pthread.h>

int pthread_mutexattr_getrobust(const pthread_mutexattr_t *attr, int *robustness);
int pthread_mutexattr_setrobust(pthread_mutexattr_t *attr, int robustness);

// 强制同步互斥锁，解除由其他线程锁定的互斥锁，必须要求互斥锁设置为PTHREAD_MUTEX_ROBUST
int pthread_mutex_consistent(pthread_mutex_t *mutex)
```
* `PTHREAD_MUTEX_STALLED`：缺省
  * 如果一个线程退出之前没有对锁定的互斥锁解锁，则其他线程用`pthread_mutex_lock`加锁都会阻塞。
* `PTHREAD_MUTEX_ROBUST`：
  * 如果一个线程退出之前没有对锁定的互斥锁解锁，则其他线程用`pthread_mutex_lock`加锁会返回`EOWNERDEAD`。此时可调用`pthread_mutex_consistent`函数，
    让当前线程获得该互斥锁，然后通过`pthread_mutex_unlock`解锁。

## 死锁的必要条件
* 互斥条件：一个资源每次只能被一个进程/线程使用。
* 请求保持条件：一个进程/线程因请求资源而阻塞时，已获得的资源保持不变。
* 不可剥夺条件：进程/线程已获得的资源，在未使用完之前，不能强行剥夺。
* 循环与等待条件：若进程/线程之间形成一种首尾相接的循环等待资源关系。

## 如何避免死锁
* 破坏死锁的四个必要条件之一。
* 设置锁可以被剥夺。
* 加锁顺序：若有多个锁时，对锁的加锁顺序要一致。
* 加锁时限：尝试获取锁的时间要有一定的时限（不要用阻塞的加锁函数），超时放弃对锁的请求，并及时释放已占用的锁。
* 死锁检测：自行保存上锁和解锁记录，如果上锁成功后，之前上锁失败的记录清零。当上锁的次数达到某一个上限值时，就认为该锁已经死锁，不再去获取锁。


# 信号量
* 信号量是一个计数器，用于控制访问资源的线程数。
* 如果信号量初始值设置为1，等同于互斥锁。
## 有名信号量
```c
#include <fcntl.h>           
#include <sys/stat.h>        
#include <semaphore.h>

sem_t *sem_open(const char *name, int oflag);
sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
```
* `name`：信号量文件名，自动存储在`/dev/shm`路径下，`sem.name`
* `oflag`：
  * `O_CREAT`：创建
  * `O_EXCL`：排斥
  * `0`：获取
* `mode`：权限，搭配`O_CREAT`使用
* `value`：信号量初始值，只有`O_CREAT`时才需指定
* 返回值：成功返回信号量内存地址，失败返回`SEM_FAILED`，且设置全局`errno`

```c
//关闭信号量
int sem_close(sem_t *sem);

// 删除信号量文件，销毁
int sem_unlink(const char *name);

// 信号量减1，不够减即阻塞
int sem_wait(sem_t *sem);

// 信号量减1，不够减返回-1，设置全局errno（EAGAIN）
int sem_trywait(sem_t *sem);

// 信号量减1，不够减阻塞一段时间，超时返回01，设置全局errno（EAGAIN）
int sem_timedwait(sem_t *restrict sem, const struct timespec *restrict abs_timeout);
struct timespec {
    long tv_sec;
    long tv_nsec;
};
```
## 无名信号量
```c
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
```
* pshared：
  * `0`：表示信号量用进程的信号量（只能在同一个进程中多个线程使用）。
  * `非0`：以共享内存的方式，为多个进程共享使用（Linux不支持）。
* `value`：信号量初始值。

```c
#include <semaphore.h>

// 销毁信号量
int sem_destroy(sem_t *sem);

// 信号量减1，不够减即阻塞
int sem_wait(sem_t *sem);

// 信号量减1，不够减返回-1，设置全局errno（EAGAIN）
int sem_trywait(sem_t *sem);

// 信号量减1，不够减阻塞一段时间，超时返回01，设置全局errno（EAGAIN）
int sem_timedwait(sem_t *restrict sem, const struct timespec *restrict abs_timeout);
struct timespec {
    long tv_sec;
    long tv_nsec;
};
```
# 互斥量和信号量的比较
* 信号量的头文件`semaphore.h`，互斥量的头文件`pthread.h`。
* 信号量的操作函数成功返回0，失败返回-1并设置`errno`。互斥量的操作函数成功返回0，失败返回错误码。
* 互斥量任何时候都只允许一个线程访问共享资源。信号量可以限制访问共享资源的数量，当信号量初始值为1时，等同于互斥量。
* 操作的线程
  * 互斥量一般是哪个线程上锁，则必须哪个线程解锁。
* 信号量的`sem_wait`和`sem_post`可以不在同一个线程（甚至没有`sem_wait`也可以`sem_post`）。
* 信号量是的各种同步方式中唯一一个能在信号处理程序中安全的同步方式。
  * 互斥量上锁后，如果咋解锁过程中被中断了，将无法解锁。
  * 信号量`sem_post`时被中断了，依然可以`sem_post`。
* 强调的不一样，即使信号量的值为1
  * 互斥锁强调互斥，只允许一个线程上锁，上锁后一个线程执行，其余线程必须等待。
  * 信号量强调同步，可以用于互斥，但更多的情况是限制对于访问共享资源的线程数量。
* 互斥量是为了上锁而有限的，条件变量是为等待而有限的，信号量既可以用于上锁，又可以用于等待，因此会有更多的选择和更高的复杂性。
  * 互斥量可以和条件变量配合使用。
  * 信号量不能配合条件变量使用。
* 作用范围
  * 互斥量可以用于线程，某些平台可以用于进程。
  * 信号量既可以用于线程，也可以用于进程。













