#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

volatile int g = 0;
pthread_mutex_t lock;

void* func(void* arg) {
    for(int i = 0; i < 100000000; ++i) {
        pthread_mutex_lock(&lock);
        ++g;
        pthread_mutex_unlock(&lock);
    }
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
