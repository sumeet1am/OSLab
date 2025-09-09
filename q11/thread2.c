#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables shared by both threads
int sm = 0, prod = 1;

// Thread function to calculate sum of first 'n' numbers
void *sum(void *parm) {
    int i, n;
    n = atoi(parm);   // Convert string argument to integer
    printf("inside sum thread\n");
    
    for (i = 1; i <= n; i++)
        sm += i;      // Accumulate sum
    
    printf("sum thread completed\n");
    pthread_exit(NULL);   // Exit from thread
}

// Thread function to calculate factorial of 'n'
void *mul(void *parm) {
    int i, n;
    n = atoi(parm);   // Convert string argument to integer
    printf("inside mul thread\n");
    
    for (i = 2; i <= n; i++)
        prod *= i;    // Multiply sequentially
    
    printf("mul thread completed product\n");
    pthread_exit(NULL);   // Exit from thread
}

int main(int argc, char *argv[]) {
    pthread_t T1, T2;          // Thread identifiers
    pthread_attr_t attr;       // Thread attributes

    // Ensure user provided an integer argument
    if (argc != 2)
        printf("usage <filename> <value>\n");

    // Initialize thread attributes
    pthread_attr_init(&attr);

    // Create two threads: one for sum, one for factorial
    pthread_create(&T1, &attr, sum, argv[1]);
    pthread_create(&T2, &attr, mul, argv[1]);

    // Wait for both threads to finish
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    // Back to main thread: print results
    printf("inside main thread\n");
    printf("sum = %d\n", sm);
    printf("fact = %d\n", prod);

    return 0;
}
