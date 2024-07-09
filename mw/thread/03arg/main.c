#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159

typedef struct tag_Pyth {
    double a;
    double b;
    double c;
}PYTH, *LPPYTH;

void* thread_area(void* arg) {
    double r = *(double*)arg;
    *(double*)arg = PI * r * r;
    return NULL;
}

void* thread_pyth(void* arg) {
    LPPYTH pyth = (LPPYTH)arg;
    pyth->c = sqrt(pyth->a * pyth->a + pyth->b * pyth->b);
    return NULL;
}

void* thread_show(void* arg) {
    sleep(1);
    printf("n = %d\n", *(int*)arg);
    return NULL;
}

int main(void) {
    printf("r = ");
    double r;
    scanf("%lf", &r);
    pthread_t tid;

    int err = pthread_create(&tid, NULL, thread_area, &r);
    if (err) {
        fprintf(stderr,"pthread_create1: %s\n", strerror(err));
        return -1;
    }

    if (err = pthread_join(tid, NULL)) {
        fprintf(stderr, "pthread_join1: %s", strerror(err));
        return -1;
    }

    printf("s = %g\n", r);
    PYTH pyth;
    printf("a = ");
    scanf("%lf", &pyth.a);
    printf("b = ");
    scanf("%lf", &pyth.b);

    if (err = pthread_create(&tid, NULL, thread_pyth, &pyth)) {
        fprintf(stderr,"pthread_create2: %s\n", strerror(err));
        return -1;
    }
    if (err = pthread_join(tid, NULL)) {
        fprintf(stderr, "pthread_join2: %s\n", strerror(err));
        return -1;
    }
    printf("c = %g\n", pyth.c);

    int* n = malloc(sizeof(int));
    *n = 1234;
    if (err = pthread_create(&tid, NULL, thread_show, n)) {
        fprintf(stderr, "pthread_create: %s\n", strerror(err));
        return -1;
    }
    if (err = pthread_join(tid, NULL)) {
        fprintf(stderr, "pthread_join: %s\n", strerror(err));
        return -1;
    }

    free(n);

    return 0;
}
