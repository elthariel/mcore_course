#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
  printf("Yummy malloc() !\n");
  int *big = (int *) malloc(sizeof(int) * 1024 * 1024);
  (void)big; // Idiom to remove unused variable warning
  printf("Goodbye !\n");
}
