#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* thread_proc(void* arg) {
    // 只能在其创建线程中才能detach
    // pthread_detach(pthread_self());

    int i;
    for (i = 0; i < 200; ++i) {
        putchar('-');
        usleep(50000);
    }
    return NULL;
}

int main(void) {
    setbuf(stdout, NULL);
    pthread_t tid;
    int err;
    if (err = pthread_create(&tid, NULL, thread_proc, NULL)) {
        fprintf(stderr, "pthread_create: %s\n", strerror(err));
        return -1;
    }
    pthread_detach(tid); // 有可能线程已经结束
    if (err = pthread_join(tid, NULL)) {
        fprintf(stderr, "pthread_join: %s\n", strerror(err));
    }

    int i;
    for (i = 0; i < 200; ++i) {
        putchar('+');
        usleep(100000);
    }


    printf("\n");

    return 0;
}
