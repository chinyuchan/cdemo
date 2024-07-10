#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void* func(void* arg) {
    int num = *(int*)arg;
    printf("num = %d\n", num);
    return NULL;
}

void* func2(void* arg) {
    long int x = (long int)arg;
    printf("x = %ld\n", x);
    return NULL;
}

typedef struct Student {
    int no;
    char name[64];
    char sex[8];
    int score[3];
} Student;

void* func3(void* arg) {
    // 别用指针，其他线程可能通过指针修改数据
    // Student* ps = (Student*)arg;
    // 使用局部变量
    Student s = *(Student*)arg;
    printf("no: %d, name: %s, sex: %s, score: ", s.no, s.name, s.sex);
    size_t i;
    for (i = 0; i < 3; ++i) {
        printf("%d ", s.score[i]);
    }
    printf("\n");
    return NULL;
}

int main(void) {
    pthread_t tid;
    int num = 1234;
    int ret = pthread_create(&tid, NULL, func, (void*)&num);
    if (ret != 0) {
        printf("pthread_create: %s\n", strerror(ret));
        return -1;
    }
    long int x = 9527;
    ret = pthread_create(&tid, NULL, func2, (void*)x);
    if (ret != 0) {
        printf("pthread_create: %s\n", strerror(ret));
        return -1;
    }

    Student s = {20240001, "wdd", "male", {10,20,30}};
    ret = pthread_create(&tid, NULL, func3, (void*)&s);
    if (ret != 0) {
        printf("pthread_create: %s\n", strerror(ret));
        return -1;
    }

    getchar();

    return 0;
}
