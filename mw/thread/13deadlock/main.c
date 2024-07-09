#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t g_mtxa = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mtxb = PTHREAD_MUTEX_INITIALIZER;

void* thread_proc1(void* arg) {
    pthread_t tid = pthread_self();

    printf("%lu线程：等待A...\n", tid);
    pthread_mutex_lock(&g_mtxa);
    printf("%lu线程：获得A.\n", tid);
    usleep(100000);
    printf("%lu线程：等待B...\n", tid);
    pthread_mutex_lock(&g_mtxb);
    printf("%lu线程：获得B.\n", tid);
    // ...
    pthread_mutex_unlock(&g_mtxb);
    printf("%lu线程：释放B.\n", tid);
    pthread_mutex_unlock(&g_mtxa);
    printf("%lu线程：释放A.\n", tid);

    return NULL;
}

void* thread_proc2(void* arg) {
    pthread_t tid = pthread_self();

    printf("%lu线程：等待B...\n", tid);
    pthread_mutex_lock(&g_mtxb);
    printf("%lu线程：获得B.\n", tid);
    usleep(100000);
    printf("%lu线程：等待A...\n", tid);
    pthread_mutex_lock(&g_mtxa);
    printf("%lu线程：获得A.\n", tid);
    // ...
    pthread_mutex_unlock(&g_mtxa);
    printf("%lu线程：释放A.\n", tid);
    pthread_mutex_unlock(&g_mtxb);
    printf("%lu线程：释放B.\n", tid);

    return NULL;
}

int main(void) {
    pthread_t tid1;
    pthread_create(&tid1, NULL, thread_proc1, NULL);
    pthread_t tid2;
    pthread_create(&tid2, NULL, thread_proc2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
