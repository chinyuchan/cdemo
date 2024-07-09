#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

unsigned int g_cn = 0;
pthread_mutex_t g_mtx = PTHREAD_MUTEX_INITIALIZER;

void* thread_add(void* arg) {
    unsigned int i;
    for (i = 0; i < 10000000; ++i) {
        pthread_mutex_lock(&g_mtx);
        ++g_cn; // 不是原子操作，有多个操作，可打断
        pthread_mutex_unlock(&g_mtx);
    }
    return NULL;
}

void* thread_sub(void* arg) {
    unsigned int i;
    for (i = 0; i < 10000000; ++i) {
        pthread_mutex_lock(&g_mtx);
        --g_cn; // 不是原子操作，有多个操作，可打断
        pthread_mutex_unlock(&g_mtx);
    }
    return NULL;
}

int main(void) {
    // pthread_mutex_init(&g_mtx, NULL);
    pthread_t tids[2];
    int i;
    // for(i = 0; i < 2; ++i) {
    //     pthread_create(&tids[i], NULL, thread_add, NULL);
    // }
    pthread_create(&tids[0], NULL, thread_add, NULL);
    pthread_create(&tids[1], NULL, thread_sub, NULL);
    for (i = 0; i < 2; ++i) {
        pthread_join(tids[i], NULL);
    }
    pthread_mutex_destroy(&g_mtx);

    printf("g_cn = %u\n", g_cn);

    return 0;
}

