#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

int main(int ac, char **av)
{
  int *array = (int *) malloc(sizeof(int) * SIZE);

  for(int i = 0; i < SIZE + 24; ++i)
    {
      printf("array[%d] -> %d\n", i, array[i]);
    }
}
