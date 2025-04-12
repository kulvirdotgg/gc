#pragma once
#include "stack.h"

typedef struct VirtualMachine {
  stack_tt *frames;
  stack_tt *objects;
} vm_t;

typedef struct StackFrame {
  stack_tt *references;
} frame_t;

vm_t *new_vm();
void free_vm(vm_t *vm);

void vm_frame_push(vm_t *vm, frame_t *frame);
frame_t *vm_new_frame(vm_t *vm);
void frame_free(frame_t *frame);
