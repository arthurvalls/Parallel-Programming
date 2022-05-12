//Laboratório 4 - Computação Concorrente
//Nome: Arthur Valls da Costa Silva
//DRE: 120177470

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

long long int globalVar = 0, N;
int nthreads, *array;
float *sequentialArray, *concurrentArray;
pthread_mutex_t mutex;

// funcao para encontrar a raiz quadrada de numeros primos
int isPrime(long long int number)
{
    if (number < 2)
        return 0;

    double squareRoot = sqrt(number);
    for (int i = 2; i <= (squareRoot); i++)
        if (number % i == 0)
            return 0;
    return 1;
}

void sequentialPrime(int *array, long long int N)
{
    for (long long int i = 0; i < N; i++)
    {
        if (isPrime(array[i]))
            sequentialArray[i] = sqrt(array[i]);
        else
            sequentialArray[i] = array[i];
    };
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
        if (isPrime(array[localVar]))
            concurrentArray[localVar] = sqrt(array[localVar]);
        else
            concurrentArray[localVar] = array[localVar];

        pthread_mutex_lock(&mutex);
        localVar = globalVar;
        globalVar++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

// funcao para verificar a corretude
void correctness(float *array1, float *array2)
{

    for (int i = 0; i < N; i++)
    {
        if (array1[i] != array2[i])
        {
            printf("ERRO: Vetores diferentes.\n");
            break;
        }
        else
            printf("Vetores iguais.\n");
        break;
    }
}

int main(int argc, char *argv[])
{
    pthread_t *tid;
    long int t;
    double start, end;
    double concurrentTime, sequentialTime;

    if (argc < 3)
    {
        fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
        return 3;
    }
    N = atoll(argv[1]);
    nthreads = atoi(argv[2]);

    // aloca o array de entrada
    array = (int *)malloc(sizeof(int) * N);
    if (array == NULL)
    {
        fprintf(stderr, "ERRO--malloc--Array1\n");
        return 2;
    }

    sequentialArray = (float *)malloc(sizeof(float) * N);
    concurrentArray = (float *)malloc(sizeof(float) * N);

    // preenche o array de entrada com números aleatórios até 10^6

    srand(time(NULL));
    int limit = pow(10, 6);
    for (long int i = 0; i < N; i++)
    {
        array[i] = rand() % limit;
    };

    // função sequencial
    GET_TIME(start);
    sequentialPrime(array, N);
    GET_TIME(end);
    sequentialTime = end - start;
    printf("Tempo sequencial = %lf\n", sequentialTime);

    // função concorrente
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
        };
    };
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

    printf("Ganho de desempenho =  %lf\n", sequentialTime / concurrentTime);

    // corretude
    correctness(concurrentArray, sequentialArray);

    free(array);
    free(sequentialArray);
    free(concurrentArray);
    free(tid);
    return 0;
}
