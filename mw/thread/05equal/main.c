#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t gmain;
void* ismain(void* arg) {
    //if (pthread_self() == gmain) {
    if (pthread_equal(pthread_self(), gmain)) {
        printf("main thread\n");
    }
    else {
        printf("child thread\n");
    }

    return NULL;
}

int main(void) {
    gmain = pthread_self();

    pthread_t tid;
    int err;
    if (err = pthread_create(&tid, NULL, ismain, NULL)) {
        fprintf(stderr, "pthread_create: %s\n", strerror(err));
        return -1;
    }

    ismain(NULL);

    if(err = pthread_join(tid, NULL)) {
        fprintf(stderr, "pthread_join: %s\n", strerror(err));
        return -1;
    }

    return 0;
}
