#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>


void* func1(void* arg) {
    char ch = 'A';
    for(; ch <= 'Z'; ++ch) {
        printf("%c", ch);
        fflush(stdout);
        usleep(100*1000);
    }
    return NULL;
}

void* func2(void* arg) {
    char ch = 48;
    for (; ch <= 64; ++ch) {
        printf("%c", ch);
        fflush(stdout);
        usleep(100*1000);
    }

    return NULL;
}

int main(void) {
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, func1, NULL);
    if (ret != 0) {
        printf("pthrad_create: %s\n", strerror(ret));
        return -1;
    }

    ret = pthread_create(&tid, NULL, func2, NULL);
    if (ret != 0) {
        printf("pthrad_create: %s\n", strerror(ret));
        return -1;
    }

    char ch = 'a';
    for(; ch <= 'z'; ++ch) {
        printf("%c", ch);
        fflush(stdout);
        usleep(100*1000);
    }
    printf("\n");

    return 0;
}
