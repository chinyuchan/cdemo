#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void* thread_proc(void* arg) {
    size_t i;
    for (i = 0; i < 500; ++i) {
        printf("%*d\n", ((size_t)arg+1)*4, i+1);
        usleep(50000);
    }
    return NULL;
}

int main(void) {
    pthread_t tids[10];
    size_t i;
    for (i = 0; i < 10; ++i) {
        int err = pthread_create(&tids[i], NULL, thread_proc, (void*)i);
        if (err) {
            fprintf(stderr, "pthread_create: %s", strerror(err));
            return -1;
        }
    }

    getchar();
    return 0;
}
