#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
  pthread_t t1, t2;
  pthread_mutex_t m1, m2;
  int i1, i2;
} program;

void *thread1(void *data)
{
  program *p = (program *)data;

  while(42)
    {
      printf("t1 lock m1\n");
      pthread_mutex_lock(&p->m1);
      printf("t1 lock m2\n");
      pthread_mutex_lock(&p->m2);

      printf("t1 unlocking\n");
      pthread_mutex_unlock(&p->m1);
      pthread_mutex_unlock(&p->m2);
    }

  return (void *)0;
}

void *thread2(void *data)
{
  program *p = (program *)data;

  while(42)
    {
      printf("t2 lock m2\n");
      pthread_mutex_lock(&p->m2);
      printf("t2 lock m1\n");
      pthread_mutex_lock(&p->m1);

      printf("t2 unlocking\n");
      pthread_mutex_unlock(&p->m1);
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
