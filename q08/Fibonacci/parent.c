// main.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n;
    printf("Enter number of Fibonacci terms: ");
    scanf("%d", &n);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char num[10];
        sprintf(num, "%d", n);
        execl("./fib", "fib", num, NULL);
        perror("execl failed");
        exit(1);
    } else {
        // Parent process
        wait(NULL);

        int shm_fd = shm_open("/fib_shm", O_RDONLY, 0666);
        int *fib = (int *) mmap(0, n * sizeof(int), PROT_READ, MAP_SHARED, shm_fd, 0);

        printf("Fibonacci Series:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", fib[i]);
        }
        printf("\n");

        // Cleanup
        munmap(fib, n * sizeof(int));
        close(shm_fd);
        shm_unlink("/fib_shm");
    }

    return 0;
}
