#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_STOCK 20

char g_storage[MAX_STOCK];
size_t g_stock = 0;
pthread_mutex_t g_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_cond_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t g_cond_empty = PTHREAD_COND_INITIALIZER;

void show(const char* who, const char* op, char prod) {
    printf("%s: ", who);
    size_t i;
    for (i  = 0; i < g_stock; ++i) {
        printf("%c", g_storage[i]);
    }
    printf("%s%c\n", op, prod);
}

void* producer(void* arg) {
    const char* who = arg;
    while(1) {
        pthread_mutex_lock(&g_mtx);
        if (g_stock >= MAX_STOCK) {
            printf("\033[0;32m%s: 满仓!\033[0m\n", who);
            // 线程阻塞并解锁g_mtx
            pthread_cond_wait(&g_cond_full, &g_mtx);
        }
        char prod = 'A' + rand() % 26;
        show(who, "<-", prod);
        g_storage[g_stock++] = prod;

        pthread_cond_signal(&g_cond_empty);

        pthread_mutex_unlock(&g_mtx);
        usleep(rand() % 100 * 1000);
    }
    return NULL;
}

void* consumer(void* arg) {
    const char* who = arg;
    while(1) {
        pthread_mutex_lock(&g_mtx);
        if (!g_stock) {
            printf("\033[0;31m%s: 空仓!\033[0m\n", who);
            pthread_cond_wait(&g_cond_empty, &g_mtx);
        }
        char prod = g_storage[--g_stock];
        show(who, "->", prod);

        // 唤醒一个在g_cond_full上阻塞的线程
        pthread_cond_signal(&g_cond_full);

        pthread_mutex_unlock(&g_mtx);
        usleep(rand() % 1000 * 1000);
    }
    return NULL;
}

int main(void) {
    srand(time(NULL));

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t tid;
    pthread_create(&tid, &attr, consumer, "消费者");
    pthread_create(&tid, &attr, producer, "生产者");


    getchar();

    return 0;
}
