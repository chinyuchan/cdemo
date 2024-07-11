#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

volatile int g = 0;
pthread_mutex_t lock;

// 临界区过大，降低了并发
// 临界区过小，频繁地加锁解锁，降低的效率
void* func(void* arg) {
    // 锁范围扩大，运行反而快，因为不会频繁加锁解锁，相当于串行
    pthread_mutex_lock(&lock);
    for(int i = 0; i < 100000000; ++i) {
        ++g;
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void) {
    int ret = pthread_mutex_init(&lock, NULL);
    if (ret != 0) {
        printf("pthread_mutex_init: %s\n", strerror(ret));
        return -1;
    }

    pthread_t tids[2];
    int i;
    for (i = 0; i < 2; ++i) {
        ret =pthread_create(&tids[i], NULL, func, NULL);
        if (ret != 0) {
            printf("pthread_create: %s\n", strerror(ret));
            return -1;
        }
    }
    for (i = 0; i < 2; ++i) {
        ret = pthread_join(tids[i], NULL);
        if (ret != 0) {
            printf("pthread_join: %s\n", strerror(ret));
            return -1;
        }
    }

    pthread_mutex_destroy(&lock);

    printf("g = %d\n", g);

    return 0;
}

