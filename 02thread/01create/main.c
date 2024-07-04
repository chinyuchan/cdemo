#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void* thread_proc(void* arg) {
    printf("%lu: %s\n", pthread_self(), (char*)arg);
    return NULL;
}

int main(void) {
    pthread_t tid;
    int err = pthread_create(&tid, NULL, thread_proc, "hello, world!");
    if (err) {
        fprintf(stderr, "pthread_create: %s\n", strerror(err));
        return -1;
    }
    printf("main thread: %lu, child thread: %lu\n", pthread_self(), tid);
    sleep(1);

    return 0;
}
