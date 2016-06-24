#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sched.h>
#include <string.h>
#include "common.h"

#define RT_OPS (3000000L)
#define RT_SLEEP (50000000L)
#define NORMAL_OPS (30000000L)

int running;

void interrupt(int signal)
{
  running = 0;
}

void set_affinity()
{
  cpu_set_t set;

  CPU_ZERO(&set);
  CPU_SET(0, &set);
  if (sched_setaffinity(0, sizeof(cpu_set_t), &set))
    perror("sched_setaffinity:");
}

void *thread_normal(void *data)
{
  set_affinity();

  while(running)
    {
      for(long useless = 0; useless < NORMAL_OPS; useless++);
      write(1, &data, 1); fsync(1);
    }
  return (void *)0;
}

void *thread_rt(void *data)
{
  struct timespec sleep;
  struct sched_param sched;

  set_affinity();

  sched.sched_priority = 10;
  if (sched_setscheduler(0, SCHED_FIFO, &sched))
    perror("sched_setscheduler: ");

  sleep.tv_sec = 0;
  sleep.tv_nsec = RT_SLEEP;

  while(running)
    {
      for(long useless = 0; useless < RT_OPS; useless++);
      write(1, &data, 1); fsync(1);
      nanosleep(&sleep, NULL);
    }
  return (void *)0;
}

void print_usage()
{
  printf("Usage: niceplus normal rt\n");
  exit(1);
}

int main(int ac, char **av)
{
  int normal, rt, i;
  pthread_t *threads;
  struct sigaction action;
  const char *symbols = "+-*:@#$%&<>1234567890";

  if (ac != 3)
    print_usage();

  normal = atoi(av[1]);
  rt = atoi(av[2]);

  printf("normal=%d (%ld ops), rt=%d (%ld ops, sleep=%ld ns)\n",
         normal, NORMAL_OPS, rt, RT_OPS, RT_SLEEP);
  threads = (pthread_t *)malloc(sizeof(pthread_t) * (normal + rt));

  // Register Interrupt signal handler
  running = 1;
  memset((void *)&action, 0, sizeof(action));
  action.sa_handler = interrupt;

  for(i = 0; i < normal; i++)
    pthread_create(threads + i, NULL, thread_normal, (void *)symbols[i]);
  for(i = normal; i < normal + rt; i++)
    pthread_create(threads + i, NULL, thread_rt, (void *)symbols[i]);

  for(i = 0; i < normal + rt; i++)
      pthread_join(threads[i], NULL);

  printf("Finished.\n");

  return 0;
}
