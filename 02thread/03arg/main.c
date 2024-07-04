#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159

void* thread_area(void* arg) {
    double r = *(double*)arg;
    *(double*)arg = PI * r * r;
    return NULL;
}

int main(void) {
    printf("r = ");
    double r;
    scanf("%lf", &r);
    pthread_t tid;

    int err = pthread_create(&tid, NULL, thread_area, &r);
    if (err) {
        fprintf(stderr,"pthread_create: %s\n", strerror(err));
        return -1;
    }

    pthread_join(tid, NULL);

    printf("s = %g\n", r);

    return 0;
}
