// odd.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./odd <number_of_terms>\n");
        return 1;
    }

    int n = atoi(argv[1]);
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, n * sizeof(int), 0666 | IPC_CREAT);
    int *arr = (int *) shmat(shmid, NULL, 0);

    for (int i = 0, num = 1; i < n; i++, num += 2) {
        arr[i] = num;
    }

    shmdt(arr);
    return 0;
}
