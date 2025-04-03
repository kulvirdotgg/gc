#pragma once
#include "stack.h"

typedef struct virtual_machine {
  stack_tt *frames;
  stack_tt *objects;
} vm_t;

vm_t *new_vm();
void free_vm(vm_t *vm);
