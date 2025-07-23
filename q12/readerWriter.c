#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numreader = 0;

void *reader(void *rno);
void *writer(void *wno);

void *reader(void *rno)
{
    pthread_mutex_lock(&mutex);
    numreader++;
    if (numreader == 1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);

    printf("Reader %d: read cnt as %d\n", *((int *)rno), cnt);

    pthread_mutex_lock(&mutex);
    numreader--;
    if (numreader == 0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *writer(void *wno)
{
    sem_wait(&wrt);
    cnt *= 2;
    printf("Writer %d: modified cnt as %d\n", *((int *)wno), cnt);
    sem_post(&wrt);

    return NULL;
}


int main()
{
    pthread_t write[3], read[3];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int *a[3]; // Array of pointers to integers for thread arguments

    for (int i = 0; i < 3; i++)
    {
        a[i] = malloc(sizeof(int)); // Allocate memory for each argument
        *a[i] = i + 1;
        pthread_create(&read[i], NULL, reader, a[i]);
        pthread_create(&write[i], NULL, writer, a[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(read[i], NULL);
        pthread_join(write[i], NULL);
        free(a[i]); // Free allocated memory after threads complete
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}

