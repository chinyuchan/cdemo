#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* func(void* arg) {
    char ch='A';
    for(; ch <= 'Z'; ++ch) {
        putchar(ch);
        fflush(stdout);
        usleep(200 * 1000);
    }
    return NULL;
}

int main(void) {
    pthread_attr_t attr;
    int ret = pthread_attr_init(&attr);
    if (ret != 0) {
        printf("pthread_init: %s\n", strerror(ret));
        return -1;
    }
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (ret != 0) {
        printf("pthread_attr_setdetachstate: %s\n", strerror(ret));
        return -1;
    }
    pthread_t tid;
    ret = pthread_create(&tid, &attr, func, NULL);
    if (ret != 0) {
        printf("pthread_create: %s\n", strerror(ret));
        return -1;
    }
    ret = pthread_join(tid, NULL);
    if (ret != 0) {
        printf("pthread_join: %s\n", strerror(ret));
    }

    pthread_attr_destroy(&attr);

    getchar();

    return 0;
}
