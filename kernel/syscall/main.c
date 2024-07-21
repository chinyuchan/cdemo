#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
    pid_t pid = syscall(SYS_getpid);
    pid_t tid = syscall(SYS_gettid);
    printf("pid = %d, tid = %d\n", pid, tid);

    int ret = 0;
    if ((ret = syscall(SYS_tgkill, pid, tid, SIGTERM)) == -1) {
        perror("syscall_tgkill");
        return -1;
    }
    printf("ret = %d\n", ret);

    return 0;
}
