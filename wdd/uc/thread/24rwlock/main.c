#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t rwlock;

volatile int g = 0;

void* change(void* arg) {
    while(1) {
        pthread_rwlock_wrlock(&rwlock);
        g = rand() % 100;
        sleep(3);
        pthread_rwlock_unlock(&rwlock);
        sleep(10);
    }

    return NULL;
}

void* show(void* arg) {
    int id = (int)arg;
    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("%d号线程：g = %d\n", id, g);
        sleep(1);
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }

    return NULL;
}

int main(void) {
    srand(time(NULL));

    pthread_rwlock_init(&rwlock, NULL);
    pthread_t tid;
    pthread_create(&tid, NULL, change, NULL);
    for (int i = 0; i < 5; ++i) {
        pthread_create(&tid, NULL, show, (void*)i);
    }

    getchar();

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
