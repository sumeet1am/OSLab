// fib.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./fib <number_of_terms>\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int shm_fd = shm_open("/fib_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, n * sizeof(int));

    int *fib = (int *) mmap(0, n * sizeof(int), PROT_WRITE, MAP_SHARED, shm_fd, 0);

    fib[0] = 0;
    if (n > 1) fib[1] = 1;
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    munmap(fib, n * sizeof(int));
    close(shm_fd);

    return 0;
}
