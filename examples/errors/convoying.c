#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
  pthread_t t1, t2;
  pthread_mutex_t m1, m2;
  int i1, i2;
} program;

void *thread1(void *data)
{
  program *p = (program *)data;
  struct timespec wait;

  wait.tv_sec = 1;
  wait.tv_nsec = 0;

  printf("Starting t1\n");
  while(42)
    {
      pthread_mutex_lock(&p->m1);
      pthread_mutex_lock(&p->m2);

      printf("t1 has locks\n");

      pthread_mutex_unlock(&p->m1);
      nanosleep(&wait, NULL);
      pthread_mutex_unlock(&p->m2);
    }

  return (void *)0;
}

void *thread2(void *data)
{
  program *p = (program *)data;
  struct timespec wait;

  wait.tv_sec = 0;
  wait.tv_nsec = 10000000;

  printf("Starting t2\n");
  while(42)
    {
      pthread_mutex_lock(&p->m1);
      pthread_mutex_lock(&p->m2);

      printf("t2 has locks\n");

      pthread_mutex_unlock(&p->m1);
      nanosleep(&wait, NULL);
      pthread_mutex_unlock(&p->m2);
    }

  return (void *)0;
}

int main(int ac, char **av)
{
  program *p;

  p = (program *)malloc(sizeof(program));

  p->i1 = p->i2 = 0;
  pthread_mutex_init(&p->m1, NULL);
  pthread_mutex_init(&p->m2, NULL);

  pthread_create(&p->t1, NULL, thread1, (void *)p);
  pthread_create(&p->t2, NULL, thread2, (void *)p);

  pthread_join(p->t1, NULL);
  return 0;
}
