#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include "common.h"

#define OPS (50000000L)

void *da_loop(void *data)
{
  int64_t i;
  int64_t *val = (int64_t *)data;

  for(i = 0; i < OPS; i++)
    {
      *val += i;
    }

  return (void *)val;
}

void print_usage()
{
  printf("Usage: false_sharing threads padding\n");
  exit(1);
}


int main(int ac, char **av)
{
  int thread_count, padding, i;
  struct timespec before, after;
  pthread_t *threads;
  int64_t *data;

  if (ac != 3)
    print_usage();

  thread_count = atoi(av[1]);
  padding = atoi(av[2]);

  printf("threads=%d, padding=%d, ops=%ld\n",
         thread_count, padding, OPS);
  data = (int64_t *) malloc(sizeof(int64_t) * (1 + padding));
  threads = (pthread_t *) malloc(sizeof(pthread_t) * thread_count);

  get_time(&before);
  for(i = 0; i < thread_count; i++)
      pthread_create(threads + i, NULL, da_loop,
                     (void *)data + i * (1 + padding));

  for(i = 0; i < thread_count; i++)
      pthread_join(threads[i], NULL);
  get_time(&after);

  double result = get_time_diff(&before, &after) / 1000.0;

  printf("Finished in %f usec.\nThats's %.2f ops/usec\n", result,
         thread_count * OPS / result);

  return 0;
}
