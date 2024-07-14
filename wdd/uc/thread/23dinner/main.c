#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define DINNERS_CNT 5

const char* dinners[DINNERS_CNT] = {"张三", "李四", "王五", "赵六", "钱七"};

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t conds[DINNERS_CNT] = {
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER
};

typedef enum STAT {
    THINKING, // 思考
    HUNGRY,   // 挨饿，思考后就会去就餐，但不一定能就到餐
    EATING,   // 就餐
}STAT;

STAT stats[DINNERS_CNT] = {THINKING, THINKING, THINKING, THINKING, THINKING};


void eat(int index) {
    int l = (index - 1 + DINNERS_CNT) % DINNERS_CNT;
    int r = (index + 1) % DINNERS_CNT;

    pthread_mutex_lock(&lock);
    while(stats[l] == EATING || stats[r] == EATING) {
        stats[index] = HUNGRY;
        printf("%s: 饿死了，给我吃一口吧！\n", dinners[index]);
        pthread_cond_wait(&conds[index], &lock);
    }
    stats[index] = EATING;
    printf("%s: 终于可以吃上了！\n", dinners[index]);
    pthread_mutex_unlock(&lock);

    usleep(rand()%1000*1000);
}

void think(int index) {
    long int l = (index - 1 + DINNERS_CNT) % DINNERS_CNT;
    long int r = (index + 1) % DINNERS_CNT;

    pthread_mutex_lock(&lock);
    stats[index] = THINKING;
    printf("%s: 吃饱了，放下筷子，可以安心思考了！\n", dinners[index]);
    pthread_cond_signal(&conds[l]);
    pthread_cond_signal(&conds[r]);
    pthread_mutex_unlock(&lock);

    usleep(rand()%1000*1000);
}

void* dinner(void* arg) {
    long int index = (long int)arg;
    while(1) {
        eat(index);
        think(index);
    }
    return NULL;
}

int main(void) {
    srand(time(NULL));

    pthread_t tids[5];
    for (long int i = 0; i < 5; ++i) {
        int ret = pthread_create(&tids[i], NULL, dinner, (void*)i);
        if (ret != 0) {
            printf("pthread_create: %s\n", strerror(ret));
            return -1;
        }
    }

    getchar();

    return 0;
}
