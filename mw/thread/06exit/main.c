#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PI 3.14159

void* thread_area(void* arg) {
    double r = *(double*)arg;
    double* ps = malloc(sizeof(double));
    *ps = PI * r * r;
    pthread_exit(ps);
}

int main(void) {
    printf("r = ");
    double r;
    scanf("%lf", &r);
    pthread_t tid;
    int err;
    if (err = pthread_create(&tid, NULL, thread_area, &r)) {
        fprintf(stderr, "pthread_create: %s\n", strerror(err));
        return -1;
    }
    double* s;
    if (err = pthread_join(tid, (void**)&s)) {
        fprintf(stderr, "pthread_join: %s\n", strerror(err));
        return -1;
    }

    printf("s = %g\n", *s);
    free(s);

    return 0;
}
