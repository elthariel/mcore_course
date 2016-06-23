#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
  int *p = (int *) malloc(sizeof(int));

  printf("first free()\n");
  free(p);
  printf("second free()\n");
  free(p);
  printf("Bam !\n");
}
