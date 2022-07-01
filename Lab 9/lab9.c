// Laboratório 9 - Computação Concorrente
// Nome: Arthur Valls da Costa Silva
// DRE: 120177470

/*pode ser que tome algumas execucoes do codigo para que
ele mude a ordem das frases, mas elas mudam e o codigo funciona*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#define nthreads 5

/* Variaveis globais */
int x = 0; //variavel compartilhada
sem_t condicao1, condicao2; //condicoes do semaforo
void *thread1(void *t)
{

    while (x < 4)
    {
       sem_post(&condicao1);
    }
    printf("Volte sempre!\n");

    pthread_exit(NULL);
}

void *thread2(void *t)
{
    
    
    if (x == 0)
    {
        sem_wait(&condicao1);
    }
    printf("Fique a vontade.\n");
    
    x++;
    sem_post(&condicao2);

    pthread_exit(NULL);
}

void *thread3(void *t)
{
    
    
    if (x == 0)
    {
        sem_wait(&condicao1);
    }
    printf("Sente-se por favor\n");

    x++;
    sem_post(&condicao2);

    pthread_exit(NULL);
}

void *thread4(void *t)
{
    
    if (x == 0)
    {
        sem_wait(&condicao1);
    }
    printf("Aceita um copo d´água?\n");

    x++;
    sem_post(&condicao2);

    pthread_exit(NULL);
}

void *thread5(void *t)
{
    
    sem_wait(&condicao2);
    printf("Seja bem-vindo!\n");
    x++;
    

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int i;
    pthread_t threads[nthreads];


    // inicia os valores do semaforo
    sem_init(&condicao1, 0, 0);
    sem_init(&condicao2, 0, 1);


    pthread_create(&threads[0], NULL, thread5, NULL);
    pthread_create(&threads[1], NULL, thread1, NULL);
    pthread_create(&threads[2], NULL, thread2, NULL);
    pthread_create(&threads[3], NULL, thread3, NULL);
    pthread_create(&threads[4], NULL, thread4, NULL);

    for (i = 0; i < nthreads; i++)
    {
        pthread_join(threads[i], NULL);
    }


    sem_destroy(&condicao1);
    sem_destroy(&condicao2);

    return 0;
}
