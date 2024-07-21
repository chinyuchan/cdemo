#include <stdio.h>
#include <sys/random.h>

int main(void) {

    unsigned char randomize[32] = {0};

    ssize_t retval = getrandom(randomize, sizeof(randomize), 0);
    if (retval < 0 || retval != sizeof(randomize)) {
        perror("getrandom");
        return -1;
    }

    for (int i = 0; i < sizeof(randomize); ++i) {
        printf("%02x", randomize[i]);
    }
    printf("\n");
    return 0;
}
