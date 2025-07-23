// parent7b.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int shmid;
    void *shared_memory;
    char *args[] = {"fib", argv[1], NULL};

    // Create shared memory
    shmid = shmget((key_t)1122, 4096, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Create child process
    if (fork() == 0) {
        execv("./fib", args); // fib is the compiled child binary
        perror("execv failed");
        exit(1);
    } else {
        wait(NULL);
        printf("PARENT: child completed\n");

        // Attach shared memory
        shared_memory = shmat(shmid, NULL, 0666);
        printf("Parent printing:\n");
        printf("%s\n", (char *)shared_memory);

        // Cleanup
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
