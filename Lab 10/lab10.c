// Laboratório 10 - Computação Concorrente
// Nome: Arthur Valls da Costa Silva
// DRE: 120177470

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define L 3 // numero de threads leitoras
#define E 3 // numero de threads escritoras

#define NTHREADS L + E

sem_t em_e, em_l, leit, escr; // semaforos
int l = 0, e = 0;             // globais

// thread que os leitores executaram
void *Leitor(void *threadid)
{
   int *tid = (int *)threadid;
   while (1)
   {
      printf("Leitor %d quer ler!\n", *tid);
      sem_wait(&leit);
      sem_wait(&em_l);
      l++;
      if (l == 1)
      {
         sem_wait(&escr);
      }
      sem_post(&em_l);
      sem_post(&leit);
      printf("Leitor %d está lendo!\n", *tid);
      sleep(1);
      printf("Leitor %d terminou de ler!\n", *tid);
      sem_wait(&em_l);
      l--;
      if (l == 0)
      {
         sem_post(&escr);
      }
      sem_post(&em_l);
   }
   free(threadid);
   pthread_exit(NULL);
}

// thread que os escritores executaram
void *Escritor(void *threadid)
{
   int *tid = (int *)threadid;
   while (1)
   {
      printf("Escritor %d quer escrever!\n", *tid);
      sem_wait(&em_e);
      e++;
      if (e == 1)
      {
         sem_wait(&leit);
      }
      sem_post(&em_e);
      sem_wait(&escr);
      printf("Escritor %d está escrevendo!\n", *tid);
      sem_post(&escr);
      printf("Escritor %d terminou de escrever!\n", *tid);
      sem_wait(&em_e);
      e--;
      if (e == 0)
      {
         sem_post(&leit);
      }
      sem_post(&em_e);
      sleep(1);
   }
   free(threadid);
   pthread_exit(NULL);
}

// funcao principal
int main(void)
{
   pthread_t tid[NTHREADS];
   int t, id[NTHREADS];

   // inicia os semaforos
   sem_init(&leit, 0, 1);
   sem_init(&escr, 0, 1);
   sem_init(&em_l, 0, 1);
   sem_init(&em_e, 0, 1);

   // cria os escritores
   for (t = 0; t < E; t++)
   {
      id[t + L] = t + 1;
      if (pthread_create(&tid[t + L], NULL, Escritor, (void *)&id[t + L]))
      {
         printf("--ERRO: pthread_create()\n");
         exit(-1);
      }
   }
   // cria os leitores
   for (t = 0; t < L; t++)
   {
      id[t] = t + 1;
      if (pthread_create(&tid[t], NULL, Leitor, (void *)&id[t]))
      {
         printf("--ERRO: pthread_create()\n");
         exit(-1);
      }
   }


   // --espera todas as threads terminarem
   for (t = 0; t < (NTHREADS); t++)
   {
      pthread_join(tid[t], NULL);
   }
   printf("Fim.\n");

   pthread_exit(NULL);
   return 0;
}
