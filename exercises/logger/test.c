#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MSGS (10000)
#define MAX_SLEEP (1000000)

void print_usage_and_exit()
{
  printf("logging_program logfile threads\n");
  exit(1);
}

// Hacky C singleton ;)
int logfile_fd(int fd)
{
  static int _fd = -1;

  if (fd >= 0)
    _fd = fd;

  return _fd;
}

void random_sleep()
{
  struct timespec t;

  t.tv_sec = 0;
  t.tv_nsec = ((double)random() / RAND_MAX) * MAX_SLEEP;
  nanosleep(&t, NULL);
}

void log_msg(int prio, const char *msg)
{
  static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  int fd = logfile_fd(-1);
  ssize_t res;

  pthread_mutex_lock(&mutex);

  res = write(fd, (void *)msg, strlen(msg));
  if (res < 0)
    {
      perror("Error writing to logfile:");
      exit(3);
    }
  write(fd, (void *)"\n", 1);
  pthread_mutex_unlock(&mutex);
}

void *producer(void *data)
{
  for (long i = 0; i < MSGS; i++)
    {
      random_sleep();
      log_msg(0, "Test");
    }
  return (void *)0;
}

int main(int ac, char **av)
{
  int producer_threads, logfile;
  pthread_t *threads;

  if (ac != 3)
    print_usage_and_exit();

  // Open logfile and init singleton
  logfile = open(av[1], O_CREAT | O_TRUNC | O_WRONLY);
  if (logfile < 0)
    {
      perror("open(logfile)");
      exit(2);
    }
  else
    printf("Logging at: %s\n", av[1]);
  fchmod(logfile, 0664);
  logfile_fd(logfile);

  // Parse threads number
  producer_threads = atoi(av[2]);

  log_msg(0, "starting program");

  threads = (pthread_t *)malloc(sizeof(pthread_t) * producer_threads);
  for(int i = 0; i < producer_threads; i++)
      pthread_create(threads + i, NULL, producer, NULL);
  for(int i = 0; i < producer_threads; i++)
    pthread_join(threads[i], NULL);

  log_msg(0, "exiting program");
  close(logfile);
  return 0;
}
