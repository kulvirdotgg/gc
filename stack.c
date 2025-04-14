#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

stack_tt *new_stack(size_t capacity) {
  stack_tt *st = malloc(sizeof(stack_tt));
  if (st == NULL) {
    fprintf(stderr, "CREATING NEW STACK FAILED");
    return NULL;
  }

  st->ptr = 0;
  st->capacity = capacity;

  st->data = malloc(sizeof(void *) * capacity);
  if (st->data == NULL) {
    fprintf(stderr, "ALLOCATING MEMORY TO STACK DS FAILED");
    return NULL;
  }
  return st;
}

void push(stack_tt *stack, void *obj) {
  if (stack->ptr == stack->capacity) {
    stack->capacity *= 2;

    stack->data = realloc(stack->data, sizeof(void *) * stack->capacity);
    if (stack->data == NULL) {
      fprintf(stderr, "STACK_OVERFLOW");
      return;
    }
  }

  stack->data[stack->ptr] = obj;
  stack->ptr++;
}

void *pop(stack_tt *stack) {
  if (stack->ptr == 0) {
    fprintf(stderr, "STACK_UNDERFLOW!!");
    return NULL;
  }

  stack->ptr--;
  return stack->data[stack->ptr];
}

void free_stack(stack_tt *stack) {
  if (stack == NULL) {
    return;
  }

  // we can always free the stack
  // but this is easy to forget to free the underlying memory stack data holds;
  if (stack->data != NULL) {
    free(stack->data);
  }

  free(stack);
}

void stack_remove_nulls(stack_tt *stack) {
  size_t insert_ptr = 0;

  // Iterate through the stack and compact non-NULL pointers.
  for (size_t i = 0; i < stack->ptr; ++i) {
    if (stack->data[i] != NULL) {
      stack->data[insert_ptr++] = stack->data[i];
    }
  }

  // Update the count to reflect the new number of elements.
  stack->ptr = insert_ptr;

  // Optionally, you might want to zero out the remaining slots.
  for (size_t i = insert_ptr; i < stack->capacity; ++i) {
    stack->data[i] = NULL;
  }
}
