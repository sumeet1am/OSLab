// prime.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./prime M N\n");
        exit(1);
    }

    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int max = N - M + 1;

    int shm_fd = shm_open("/prime_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, max * sizeof(int));
    int *shm_ptr = (int *) mmap(NULL, max * sizeof(int), PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int index = 0;
    for (int i = M; i <= N; i++) {
        if (is_prime(i)) {
            shm_ptr[index++] = i;
        }
    }
    shm_ptr[index] = -1;  // Sentinel to indicate end

    munmap(shm_ptr, max * sizeof(int));
    close(shm_fd);

    return 0;
}
