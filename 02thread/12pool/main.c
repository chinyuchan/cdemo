#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_CONNS 5
#define MAX_USERS 50

sem_t g_sem;

void* thread_user(void* arg) {
    pthread_t tid = pthread_self();
    int sval;
    sem_getvalue(&g_sem, &sval);
    printf("%lu线程：等待数据库连接（还剩%d个空闲连接）...\n", tid, sval);
    sem_wait(&g_sem);
    sem_getvalue(&g_sem, &sval);
    printf("%lu线程：获得数据库连接（还剩%d个空闲连接）...\n", tid, sval);
    usleep(500000);
    sem_post(&g_sem);
    sem_getvalue(&g_sem, &sval);
    printf("%lu线程：释放数据库连接（还剩%d个空闲连接）...\n", tid, sval);

    return NULL;
}

int main(void) {
    sem_init(&g_sem, 0, MAX_CONNS);
    size_t i;
    pthread_t tids[MAX_USERS];
    int err;
    for (i = 0; i < MAX_USERS; ++i) {
        int err = pthread_create(&tids[i], NULL, thread_user, NULL);
        if (err) {
            fprintf(stderr, "pthread_create: %s\n", strerror(err));
            return -1;
        }
    }

    for (i = 0; i < MAX_USERS; ++i) {
        int err = pthread_join(tids[i], NULL);
        if (err) {
            fprintf(stderr, "pthread_join: %s\n", strerror(err));
            return -1;
        }
    }

    sem_destroy(&g_sem);

    return 0;
}
