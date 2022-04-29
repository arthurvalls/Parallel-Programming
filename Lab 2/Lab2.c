#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "timer.h"

float *matrix1, *matrix2, *sequentialOutput, *concurrentOutput;
int nthreads;
pthread_t *tid;

typedef struct
{
    int id, dim;
} tArgs;

void sequentialMultiplication(int dim)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            for (int k = 0; k < dim; k++)
            {
                sequentialOutput[i * dim + j] += matrix1[i * dim + k] * matrix2[k * dim + j];
            }
        }
    }
}

void *concurrentMultiplication(void *arg)
{
    tArgs *args = (tArgs *)arg;
    for (int i = args->id; i < args->dim; i += nthreads)
    {
        for (int j = 0; j < args->dim; j++)
        {
            for (int k = 0; k < args->dim; k++)
            {
                concurrentOutput[i * args->dim + j] += matrix1[i * args->dim + k] * matrix2[k * args->dim + j];
            }
        }
    }
    pthread_exit(NULL);
}

void createMatrices(int dim)
{
    srand(time(NULL));
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            sequentialOutput[i * dim + j] = 0;
            concurrentOutput[i * dim + j] = 0;
            matrix1[i * dim + j] = rand() % 10;
            matrix2[i * dim + j] = rand() % 10;
        }
    }
}

int main(int argc, char *argv[])
{
    int dim;
    double start, end, sequentialTime, concurrentTime, timeUpgrade;

    tArgs *args;
    if (argc < 3)
    {
        printf("Digite: %s <dimensao da matriz> <numero de threads>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]);
    nthreads = atoi(argv[2]);

    matrix1 = (float *)malloc(sizeof(float) * dim * dim);
    if (matrix1 == NULL)
    {
        printf("malloc error matrix1\n");
        return 2;
    }
    matrix2 = (float *)malloc(sizeof(float) * dim * dim);
    if (matrix2 == NULL)
    {
        printf("malloc error matrix2\n");
        return 2;
    }
    sequentialOutput = (float *)malloc(sizeof(float) * dim * dim);
    if (sequentialOutput == NULL)
    {
        printf("malloc error sequentialOutput\n");
        return 2;
    }
    concurrentOutput = (float *)malloc(sizeof(float) * dim * dim);
    if (concurrentOutput == NULL)
    {
        printf("malloc error concurrentOutput\n");
        return 2;
    }

    GET_TIME(start);

    sequentialMultiplication(dim);

    GET_TIME(end);

    sequentialTime = end - start;

    printf("\nTempo de duração da multiplicação sequencial foi: %.4lf segundos.\n", sequentialTime);
    tid = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
    if (tid == NULL)
    {
        printf("\nmalloc error: tid\n");
        return 2;
    }
    args = (tArgs *)malloc(sizeof(tArgs) * nthreads);
    if (args == NULL)
    {
        printf("\nmalloc error: args\n");
        return 2;
    }

    GET_TIME(start);
    for (int i = 0; i < nthreads; i++)
    {
        (args + i)->id = i;
        (args + i)->dim = dim;
        if (pthread_create(tid + i, NULL, concurrentMultiplication, (void *)(args + i)))
        {
            printf("pthread_create error\n");
            return 2;
        }
    }

    for (int i = 0; i < nthreads; i++)
    {
        if (pthread_join(*(tid + i), NULL))
        {
            printf("pthread_join error\n");
            return 2;
        }
    }
    GET_TIME(end);

    concurrentTime = end - start;
    printf("\nTempo de duração da multiplicação concorrente foi: %.4lf segundos, utilizando %d threads.\n", concurrentTime, nthreads);
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (concurrentOutput[i * dim + j] != sequentialOutput[i * dim + j])
            {
                printf("\nMatrizes são diferentes\n");
                return 2;
            }
        }
    }

    timeUpgrade = sequentialTime / concurrentTime;



    printf("Melhoria no desempenho -> %lf\n segundos ", timeUpgrade);

    
}
