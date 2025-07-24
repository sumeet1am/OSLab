#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

void generateFibonacci(int *fib, int n) {
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, n * sizeof(int), 0666 | IPC_CREAT);
    int *shmarr = (int *) shmat(shmid, (void *)0, 0);

    generateFibonacci(shmarr, n);

    shmdt(shmarr);

    return 0;
}
