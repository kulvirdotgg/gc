#include "stack.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("--- Main Function I am inside you ---\n");

  size_t size = 2;
  stack_tt *s = new_stack(size);
  assert(s->capacity == size);

  int one = 69;
  int two = 420;
  int three = 80085;

  push(s, &one);
  push(s, &two);
  push(s, &three);

  assert(s->capacity == size * 2);
  assert(s->ptr == size + 1);

  int *poppy = pop(s);
  assert(*poppy == three);

  poppy = pop(s);
  assert(*poppy == two);

  poppy = pop(s);
  assert(*poppy == one);

  assert(s->ptr == 0);

  free(s->data);
  free(s);

  return 0;
}
