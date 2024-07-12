#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t lock;
pthread_mutexattr_t attr;

void* func1(void* arg) {
    pthread_t tid = pthread_self();
    printf("%ld线程.\n", tid);
    int ret = pthread_mutex_lock(&lock);
    if (ret != 0) {
        printf("%ld线程, pthread_mutex_lock: %s\n", tid, strerror(ret));
        return NULL;
    }
    printf("%ld线程上锁成功!\n", tid);

    return NULL;
}

void* func2(void* arg) {
    pthread_t tid = pthread_self();
    printf("%ld线程.\n", tid);
    sleep(1);
    int ret = pthread_mutex_lock(&lock);
    if (ret != 0) {
        printf("%ld线程, pthread_mutex_lock: %s\n", tid, strerror(ret));
        return NULL;
    }
    printf("%ld线程上锁成功!\n", tid);
    pthread_mutex_lock(&lock);

    return NULL;
}

int main(void) {
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_STALLED_NP);
    pthread_mutex_init(&lock, &attr);

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, func1, NULL);
    pthread_create(&tid2, NULL, func2, NULL);

    if (pthread_join(tid1, NULL) != 0) {
        printf("%ld线程出错了!\n", tid1);
    }
    else {
        printf("%ld线程退出了!\n", tid1);
    }
    if (pthread_join(tid2, NULL) != 0) {
        printf("%ld线程出错了!\n", tid2);
    }
    else {
        printf("%ld线程退出了!\n", tid2);
    }
    return 0;
}
