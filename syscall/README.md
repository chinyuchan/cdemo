# syscall

```
#include <sys/syscall.h>
#include <unistd.h>

long syscall(long number, ...);
```
* 功能：`syscall()`执行一个系统调用，根据指定的参数number和所有系统调用的汇编语言接口来确定调用哪个系统调用。
* 返回值：同所执行的系统调用的返回值


## `gettid()`和`pthread_self()`的区别
Linux内核中并没有实现线程，而是glibc线程库实现的POSIX线程，每个线程有一个id，类型为`pthread_t`，由`pthread_self()`获得。
该id在各进程中是独立的，即在不同进程中，可能有相同的线程id。

* `gettid()`是Linux内核实现的函数，内核将线程也看成（轻量级的）进程(LWP)，因此`gettid()`返回的是内核管理的进程id。
    ```c
    asmlinkage long sys_gettid(void)
    {
        return current->pid;
    }
    ```
* `pthread_self()`是glibc实现的，实际上是线程描述符`pthread`指针地址
    ```c
    pthread_t __pthread_self (void)
    {
        return (pthread_t)THREAD_SELF;
    }
    
    # define THREAD_SELF \
    ({ struct pthread *__self; \
    asm ("movq %%fs:%c1,%q0" : "=r" (__self) \
    : "i" (offsetof (struct pthread, header.self))); \
    __self;})
    ```
从上面我们可以得知，`gettid()`是内核给线程（轻量级进程）分配的进程id，全局（所有进程中）唯一；`pthread_self()`是在用户态实现的，
获取的id实际上是主线程分配给子线程的线程描述符的地址而已，只是在当前进程空间中是唯一的。


