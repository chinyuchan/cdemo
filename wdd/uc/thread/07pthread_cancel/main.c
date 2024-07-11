#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MC_SECONDS 300*1000

void* func1(void* arg) {
    char ch = 'A';
    for(; ch <= 'Z'; ++ch) {
        putchar(ch);
        fflush(stdout);
        usleep(MC_SECONDS);
    }
    return NULL;
}

void* func2(void* arg) {
    int ret = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    if (ret != 0) {
        printf("pthread_setcancelstate: %s\n", strerror(ret));
    }
    char ch = 'a';
    for(; ch <= 'z'; ++ch) {
        putchar(ch);
        fflush(stdout);
        usleep(MC_SECONDS);
    }
    return NULL;
}

void* func3(void* arg) {
    char ch = '1';
    for(; ch <= '9'; ++ch) {
        putchar(ch);
        fflush(stdout);
        usleep(MC_SECONDS);
    }
    return NULL;
}

void error(int err) {
    printf("%s\n", strerror(err));
    exit(0);
}

int main(void) {
    fflush(stdout);
    pthread_t tids[3];
    void*(*funcs[3])(void*) = {func1, func2, func3};
    int i;
    for (i = 0; i < 3; ++i) {
        int ret = pthread_create(&tids[i], NULL, funcs[i], NULL);
        if (ret != 0) {
            printf("pthread_create: %s\n", strerror(ret));
            return -1;
        }
    }
    int ret;
     ret = pthread_detach(tids[0]);
     if (ret != 0) {
         error(ret);
         return -1;
     }
     ret = pthread_detach(tids[2]);
     if (ret != 0) {
         error(ret);
         return -1;
     }
    printf("enter to cancel all thread...\n");
    getchar();
     for (i = 0; i < 3; ++i) {
         ret = pthread_cancel(tids[i]);
         if (ret != 0) {
             error(ret);
         }
     }
    getchar();

    return 0;
}
