#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* func(void* arg) {
    char ch;
    for(ch = '0'; ch <= '9'; ++ch) {
        putchar(ch);
        fflush(stdout);
        usleep(200 * 1000);
    }
    return NULL;
}

int main(void) {
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, func, NULL);
    if (ret != 0) {
        printf("pthread_create: %s\n", strerror(ret));
        return -1;
    }

    ret = pthread_detach(tid);
    if (ret != 0) {
        printf("pthread_detach: %s\n", strerror(ret));
        return -1;
    }

    ret = pthread_join(tid, NULL);
    if(ret != 0) {
        printf("pthread_join: %s\n", strerror(ret));
    }

    getchar();

    return 0;
}
