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

  int eww = 69;

  push(s, &eww);
  push(s, &eww);

  assert(s->capacity == 2);
  assert(s->ptr == 2);

  push(s, &eww);

  assert(s->capacity == 4);
  assert(s->ptr == 3);

  free(s->data);
  free(s);

  return 0;
}
