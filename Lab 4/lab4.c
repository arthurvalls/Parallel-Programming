#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

long long int s = 0, N; // numero de elementos do vetor
int nthreads;           // numero de threads
int *vetor;             // vetor de entrada com dimensao N
double concurrentTime, sequentialTime;
pthread_mutex_t mutex; // variavel de mutex para exclusao mutua

int isPrime(int number)
{
    double root = sqrt(number);

    if (number < 2) return 0;

    for (int i = 2; i <= root ; i++) if (number % i == 0) return 0;
    return 1;
}


// funcao executada pelas threads
void *ExecutaTarefa(void *arg)
{
    
    double *localArray = (double *)arg;

    while (s < N)
    {
        pthread_mutex_lock(&mutex);
        s++;
        pthread_mutex_unlock(&mutex);
        if (isPrime(vetor[s]))
            localArray[s] = sqrt(vetor[s]);
        else
            localArray[s] = vetor[s];
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t *tid;
    int t;
    double start, end;
    //double *localArray;
    double *sequentialArray, *concurrentArray;

    if (argc < 3)
    {
        fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
        return 1;
    }
    N = atoi(argv[1]);
    nthreads = atoi(argv[2]);
    // aloca o vetor de entrada
    vetor = (int *)malloc(sizeof(int) * N);
    if (vetor == NULL)
    {
        fprintf(stderr, "ERRO--malloc\n");
        return 2;
    }
    // preenche o vetor de entrada

    sequentialArray = (double *)malloc(sizeof(double) * N);

    srand(time(NULL));
    for (long int i = 0; i < N; i++)
        vetor[i] = rand() % N;

    // sequencial
    GET_TIME(start);

    for (long long int i = 0; i < N; i++)
    {
        if (isPrime(vetor[i]))
            sequentialArray[i] = sqrt(vetor[i]);
        else
            sequentialArray[i] = vetor[i];
    }

    GET_TIME(end);
    sequentialTime = end - start;
    printf("Tempo sequencial = %lf\n", sequentialTime);

    concurrentArray = (double *)malloc(sizeof(double) * N);
    
    GET_TIME(start);
    tid = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
    if (tid == NULL)
    {
        fprintf(stderr, "ERRO--malloc\n");
        return 2;
    }
    pthread_mutex_init(&mutex, NULL);
    for (t = 0; t < nthreads; t++)
    {
        
        if (pthread_create(&tid[t], NULL, ExecutaTarefa, (void *)concurrentArray))
        {
            printf("--ERRO: pthread_create()\n");
            exit(-1);
        }
    }
    //--espera todas as threads terminarem
    for (t = 0; t < nthreads; t++)
    {
        if (pthread_join(tid[t], NULL))
        {
            printf("--ERRO: pthread_join() \n");
            exit(-1);
        }
    }
    pthread_mutex_destroy(&mutex);
    GET_TIME(end);

    concurrentTime = end - start;
    printf("Tempo concorrente = %lf\n", concurrentTime);
    printf("Ganho de aceleração: %lf\n", sequentialTime/concurrentTime);
    free(vetor);
    free(tid);
    return 0;
}
