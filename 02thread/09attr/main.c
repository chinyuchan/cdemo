// 先定义宏_GNU_SOURCE，因为pthread_getattr_np属于GNU扩展接口，而非POSIX标准
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int printaddrs(pthread_attr_t* attr) {
    printf("-----------线程属性-----------\n");
    int detachstate;
    pthread_attr_getdetachstate(attr, &detachstate);
    printf("分离状态: %s\n", detachstate == PTHREAD_CREATE_DETACHED ? "分离线程" : detachstate == PTHREAD_CREATE_JOINABLE ? "可汇合线程" : "未知");

    int scope;
    pthread_attr_getscope(attr, &scope);
    printf("竞争范围: %s\n", scope == PTHREAD_SCOPE_SYSTEM ? "系统级竞争": scope == PTHREAD_SCOPE_PROCESS ? "进程级竞争" : "未知");

    int inheritsched;
    pthread_attr_getinheritsched(attr, &inheritsched);
    printf("继承特性: %s\n", inheritsched == PTHREAD_INHERIT_SCHED ? "继承调用属性": inheritsched == PTHREAD_EXPLICIT_SCHED ? "显式调用属性" : "未知");

    int policy;
    pthread_attr_getschedpolicy(attr, &policy);
    printf("调度策略: %s\n", policy == SCHED_OTHER ? "普通策略": policy == SCHED_FIFO ? "先进先出策略" : policy == SCHED_RR ? "轮转策略" : "未知");

    struct sched_param schedparam;
    pthread_attr_getschedparam(attr, &schedparam);
    printf("调度优先级: %d\n", schedparam.sched_priority);

    size_t guardsize;
    pthread_attr_getguardsize(attr, &guardsize);
    printf("栈尾警戒区大小: %lu 字节\n", guardsize);

    void* stackaddr;
    size_t stacksize;
    pthread_attr_getstack(attr, &stackaddr, &stacksize);
    printf("栈地址: %p\n", stackaddr);
    printf("栈大小: %lu 字节\n", stacksize);
    printf("--------------------------\n");
}

void* thread_proc(void* arg) {
    pthread_attr_t attr;
    pthread_getattr_np(pthread_self(), &attr);
    printaddrs(&attr);
    return NULL;
}

int main(void) {
    pthread_attr_t attr;
    pthread_getattr_np(pthread_self(), &attr);
    printaddrs(&attr);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    void* stackaddr = malloc(4096 * 10);
    printf("stackaddr = %p\n", stackaddr);
    pthread_attr_setstack(&attr, stackaddr, 4096 * 10);
    pthread_t tid;
    pthread_create(&tid, &attr, thread_proc, NULL);
    pthread_attr_destroy(&attr);

    printf("pid = %d\n", getpid());
    getchar();

    return 0;
}
