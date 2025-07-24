#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int n;
    printf("Enter number of Fibonacci terms: ");
    scanf("%d", &n);

    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, n * sizeof(int), 0666 | IPC_CREAT);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process executes Fibonacci logic
        char n_str[10];
        sprintf(n_str, "%d", n);
        execl("./fib", "fib", n_str, NULL);
        perror("execl failed");
        exit(1);
    } else {
        // Parent waits for child
        wait(NULL);

        int *shmarr = (int *) shmat(shmid, (void *)0, 0);
        printf("Fibonacci Series:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", shmarr[i]);
        }
        printf("\n");

        shmdt(shmarr);
        shmctl(shmid, IPC_RMID, NULL); // remove shared memory
    }

    return 0;
}
