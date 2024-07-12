#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock;

int main(void) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK_NP);
    pthread_mutex_init(&lock, &attr);

    int ret = pthread_mutex_lock(&lock);
    if (ret == 0) {
        printf("第一次上锁成功！\n");
    }
    else {
        printf("第一次上锁失败！: %s\n", strerror(ret));
        return -1;
    }
    ret = pthread_mutex_lock(&lock);
    if (ret == 0) {
        printf("第二次上锁成功！\n");
    }
    else {
        printf("第二次上锁失败！: %s\n", strerror(ret));
        return -1;
    }


    return 0;
}
