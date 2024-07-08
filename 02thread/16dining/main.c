#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define DINNERS 5

typedef enum tag_State {
    THINKING,
    HUNGRY,
    EATING
} ESTAT;

pthread_mutex_t g_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_conds[DINNERS] = {
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER
};
const char* g_names[DINNERS] = {"哲学家1", "哲学家2", "哲学家3", "哲学家4", "哲学家5"};
ESTAT g_stats[DINNERS] = {THINKING, THINKING, THINKING, THINKING, THINKING};

void eat(int i) {
    int l = (i + 1) % DINNERS;
    int r = (i - 1 + DINNERS) % DINNERS;

    pthread_mutex_lock(&g_mtx);
    while(g_stats[l] == EATING || g_stats[r] == EATING) {
        g_stats[i] = HUNGRY;
        printf("%s: 快点吧，饿死了~~~\n", g_names[i]);
        pthread_cond_wait(&g_conds[i], &g_mtx);
    }
    g_stats[i] = EATING;
    printf("%s: 终于可以吃一口了！\n", g_names[i]);
    pthread_mutex_unlock(&g_mtx);

    usleep(rand() % 100 * 10000);
}

void think(int i) {
    int l = (i + 1) % DINNERS;
    int r = (i - 1 + DINNERS) % DINNERS;

    pthread_mutex_lock(&g_mtx);
    g_stats[i] = THINKING;
    printf("%s: 吃饱了，开始思考...\n", g_names[i]);
    pthread_cond_signal(&g_conds[l]);
    pthread_cond_signal(&g_conds[r]);
    pthread_mutex_unlock(&g_mtx);

    usleep(rand() % 100 * 10000);
}

void* diner(void* arg) {
    int i = (int)arg;

    while(1) {
        eat(i);
        think(i);
    }

    return NULL;
}


int main(void) {
    srand(time(NULL));
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    size_t i;
    pthread_t tid;
    for (i = 0; i < DINNERS; ++i) {
        pthread_create(&tid, &attr, diner, (void*)i);
    }

    getchar();

    return 0;
}
