#pragma once
#include <stdlib.h>

typedef struct Stack {
  size_t ptr;
  size_t capacity;
  void **data;
} stack_tt;

stack_tt *new_stack(size_t capacity);
void push(stack_tt *stack, void *obj);
void *pop(stack_tt *stack);
void free_stack(stack_tt *stack);
void stack_remove_nulls(stack_tt *stack);
