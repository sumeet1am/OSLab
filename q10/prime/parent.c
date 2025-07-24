// main.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
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
        wait(NULL);  // Wait for child to finish

        int max = atoi(argv[2]) - atoi(argv[1]) + 1;
        int shm_fd = shm_open("/prime_shm", O_RDONLY, 0666);
        int *shm_ptr = (int *) mmap(NULL, max * sizeof(int), PROT_READ, MAP_SHARED, shm_fd, 0);

        printf("Prime numbers between %s and %s are:\n", argv[1], argv[2]);
        for (int i = 0; shm_ptr[i] != -1; i++) {
            printf("%d ", shm_ptr[i]);
        }
        printf("\n");

        munmap(shm_ptr, max * sizeof(int));
        close(shm_fd);
        shm_unlink("/prime_shm");
    }

    return 0;
}
