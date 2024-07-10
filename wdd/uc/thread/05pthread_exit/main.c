#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* func(void* arg) {
    // 在任何线程中调用exit函数，都会终止整个进程
    //exit(0);
    int* n = malloc(sizeof(int));
    *n = *(int*)arg + 1;
    // 在任何位置调用pthread_exit函数，都会终止整个线程
    pthread_exit(n);
}

int main(void) {
    int n = 123;
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, func, &n);
    if (ret != 0) {
        printf("pthread_create: %s\n", strerror(ret));
        return -1;
    }

    int* retval = NULL;
    ret = pthread_join(tid, (void**)&retval);
    if (ret != 0) {
        printf("pthread_join: %s\n", strerror(ret));
        return -1;
    }

    printf("子线程结束, retval = %d\n", *retval);

    return 0;
}
