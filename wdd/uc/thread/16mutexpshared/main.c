#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock;

int main(void) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    int ret = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    if (ret !=0) {
        printf("pthread_mutexattr_setpshared: %s\n", strerror(ret));
        return -1;
    }
    ret = pthread_mutex_init(&lock, &attr);
    if (ret != 0) {
        printf("pthread_mutex_init: %s\n", strerror(ret));
        return -1;
    }

    pid_t pid = vfork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        int ret = pthread_mutex_lock(&lock);
        if (ret != 0) {
            printf("pthread_mutex_lock: %s\n", strerror(ret));
            exit(-1);
        }
        printf("%d进程加锁成功\n", getpid());
        sleep(5);
        ret = pthread_mutex_unlock(&lock);
        if (ret != 0) {
            printf("pthread_mutex_unlock: %s\n", strerror(ret));
            exit(-1);
        }
        printf("%d进程解锁成功\n", getpid());
        exit(0);
    }
    else {
        int ret = pthread_mutex_lock(&lock);
        if (ret != 0) {
            printf("pthread_mutex_lock: %s\n", strerror(ret));
            exit(-1);
        }
        printf("%d进程加锁成功\n", getpid());
        sleep(5);
        ret = pthread_mutex_unlock(&lock);
        if (ret != 0) {
            printf("pthread_mutex_unlock: %s\n", strerror(ret));
            exit(-1);
        }
        printf("%d进程解锁成功\n", getpid());
    }

    pthread_mutexattr_destroy(&attr);
    pthread_mutex_destroy(&lock);

    return 0;
}
