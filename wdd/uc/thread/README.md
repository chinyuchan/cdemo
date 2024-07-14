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


# 条件变量
* 条件变量不能单独使用，需要配合互斥锁一起使用。
* 允许线程以无竞争的方式等待特定条件发生，条件变量本身是由互斥锁保护的。

```c
#include <pthread.h>

// 静态初始化
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// 动态初始化
int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);

// 给在等待条件的一个线程发送信号，唤醒等待的线程，获得互斥锁
int pthread_cond_signal(pthread_cond_t *cond);

// 给在等待条件的一个线程发送广播，唤醒所有等待的线程，它们竞争互斥锁
int pthread_cond_broadcast(pthread_cond_t *cond);

// 阻塞等待，并且释放互斥锁（也就是说pthread_cond_wait之前，必须上锁成功），当线程被唤醒时，又会去竞争互斥锁，如果上锁成功，函数就返回，否则一直阻塞
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);

// 等待一段时间，如果超时，返回错误
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t  *mutex,  const  struct  timespec  *abstime);

// 销毁条件变量
int pthread_cond_destroy(pthread_cond_t *cond);


int pthread_condattr_init(pthread_condattr_t *attr);
int pthread_condattr_destroy(pthread_condattr_t *attr);
int pthread_condattr_getpshared(const pthread_condattr_t *restrict attr, int *restrict pshared);
int pthread_condattr_setpshared(pthread_condattr_t *attr, int pthread);
int pthread_condattr_getclock(const pthread_condattr_t *restrict attr, clockid_t *restrict clock_id);
int pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id);
```

# （线程）读写锁
* 读锁：共享锁
* 写锁：独占锁、排他锁、互斥锁
* 读写锁的效率虽然和互斥锁一样慢，甚至效率更低，但仍有适合的场景
  * 适用于读的频率远大于写的频率，提高程序并发性
```
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rwlock, const struct timespec *restrict abstime);

int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict rwlock, const struct timespec *restrict abstime);

int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

int pthread_rwlockattr_init(pthread_rwlockattr_t *attr);
int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);

int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *restrict attr, int *restrict pshared);
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, int pshared);

int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t *attr, int pref);
int pthread_rwlockattr_getkind_np(const pthread_rwlockattr_t *attr, int *pref);
```
# 自旋锁
* 自旋锁也是互斥的。
* 互斥锁、信号量、读写锁、屏障，它们的机制是当调用wait/lock函数进行上锁，如果不能上锁，则阻塞。所谓阻塞，其实就是让出CPU，让其他可执行的线程去执行，只有能够上锁时，wait/lock才被唤醒。
* 自旋锁当不能上锁时，调用lock的线程会一直占用CPU，一直去询问是否可以上锁，很容易死锁。
  * 自旋，即占用CPU一直循环。
* 自旋锁要求临界区很小（执行不会占用太多时间），一般适用于多核CPU。
```c
#include <pthread.h>

int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
int pthread_spin_destroy(pthread_spinlock_t *lock);

int pthread_spin_lock(pthread_spinlock_t *lock);
int pthread_spin_trylock(pthread_spinlock_t *lock);
int pthread_spin_unlock(pthread_spinlock_t *lock);
```

# 屏障
* 屏障就是要求多少线程满足条件之后再继续执行，统一或协调线程的执行步调。
* `pthread_join`是简易的屏障，等一个线程结束。
```c
// 初始化一个屏障，需要count个线程执行到pthread_barrier_wait函数，才能继续执行；否则，被阻塞。
int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned count);
int pthread_barrier_destroy(pthread_barrier_t *barrier);

int pthread_barrier_wait(pthread_barrier_t *barrier);

int pthread_barrierattr_init(pthread_barrierattr_t *attr);
int pthread_barrierattr_destroy(pthread_barrierattr_t *attr);

int pthread_barrierattr_setpshared(const pthread_barrierattr_t *restrict attr);
```
# 总结
| 种类   | 特点                                            | 使用场景                   |
|------|-----------------------------------------------|------------------------|
| 互斥锁  | 互斥、排他<br/>临界区代码永远只有一个线程在执行<br/>上锁解锁必须由同一个线程完成 | 互斥问题                   |
| 信号量  | 限制访问共享资源的线程数量<br/>信号量的`wait`/`post`可以不在同一个线程  | 信号量为1时，可以当做互斥锁且效率比互斥锁高 |
| 条件变量 | 需要结合互斥锁才能使用<br/>优化了等待过程                       | 生产者消费者模型、哲学家就餐模型       |
| 读写锁  | 共享-独占锁<br/>读锁是共享锁<br/>写锁时独占锁                  | 读的评率远高于写的频率<br/>提高并行性  |
| 自旋锁  | 互斥<br/>lock时，不能上锁会一直占用CPU进行上锁（不会让出CPU）        | 多核CPU<br/>临界区小         |
| 屏障   | 同步多个线程的执行进度                                   | 统筹线程的执行进度              |

## 临界区
* 临界区过大，会导致并发性降低
* 临界区过小，会导致上锁、解锁太过于频繁导致效率变低

## 锁的粒度
* 临界区的大小（上锁到解锁的范围）

## 线程安全
* 在多线程场景下，函数/容器作为公共资源被多线程访问时，能否保证数据的安全性与完整性。
* 如果能够保证，则是线程安全的，否则是线程不安全的。
* Java有两套容器，一套是线程安全的，一套是线程不安全的。C++ STL容器是线程不安全的。
* 线程安全能够保证数据的正确性与完整性，但会导致效率变低。





