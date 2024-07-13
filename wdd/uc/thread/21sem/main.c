#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int usb[3] = {};
sem_t sem;
sem_t mtx;
void* func(void* arg) {
    int ret = sem_wait(&sem);
    if (ret != 0) {
        perror("sem_wait");
        return NULL;
    }
    int i;
    sem_wait(&mtx);
    for (i = 0; i < 3; ++i) {
        if (usb[i] == 0) {
            usb[i] = 1;
            break;
        }
    }
    sem_post(&mtx);
    printf("%d线程获得了资源，资源编号为[%d]，可以开干了...\n", (int)arg, i);
    sleep(rand() % 5);
    printf("%d线程干完了，可以释放资源了...\n", (int)arg);
    usb[i] = 0;
    ret = sem_post(&sem);
    if (ret != 0) {
        perror("sem_post");
        return NULL;
    }

    return NULL;
}

int main(void) {
    srand(time(NULL));

    if (sem_init(&sem, 0, 3) != 0) {
        perror("sem_init");
        return -1;
    }
    if (sem_init(&mtx, 0, 1) != 0) {
        perror("sem_init");
        return -1;
    }

    pthread_t tids[10];
    int ret;
    for(int i  = 0; i < 10; ++i) {
        ret = pthread_create(&tids[i], 0, func, (void*)i);
        if (ret != 0) {
            printf("pthread_create: %s\n", strerror(ret));
            return -1;
        }
    }

    getchar();

    sem_destroy(&sem);
    sem_destroy(&mtx);

    return 0;
}
