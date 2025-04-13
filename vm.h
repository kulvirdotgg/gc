#pragma once
#include "mark_object.h"
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

void track_object(vm_t *vm, mark_t *obj);
void frame_ref_object(frame_t *frame, mark_t *obj);

void mark(vm_t *vm);
void trace(vm_t *vm);
void sweep(vm_t *vm);

// helper functions for trace
void trace_blacken_object(stack_tt *gray_objects, mark_t *ref);
void trace_mark_object(stack_tt *gray_objects, mark_t *ref);

void vm_collect_garbage(vm_t *vm);
