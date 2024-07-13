#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

volatile int g = 0;
sem_t* sem = NULL;

void* func1(void* arg) {
    for (int i = 0; i < 10000000; ++i) {
        sem_wait(sem); // lock
        ++g;
        sem_post(sem); // unlock
    }
    return NULL;
}

void* func2(void* arg) {
    for (int i=0; i < 10000000; ++i) {
        sem_wait(sem);
        ++g;
        sem_post(sem);
    }
    return NULL;
}


int main(void) {
    sem = sem_open("mysem", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        return -1;
    }

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, func1, NULL);
    pthread_create(&tid2, NULL, func2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_close(sem);
    sem_unlink("mysem");

    printf("g=%d\n", g);

    return 0;
}
