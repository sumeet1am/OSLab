#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sm = 0, prod = 1;

void *sum(void *parm) {
    int i, n;
    n = atoi(parm);
    printf("inside sum thread\n");
    for (i = 1; i <= n; i++)
        sm += i;
    printf("sum thread completed\n");
    pthread_exit(NULL);
}

void *mul(void *parm) {
    int i, n;
    n = atoi(parm);
    printf("inside mul thread\n");
    for (i = 2; i <= n; i++)
        prod *= i;
    printf("mul thread completed product\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t T1, T2;
    pthread_attr_t attr;

    if (argc != 2)
        printf("usage <filename> <value>");

    pthread_attr_init(&attr);
    pthread_create(&T1, &attr, sum, argv[1]);
    pthread_create(&T2, &attr, mul, argv[1]);
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    printf("inside main thread\n");
    printf("sum = %d\n", sm);
    printf("fact = %d\n", prod);
}
