#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <assert.h>

void get_time(struct timespec *t)
{
  assert(t);

  if (clock_gettime(CLOCK_MONOTONIC, t) < 0)
    {
      perror("Error getting time");
      exit(2);
    }
}

double get_time_diff(struct timespec *before, struct timespec *after)
{
  assert(before);
  assert(after);

  return (double) (after->tv_sec - before->tv_sec) * 1000000000
    + (after->tv_nsec - before->tv_nsec);
}
