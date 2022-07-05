// Laboratório 9 - Computação Concorrente
// Nome: Arthur Valls da Costa Silva
// DRE: 120177470

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#define nthreads 5

/* Variaveis globais */
int x = 0;            // variavel compartilhada
sem_t condt2, condt3; // condicoes do semaforo
void *thread1(void *t)
{
    sem_wait(&condt3);

    printf("Volte sempre!\n");

    pthread_exit(NULL);
}

void *thread2(void *t)
{
    printf("Fique a vontade.\n");
    sem_wait(&condt2);

    x++;
    if (x == 3)
    {
        sem_post(&condt3);
    }
    else
    {
        sem_post(&condt2);
    }

    pthread_exit(NULL);
}

void *thread3(void *t)
{

    printf("Sente-se por favor\n");
    sem_wait(&condt2);

    x++;
    if (x == 3)
    {
        sem_post(&condt3);
    }
    else
    {
        sem_post(&condt2);
    }

    pthread_exit(NULL);
}

void *thread4(void *t)
{

    printf("Aceita um copo d´água?\n");
    sem_wait(&condt2);

    x++;
    if (x == 3)
    {
        sem_post(&condt3);
    }
    else
    {
        sem_post(&condt2);
    }

    pthread_exit(NULL);
}

void *thread5(void *t)
{

    printf("Seja bem-vindo!\n");
    sem_post(&condt2);
   
    pthread_exit(NULL);
    
}

int main(int argc, char const *argv[])
{
    int i;
    pthread_t threads[nthreads];

    // inicia os valores do semaforo
    sem_init(&condt2, 0, 0);
    sem_init(&condt3, 0, 0);

    pthread_create(&threads[0], NULL, thread5, NULL);
    pthread_create(&threads[1], NULL, thread1, NULL);
    pthread_create(&threads[2], NULL, thread2, NULL);
    pthread_create(&threads[3], NULL, thread3, NULL);
    pthread_create(&threads[4], NULL, thread4, NULL);

    for (i = 0; i < nthreads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
