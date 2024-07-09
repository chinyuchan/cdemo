# 线程管理
## 基本概念
* 线程就是程序的执行录像，即进程内部的控制序列，或者说是进程的子任务。
* 线程，轻量级，不拥有自己独立的内存资源，共享进程的代码区、数据区、堆区（没有栈区）、环境变量和命令行参数、文件描述符、信号处理函数、当前目录、用户ID和组ID等资源。
* 线程拥有自己独立的栈，因此也有独立的局部变量。
* 一个进程可以同时拥有多个线程，即同时被系统调度的多条执行路线，但至少要有一个主线程。

## 基本特点
* 线程是进程的一个实体，可作为系统独立调度和分派的基本单位。
* 线程有不同的状态，系统提供了多种线程控制原语，如创建线程、销毁线程等等。
* 线程不拥有自己的资源，只拥有从属于进程的全部资源，所有的资源分配都是面向进程的。
* 一个进程中可以有多个线程并发地运行。它们可以执行相同的代码，也可以执行不同的代码。
* 同一个进程的多个线程都在同一个地址空间内活动，因此相对于进程，现成的系统开销小，任务切换快。
* 线程间的数据交换不需要依赖类似于IPC的特殊通信机制，简单而高效。
* 每个线程拥有自己独立的线程ID、寄存器信息、函数栈、错误码和信号掩码。
* 线程之间存在优先级的差异。

## POSIX线程(pthread)
* 早期各厂商各自提供私有的线程库版本，接口和实现的差异非常大，不易于移植。
* IEEE POSIX 1003.1c(1995)标准，定义了统一的线程编程接口，遵循该标准的线程实现被统称为POSIX线程，即pthread。
* pthread包含一个头文件`pthread.h`和一个接口库`libpthread.so`。
  ```
    #include <pthread.h>
    ...
    gcc ... -lpthread
  ```
* 功能：
  * 线程管理：创建/销毁线程、分离/联合线程、设置/查询线程属性。
  * 线程同步
    * 互斥量：创建/销毁互斥量、加锁/解锁互斥量、设置/查询互斥量属性。
    * 条件变量：创建/销毁条件变量、等待/触发条件变量、设置/查询条件变量属性。

## 线程函数
### 创建线程
```c
#include <pthread.h>

int pthread_create(pthread_t *restrict thread,
                  const pthread_attr_t *restrict attr,
                  void *(*start_routine)(void *),
                  void *restrict arg);
```
* 参数
  * `thread`：线程ID，输出参数。`pthread_t`即`unsigned long int`。
  * `attr`：线程属性，NULL表示缺省属性。`pthread_attr_t`可能是整型也可能是结构，因实现而异。
  * `start_routine`：线程过程函数指针，参数和返回值的类型都是`void*`。启动线程本质上就是调用一个函数，只不过是在一个独立的线程内调用的。
  * `arg`：传递给线程过程函数的参数。线程过程函数的调用者是系统内核，而非用户代码，因此需要在创建线程时指定参数。若有多个参数，可通过传结构体指针。
* 返回值：成功返回0，失败返回错误码。
* 注意：
  * `restrict`：C99引入的编译优化指示符，提高重复解引用同一个指针的效率。解引用的目标值放到寄存器中，下次再解引用直接从寄存器取。
  * 在`pthread.h`头文件中声明的函数，通常以直接返回错误码的方式表示失败，而非以设置`errno`并返回-1。因为`errno`是全局变量。
  * `main`函数即主线程，`main`函数返回即主线程结束，主线程结束即进程结束，进程一旦结束其所有的线程即结束。
  * 应设法保证在线程过程函数执行期间，其参数所指向的目标持久有效。

### 等待线程结束
```c
#include <pthread.h>

int pthread_join(pthread_t thread, void **retval);
```
* 功能：等待thread参数所标识的线程结束。
* 返回值：成功返回0，失败返回错误码。
* 注意从线程过程函数中返回值的方法：
  * 线程过程函数将所需返回的内容放在一块内存中，返回该内存的地址，保证这块内存在函数返回，即线程结束以后依然有效。
  * 若`retval`参数为非`NULL`，则`pthread_join`函数将线程过程函数所返回的指针，拷贝到该参数所指向的内存中。
  * 若线程过程函数所返回的指针指向动态分配的内存，则还需保证在用过该内存之后释放之。

### 获取线程自身的ID
```c
#include <pthread.h>

pthread_t pthread_self(void);
```
* 返回值：成功返回0，不会失败，因为每个线程都有ID。

### 比较两个线程的ID
```c
#include <pthread.h>

int pthread_equal(pthread_t t1, pthread_t t2);
```
* 返回值：t1和t2相等返回非0，不等返回0。`pthread_t`有些实现是`unsigned long int`，有些是结构体，所以不能简单地用`==`判断。

### 终止线程
* 从线程过程函数中return。
* 调用`pthread_exit`函数。
```c
#include <pthread.h>

void pthread_exit(void *retval);
```
注意：在任何线程中调用`exit`函数都会终止整个进程。

### 线程执行轨迹
* 同步方式（非分离状态）
  * 创建线程之后，调用`pthread_join`函数等待其终止，并释放线程资源。
* 异步方式（分离状态）
  * 无需创建者等待，线程终止之后自行释放资源。
```
#include <pthread.h>

int pthread_detach(pthread_t thread);
```
* 功能：使`thread`参数所标识的线程进入分离（DETACH）状态。处于分离状态的线程终止后自动释放线程资源，且不能被`pthread_join`函数等待。
* 返回值：成功返回0，失败返回错误码。

### 取消线程
#### 向指定线程发出取消请求
```c
#include <pthread.h>

int pthread_cancel(pthread_t thread);
```
* 返回值：成功返回0，失败返回错误码。
* 注意：
  * 该函数只是向线程发出取消请求，并不等待线程终止。
  * 缺省情况下，线程收到取消请求后，并不会立即终止，而是仍继续运行，直到达到某个取消点。在取消点处，线程检查其自身是否已经被取消了，并做出相应动作。如果立即取消，可能导致数据不完整。

#### 设置调用线程的可取消状态
```c
#include <pthread.h>

int pthread_setcancelstate(int state, int *oldstate);
```
* 返回值：成功返回0，并通过`oldstate`参数输出原可取消状态（若非NULL），失败返回错误码。
* `state`取值：
  * `PTHREAD_CANCEL_ENABLE`：接受取消请求（缺省）。
  * `PTHREAD_CANCEL_DISABLE`：忽略取消请求。

#### 设置调用线程的可取消类型
```c
#include <pthread.h>

int pthread_setcanceltype(int type, int *oldtype);
```
* 返回值：成功返回0，并通过`oldtype`参数输出原可取消类型（若非NULL），失败返回错误码。
* `type`取值：
  * `PTHREAD_CANCEL_DEFERRED`：延迟取消（缺省）。被取消线程在接收到取消请求后并不立即响应，而是一直等到执行了特定的函数（取消点）之后再响应该请求。
  * `PTHREAD_CANCEL_ASYNCHRONOUS`：异步取消。被取消线程可以在任意时间取消，而不是得遇到取消点才能被取消。但是操作系统并不能保证这一点。


### 线程属性
创建线程函数的第二个参数即为线程属性，传空指针表示使用缺省属性。
```
#include <pthread.h>

int pthread_create(pthread_t *restrict thread,
                  const pthread_attr_t *restrict attr,
                  void *(*start_routine)(void *),
                  void *restrict arg);

typdef struct {
    int detachstate;
    int scope;
    int inheritsched;
    int schedpolicy;
    struct sched_param schedparam;
    size_t guardsize;
    void* stackaddr;
    size_t stacksize;
} pthread_attr_t;
```
* `detachstate`：分离状态
  * `PTHREAD_CREATE_DETACHED`：分离线程。
  * `PTHREAD_CREATE_JOINABLE`：可汇合线程（缺省）。
* `scope`：竞争范围
  * `PTHREAD_SCOPE_SYSTEM`：在系统范围内竞争资源。
  * `PTHREAD_SCOPE_PROCESS`：在进程范围内竞争资源（Linux不支持）。
* `inheritsched`：继承特性
  * `PTHREAD_INHERIT_SCHED`：调度属性从创建线程者继承。
  * `PTHREAD_EXPLICIT_SCHED`：调度属性由后面两个成员决定。
* `schedpolocy`：调度策略
  * `SCHED_FIFO`：先进先出策略。
    * 没有时间片。
    * 一个FIFO线程会持续运行，直到阻塞或有更高优先级线程就绪。
    * 当FIFO线程阻塞时，系统将其移出就绪队列，待其恢复时再加到同优先级就绪队列的末尾。
    * 当FIFO线程被高优先级线程抢占时，它在就绪队列中的位置不变。因此一旦高优先级线程终止或阻塞，被抢占的FIFO线程将会立即继续运行。
  * `SCHED_RR`：轮转策略。
    * 给每个RR线程分配一个时间片，一旦RR线程的时间片耗尽，系统即将其移到就绪队列的末尾。
  * `SCHED_OTHER`：普通策略。
    * 静态优先级为80。
    * 任何就绪的FIFO线程或RR线程都会抢占此类线程。
* `schedparam`：调度参数。
  ```
  struct sched_param {
      int sched_priority; // 静态优先级，值越小，优先级越高
  };
  ```
* `guardsize`：栈尾警戒区大小（字节），缺省为一页（4096）字节。允许一定范围的栈溢出，防止破坏其他数据。
* `stackaddr`：栈地址。
* `stacksize`：栈大小（字节）。

不要手工读写该结构体，而应调用`pthread_attr_set/get`t函数设置/获取具体属性。


#### 设置线程属性
* 第一步，初始化线程结构体属性
  ```c
  int pthread_attr_init(pthread_attr_t* attr);
  ```
* 第二步，设置具体的线程属性
  ```c
  int pthread_attr_setdetachstate(pthread_attr_t* attr, int detachstate);
  int pthread_attr_setscope(pthread_attr_t* attr, int scope);
  int pthread_attr_setinheritsched(pthread_attr_t* attr, int inheritsched);
  int pthread_attr_setschedpolicy(pthread_attr_t* attr, int policy);
  int pthread_attr_setschedparam(pthread_attr_t* attr, const struct sched_param* param);
  int pthread_attr_setguardsize(pthread_attr_t* attr, int guardsize);
  int pthread_attr_setstackaddr(pthread_attr_t* attr, void* stackaddr);
  int pthread_attr_setstacksize(pthread_attr_t* attr, size_t stacksize);
  int pthread_attr_setstack(pthread_attr_t* attr, void* stackaddr, size_t stacksize);
  ```
* 第三步，以设置好的线程属性结构体为参数创建线程
* 第四步，销毁线程属性结构体
  ```c
  int pthread_attr_destroy(pthread_attr_t* attr);
  ```
#### 获取线程属性
* 第一步，获取线程属性结构体
  ```c
  int pthread_getattr_np(pthread_t thread, pthread_attr_t* attr);
  ```
* 第二步，获取具体线程属性
  ```c
  int pthread_attr_setdetachstate(pthread_attr_t* attr, int detachstate);
  int pthread_attr_setscope(pthread_attr_t* attr, int scope);
  int pthread_attr_setinheritsched(pthread_attr_t* attr,  int inheritsched);
  int pthread_attr_setschedpolicy(pthread_attr_t* attr, int policy);
  int pthread_attr_getschedparam(pthread_attr_t* attr, struct sched_param* param);
  int pthread_attr_setguardsize(pthread_attr_t* attr, size_t guardsize);
  int pthread_attr_setstackaddr(pthread_attr_t* attr, void *stackaddr);
  int pthread_attr_setstacksize(pthread_attr_t* attr, size_t stacksize);
  int pthread_attr_setstack(pthread_attr_t* attr, void stackaddr, size_t stacksize);
  ```
以上所有函数成功返回0，失败返回错误码。


# 线程同步 
## 竞争与同步
当多个线程同时访问其所共享的进程资源时，需要相互协调，以防止出现数据不一致、不完整的问题，这就要线程同步。

## 互斥锁
```
线程1：
    加锁互斥锁
    锁区代码块
    解锁互斥锁
线程2：
    加锁互斥锁
    锁区代码块
    解锁互斥锁
```
锁区（临界区）代码块中的代码在任何时候最多只被一个线程执行。任何时刻只会有一个线程对特定的互斥锁加锁成功，其他试图对其加锁的线程会在加锁函数的阻塞中等待，
直到该互斥锁的持有者将其解锁。对特定互斥锁加锁成功的线程，可以通过调用解锁函数将其解锁，那些阻塞于该互斥锁加锁的线程中的一个会被唤醒，得到该互斥锁，
并从加锁函数中返回，执行锁区代码。
```c
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; // 静态方式初始化

pthread_mutex_t m;
pthread_mutext_init(&m, NULL);  // 动态方式初始化

pthread_mutex_lock(&m);    // 加锁
// ...
pthread_mutex_unlock(&m);  // 解锁
pthread_mutex_destroy(&m); // 销毁
```

## 信号量
信号量是一个计数器，用于控制访问有限资源的线程数。

### 创建信号量
```c
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
```
* `sem`：信号量ID，输出参数。
* `pshared`：一般取0，表示调用线程的信号量。非0表示信号量可以共享内存的方式，为多个线程所共享（Linux暂不支持）。
* `value`：信号量初值。

```c
// 信号量减1，不够减就阻塞
int sem_wait(sem_t* sem);

// 信号量减1，不够减即返回-1，errno为EAGAIN
int sem_trywait(sem_t* sem);

// 信号量减1，不够减就阻塞，直到abs_timeout超时返回-1，errno为ETIMEDOUT
int sem_timedwait(sem_t* sem, const struct timespec *restrict abs_timeout);

struct timespec {
    time_t tv_sec; // seconds
    long tv_nsec;  // Nanoseconds [0, 999999999]
};

// 信号量加1
int sem_post(sem_t* sem);

// 销毁信号量
int sem_destroy(sem_t* sem);
```
注意：
* 信号量API没有声明在`pthread.h`中，而是声明在`semaphore.h`中，失败也不返回错误码，而是返回-1，同时设置`errno`。
* 互斥量任何时候都只允许一个线程访问共享资源，而信号量则允许最多`value`个线程同时访问共享资源，当`value`为1时，与互斥量等价。


## 条件变量

### 生产者消费者模型
* 生产者：产生数据的线程。
* 消费者：使用数据的线程。
* 通过缓冲区隔离生产者和消费者，与二者直连相比，避免相互等待，提高运行效率。
* 生产快于消费，缓冲区满，撑死。
* 消费快于生产，缓冲区空，饿死。
* 条件变量可以让调用线程在满足特定条件的情况下暂停。

### 初始化条件变量
```c
#include <pthread.h>

// 初始化后，是条件不满足状态
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);
```

### 等待条件变量
```c
#include <pthread.h>

// 等待条件变量满足条件
// 使调用线程睡入条件变量，同时释放互斥锁mutex
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);

int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);

struct timespec {
    time_t tv_sec;  // seconds
    long   tv_nsec; // nanoseconds [0 - 999999999]
};
```

### 唤醒线程
```c
#include <pthread.h>

// 从条件变量cond中唤醒一个线程，令其重新获得原先的互斥锁
int pthread_cond_signal(pthread_cond_t *cond);

// 从条件变量cond中唤醒所有线程
int pthread_cond_broadcast(pthread_cond_t *cond);
```
注意：
* 被醒出的线程此刻将从pthread_cond_wait函数中返回，但如果该线程无法获得原先的锁，则会继续阻塞在加锁上。
* 当一个线程被从条件变量中换醒以后，导致其睡入条件变量的条件可能还需再判断一次，因此随时有可能被其他线程修改。

### 销毁条件变量
```c
#include <pthread.h>

int pthread_cond_destroy(pthread_cond_t *cond);
```





































