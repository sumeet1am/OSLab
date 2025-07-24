// main.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./main M N\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execl("./prime", "prime", argv[1], argv[2], NULL);
        perror("execl failed");
        exit(1);
    } else {
        // Parent process
        wait(NULL);

        int shm_fd = shm_open("/prime_shm", O_RDONLY, 0666);
        int size = 1024;  // should be large enough to hold all primes
        int *shm_ptr = (int *) mmap(0, size, PROT_READ, MAP_SHARED, shm_fd, 0);

        printf("Prime numbers between %s and %s:\n", argv[1], argv[2]);
        for (int i = 0; shm_ptr[i] != -1; i++) {
            printf("%d ", shm_ptr[i]);
        }
        printf("\n");

        // Cleanup
        munmap(shm_ptr, size);
        close(shm_fd);
        shm_unlink("/prime_shm");
    }

    return 0;
}
