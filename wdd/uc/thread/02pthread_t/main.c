#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t main_id;

void* func(void* arg) {
    if (pthread_equal(main_id, pthread_self())) {
        printf("主线程调用, ID=%lu\n", pthread_self());
    }
    else {
        printf("子线程执行, ID=%lu\n", pthread_self());
    }
    return NULL;
}

int main(void) {
    main_id = pthread_self();
    printf("主线程ID: %lu\n", main_id);

    pthread_t tid;
    int ret = pthread_create(&tid, NULL, func, NULL);
    if (ret != 0) {
        printf("pthread_create: %s\n", strerror(ret));
        return -1;
    }
    printf("子线程ID: %lu\n",tid);

    func(NULL);

    getchar();

    return 0;
}
