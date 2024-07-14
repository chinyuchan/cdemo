#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_barrier_t barrier;

void* func(void* arg) {
    int id = (int)arg;

    printf("%d号线程开始执行了...\n", id);
    sleep(rand()%10);
    printf("%d号线程达到汇合点了\n", id);
    pthread_barrier_wait(&barrier);
    printf("汇合的线程到达指定个数，%d号线程又可以继续往前执行了\n", id);

    return NULL;
}

int main(void) {
    srand(time(NULL));
    pthread_barrier_init(&barrier, NULL, 5);
    pthread_t tids[10];
    for (int i = 0; i < 10; ++i) {
        pthread_create(&tids[i], 0, func, (void*)i);
    }

    getchar();
    pthread_barrier_destroy(&barrier);

    return 0;
}
