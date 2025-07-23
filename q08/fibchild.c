// child7b.c
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int k = 2, n1, n2, n3;
    void *ptr;

    int shmid = shmget((key_t)1122, 4096, 0666);
    ptr = shmat(shmid, NULL, 0666);

    printf("CHILD:\n");

    int i = atoi(argv[1]); // Number of Fibonacci terms

    n1 = 0;
    n2 = 1;

    sprintf(ptr, "%d ", n1);
    ptr += strlen(ptr);
    printf("%d ", n1);

    sprintf(ptr, "%d ", n2);
    ptr += strlen(ptr);
    printf("%d ", n2);

    while (k < i) {
        n3 = n1 + n2;
        sprintf(ptr, "%d ", n3);
        ptr += strlen(ptr);
        printf("%d ", n3);
        n1 = n2;
        n2 = n3;
        k++;
    }

    printf("\n");
    return 0;
}
