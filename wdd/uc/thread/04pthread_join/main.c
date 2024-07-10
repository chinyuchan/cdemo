#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* func(void* arg) {
    int* ret = malloc(sizeof(int));
    *ret = *(int*)arg + 1;
    return ret;
}

int main(void) {
    pthread_t tid;
    int num = 123;
    int ret = pthread_create(&tid, NULL, func, &num);
    if (ret != 0) {
        printf("pthread_create: %s\n", strerror(ret));
        return -1;
    }

    // pthread_jion函数中，会解引用并赋值（*retval=xxxx），但是解引用(*NULL=xxx)就会发生非法内存访问
    // int** retval = NULL;
    // pthread_jion(tid, (void**)retval);

    int* retval = NULL;
    ret = pthread_join(tid, (void**)&retval);
    if (ret != 0) {
        printf("pthread_join: %s\n", strerror(ret));
        return -1;
    }

    printf("retval = %d\n", *retval);

    return 0;
}
