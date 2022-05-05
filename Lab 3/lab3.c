#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

long int N;  // numero de elementos do vetor
int nthreads;  // numero de threads
double *vetor; // vetor de entrada com dimensao N
double concurrentTime, sequentialTime, largestSeq = 0, smallestSeq = 0, largestConc = 0, smallestConc = 0;

// fluxo das threads
void *tarefa(void *arg)
{
    long int id = (long int)arg;         // identificador da thread
    long int tamBloco = N / nthreads; // tamanho do bloco de cada thread
    long int start = id * tamBloco;     // elemento inicial do bloco da thread
    long int end;                        // elemento final(nao processado) do bloco da thread
    if (id == nthreads - 1)
        end = N;
    else
        end = start + tamBloco; // trata o resto se houver
    for (long int i = start; i < end; i++)
    {
        if (vetor[i] > largestConc)
            largestConc = vetor[i];
        if (vetor[i] < smallestConc)
            smallestConc = vetor[i];
    }
    pthread_exit(NULL);
}

// fluxo principal
int main(int argc, char *argv[])
{
    double start, end; // tomada de tempo
    pthread_t *tid;    // identificadores das threads no sistema
    double *retorno;   // valor de retorno das threads

    // recebe e valida os parametros de entrada (dimensao do vetor, numero de threads)
    if (argc < 3)
    {
        fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
        return 1;
    }
    N = atoi(argv[1]);
    nthreads = atoi(argv[2]);
    // aloca o vetor de entrada
    vetor = (double *)malloc(sizeof(double) * N);
    if (vetor == NULL)
    {
        fprintf(stderr, "ERRO--malloc\n");
        return 2;
    }
    // preenche o vetor de entrada
    srand((float)time(NULL));
    for (long int i = 0; i < N; i++)
        vetor[i] =  (float)rand();

    // procura sequencial
    GET_TIME(start);
    for (long int i = 1; i < N; ++i)
    {
        if (vetor[i] > largestSeq)
            largestSeq = vetor[i];
        if (vetor[i] < smallestSeq)
            smallestSeq = vetor[i];
    }
    GET_TIME(end);
    sequentialTime = end - start;
    printf("Tempo sequencial:  %lf\n", sequentialTime);

    // procura concorrente
    GET_TIME(start);
    tid = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
    if (tid == NULL)
    {
        fprintf(stderr, "ERRO--malloc\n");
        return 2;
    }
    // criar as threads
    for (long int i = 0; i < nthreads; i++)
    {
        if (pthread_create(tid + i, NULL, tarefa, (void *)i))
        {
            fprintf(stderr, "ERRO--pthread_create\n");
            return 3;
        }
    }
    // aguardar o termino das threads
    for (long int i = 0; i < nthreads; i++)
    {
        if (pthread_join(*(tid + i), (void **)&retorno))
        {
            fprintf(stderr, "ERRO--pthread_create\n");
            return 3;
        }
        
    }
    GET_TIME(end);
    concurrentTime = end - start;
    printf("Tempo concorrente:  %lf\n", concurrentTime);

    printf("Aceleração do programa:  %lf\n", (sequentialTime/concurrentTime));

    //corretude
   if(largestSeq != largestConc || smallestSeq != smallestConc){
       fprintf(stderr, "ERRO--número enconcontrado sequencial e concorrente diferentes");
   }

    // libera as areas de memoria alocadas
    free(vetor);
    free(tid);

    return 0;
}
