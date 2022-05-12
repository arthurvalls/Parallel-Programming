#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

long long int globalVar = 0, N;
int nthreads, *vetor;
float *sequentialArray, *concurrentArray;

pthread_mutex_t mutex; // variavel de mutex para exclusao mutua

int isPrime(int number)
{

    if (number < 2)
        return 0;

    double squareRoot = sqrt(number);
    for (int i = 2; i <= (squareRoot) + 1; i++)
        if (number % i == 0)
            return 0;
    return 1;
}

void sequentialPrimes(int *vetor, long long int N)
{
    for (long long int i = 0; i < N; i++)
    {
        if (isPrime(vetor[i]))
            sequentialArray[i] = sqrt(vetor[i]);
        else
            sequentialArray[i] = vetor[i];
    }
}
// funcao executada pelas threads
void *task()
{

    pthread_mutex_lock(&mutex);
    int localVar = globalVar;
    globalVar++;
    pthread_mutex_unlock(&mutex);

    while (localVar < N)
    {
        if (isPrime(concurrentArray[localVar]))
            concurrentArray[localVar] = sqrt(vetor[localVar]);
        else
            concurrentArray[localVar] = vetor[localVar];
        pthread_mutex_lock(&mutex);
        localVar = globalVar;
        globalVar++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t *tid;
    int t;
    double start, end;
    double concurrentTime, sequentialTime;

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
    sequentialArray = (float *)malloc(sizeof(float) * N);
    if (vetor == NULL)
    {
        fprintf(stderr, "ERRO--malloc\n");
        return 2;
    }
    concurrentArray = (float *)malloc(sizeof(float) * N);
    if (vetor == NULL)
    {
        fprintf(stderr, "ERRO--malloc\n");
        return 2;
    }

    // preenche o vetor de entrada
    srand(time(NULL));
    // int limit = pow(10,6);

    for (long int i = 0; i < N; i++)
    {
        vetor[i] = rand() % N;
    }

    // sequencial
    GET_TIME(start);
    sequentialPrimes(vetor, N);
    GET_TIME(end);
    sequentialTime = end - start;
    printf("Tempo sequencial = %lf\n", sequentialTime);

    GET_TIME(start);
    pthread_mutex_init(&mutex, NULL);
    tid = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
    if (tid == NULL)
    {
        fprintf(stderr, "ERRO--malloc\n");
        return 2;
    }
    for (t = 0; t < nthreads; t++)
    {

        if (pthread_create(tid + t, NULL, task, NULL))
        {
            printf("--ERRO: pthread_create()\n");
            exit(-1);
        }
    }
    //--espera todas as threads terminarem
    for (t = 0; t < nthreads; t++)
    {
        if (pthread_join(*(tid + t), NULL))
        {
            printf("--ERRO: pthread_join() \n");
            exit(-1);
        }
    }
    pthread_mutex_destroy(&mutex);
    GET_TIME(end);

    concurrentTime = end - start;
    printf("Tempo concorrente = %lf\n", concurrentTime);

    for (int i = 0; i < N; i++)
    {
        if (concurrentArray[i] != sequentialArray[i])
        {
            printf("ERRO: Matrizes diferentes.\n");
            break;
        }
        else
            printf("Matrizes iguais.\n");
        break;
    }

    printf("Ganho de aceleração: %lf\n", sequentialTime / concurrentTime);

    free(sequentialArray);
    free(concurrentArray);
    free(tid);
    return 0;
}
