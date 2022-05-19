// Laboratório 5 - Computação Concorrente
// Nome: Arthur Valls da Costa Silva
// DRE: 120177470

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define nthreads 5

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

void *thread1(void *arg)
{
    pthread_mutex_lock(&x_mutex);
    while (x < 4)
    {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Volte sempre!\n");

    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

void *thread2(void *arg)
{
    pthread_mutex_lock(&x_mutex);

    while (x < 1)
    {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Fique a vontade.\n");

    x++;
    pthread_cond_broadcast(&x_cond);
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

void *thread3(void *arg)
{
    pthread_mutex_lock(&x_mutex);
    if (x < 1)
    {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Sente-se por favor\n");

    x++;
    pthread_cond_broadcast(&x_cond);
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

void *thread4(void *arg)
{
    pthread_mutex_lock(&x_mutex);
    if (x < 1)
    {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Aceita um copo d´água?\n");

    x++;
    pthread_cond_broadcast(&x_cond);
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

void *thread5(void *arg)
{
    pthread_mutex_lock(&x_mutex);
    printf("Seja bem-vindo!\n");
    x++;
    pthread_cond_broadcast(&x_cond);
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int i;
    pthread_t threads[nthreads];

    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);

    pthread_create(&threads[4], NULL, thread5, NULL);
    pthread_create(&threads[0], NULL, thread1, NULL);
    pthread_create(&threads[1], NULL, thread2, NULL);
    pthread_create(&threads[2], NULL, thread3, NULL);
    pthread_create(&threads[3], NULL, thread4, NULL);

    for (i = 0; i < nthreads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond);

    return 0;
}
