#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void elapse() {
    size_t i;
    for (i = 0; i < 800000000; ++i);
}

void* thread_proc(void* arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL); // 不接受取消
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL); // 异步取消（立即取消）

    while(1) {
        printf("thread_proc\n");
        elapse();
    }

    return NULL;
}

int main(void) {
    setbuf(stdout, NULL);
    pthread_attr_t
    printf("Press enter to cancel.\n");
    pthread_t tid;
    pthread_create(&tid, NULL, thread_proc, NULL);
    getchar();
    pthread_cancel(tid);
    printf("send cancel request, waiting for terminate.\n");
    pthread_join(tid, NULL);
    printf("thread terminate.\n");

    return 0;
}
