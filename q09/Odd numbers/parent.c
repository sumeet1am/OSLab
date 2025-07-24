// main.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n;
    printf("Enter number of odd numbers to generate: ");
    scanf("%d", &n);

    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, n * sizeof(int), 0666 | IPC_CREAT);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char arg[10];
        sprintf(arg, "%d", n);
        execl("./odd", "odd", arg, NULL);
        perror("execl failed");
        exit(1);
    } else {
        // Parent process
        wait(NULL);
        int *arr = (int *) shmat(shmid, NULL, 0);

        printf("First %d Odd Numbers:\n", n);
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        shmdt(arr);
        shmctl(shmid, IPC_RMID, NULL); // delete shared memory
    }

    return 0;
}
