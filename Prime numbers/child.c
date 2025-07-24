// prime.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i*i <= num; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./prime M N\n");
        return 1;
    }

    int M = atoi(argv[1]);
    int N = atoi(argv[2]);

    int max_possible = N - M + 1; // worst case: all numbers are prime
    int shm_fd = shm_open("/prime_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, max_possible * sizeof(int));

    int *shm_ptr = (int *) mmap(0, max_possible * sizeof(int), PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int index = 0;
    for (int i = M; i <= N; i++) {
        if (is_prime(i)) {
            shm_ptr[index++] = i;
        }
    }

    shm_ptr[index] = -1; // Sentinel to mark end
    munmap(shm_ptr, max_possible * sizeof(int));
    close(shm_fd);

    return 0;
}
