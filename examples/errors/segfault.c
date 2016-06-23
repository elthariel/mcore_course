#include <stdio.h>

int main(int ac, char **av)
{
  printf("Hello World, watch me crash and burn...\n");

  int *pointer = 0;

  printf("Never Executed %d", *pointer);
}
