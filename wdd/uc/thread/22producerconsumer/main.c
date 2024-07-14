#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_SIZE 20
char store[MAX_SIZE] = {};
int size = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void show(const char* name, char data, const char* op) {
    printf("[");
    for (int i = 0; i < size; ++i) {
        printf("%c", store[i]);
    }
    printf("]");
    printf("%s ", op);
    printf("%s(%c)\n", name, data);
}

void* produce(void* arg) {
    const char* name = (const char*)arg;
    while(1) {
        char data = rand() % 26 + 'A';
        pthread_mutex_lock(&lock);
        while (size >= MAX_SIZE) {
            //pthread_mutex_unlock(&lock);
            //continue;
            pthread_cond_wait(&not_full, &lock);
        }
        store[size++] = data;
        show(name, data, "<-");
        pthread_cond_broadcast(&not_empty);
        pthread_mutex_unlock(&lock);
        usleep(rand()%1000*1000);
    }
    return NULL;
}

void* consume(void* arg) {
    const char* name = (const char*)arg;
    while(1) {
        pthread_mutex_lock(&lock);
        while (size == 0) {
            // pthread_mutex_unlock(&lock);
            // continue;
            pthread_cond_wait(&not_empty, &lock);
        }
        char data = store[--size];
        show(name, data, "->");
        pthread_cond_broadcast(&not_full);
        pthread_mutex_unlock(&lock);
        usleep(rand()%1000*1000);
    }
    return NULL;
}


int main(void) {
    srand(time(NULL));
    char* producers[3] = {"张三", "李四", "王五"};
    char* consumers[3] = {"赵一", "钱二", "孙九"};
    pthread_t tid;
    int i, ret;
    for (i = 0; i < 3; ++i) {
        ret = pthread_create(&tid, NULL, produce, producers[i]);
        if (ret != 0) {
            printf("pthread_create: %s\n", strerror(ret));
            return -1;
        }
        ret = pthread_create(&tid, NULL, consume, consumers[i]);
        if (ret != 0) {
            printf("pthread_create: %s\n", strerror(ret));
            return -1;
        }
    }
    getchar();
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}
