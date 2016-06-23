#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
  int int_on_stack, *int_on_heap;

  int_on_heap = (int *)malloc(sizeof(int));

  printf("int on stack: %d\n", int_on_stack);
  printf("int on heap: %d\n", *int_on_heap);

  free(int_on_heap);
}
