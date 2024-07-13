#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

volatile int g = 0;
sem_t sem;

void* func1(void* arg) {
    for (int i = 0; i < 10000000; ++i) {
        sem_wait(&sem); // lock
        ++g;
        sem_post(&sem); // unlock
    }
    return NULL;
}

void* func2(void* arg) {
    for (int i=0; i < 10000000; ++i) {
        sem_wait(&sem);
        ++g;
        sem_post(&sem);
    }
    return NULL;
}


int main(void) {
    if (sem_init(&sem, 0, 1)!=0) {
        perror("sem_init");
        return -1;
    }

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, func1, NULL);
    pthread_create(&tid2, NULL, func2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&sem);


    printf("g=%d\n", g);

    return 0;
}
