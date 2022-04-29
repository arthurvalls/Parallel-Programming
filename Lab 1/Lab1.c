#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NTHREADS 2
#define LIMIT 10000

int vetor[LIMIT];


void *elevar(void *arg) // função que cada thread utilizará para elevar os elementos do vetor de sua respectiva parte ao quadrado
{
    int ident = *(int *)arg;
    int i = (LIMIT / (ident)) - 1;
    int j = 0;
    while (j != (LIMIT / 2))
    {
        vetor[i] = (i * i);
        j++;
        i--;
    }
    pthread_exit(NULL);
}

int main()
{
    int elemento, i;

    for (elemento = 0; elemento < LIMIT; elemento++) // preenche vetor
    {
        vetor[elemento] = elemento;
    }

    pthread_t tid_sistema[NTHREADS]; // identificadores das threads no sistema
    int ident[NTHREADS];

    for (i = 1; i <= NTHREADS; i++) // cria as threads
    {
        ident[i - 1] = i;
        if (pthread_create(&tid_sistema[i - 1], NULL, elevar, (void *)&ident[i - 1]))
            printf("--ERRO: pthread_create()\n");
    }

  
    for (i = 0; i < NTHREADS; i++)   // aguarda o término de execução das threads
    {
        if (pthread_join(tid_sistema[i], NULL))
            printf("--ERRO: pthread_join\n");
    }

 
    for (i = 0; i < LIMIT; i++)  // testa caso ocorra erros
    {
        if (vetor[i] != (i * i))
        {
            printf("--ERRO: elevar\n");
            break;
        }
    }
    return 0;
}
