#include "vm.h"
#include "mark_object.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void track_object(vm_t *vm, mark_t *obj) {
  if (vm == NULL || obj == NULL) {
    fprintf(stderr, "MARK OBJECTS ARE NULL\n");
  }
  push(vm->objects, (void *)obj);
}

void vm_frame_push(vm_t *vm, frame_t *frame) {
  if (vm == NULL || frame == NULL) {
    return;
  }

  push(vm->frames, (void *)frame);
}

frame_t *vm_new_frame(vm_t *vm) {
  frame_t *frame = malloc(sizeof(frame_t));
  if (frame == NULL) {
    fprintf(stderr, "FAILED TO INITIALIZE FRAME\n");
    return NULL;
  }

  frame->references = new_stack(8);
  if (frame->references == NULL) {
    fprintf(stderr, "FAILED TO INITIALIZE VM FRAME\n");
    free(frame);
    return NULL;
  }

  vm_frame_push(vm, frame);

  return frame;
}

void frame_free(frame_t *frame) {
  if (frame == NULL) {
    fprintf(stderr, "STACK FRMAE IS ALREADY NULL\n");
  }

  free_stack(frame->references);

  free(frame);
}

vm_t *new_vm() {
  vm_t *vm = malloc(sizeof(vm_t));
  if (vm == NULL) {
    fprintf(stderr, "FAILED TO INITIALIZE VM OBJECT\n");
    return NULL;
  }

  vm->frames = new_stack(8);
  vm->objects = new_stack(8);

  return vm;
}

void free_vm(vm_t *vm) {
  if (vm == NULL) {
    fprintf(stderr, "STACK VM IS ALREADY NULL\n");
    return;
  }

  // free each and every frame in the stack
  for (int i = 0; i < vm->frames->ptr; i++) {
    frame_free(vm->frames->data[i]);
  }
  free_stack(vm->frames);

  for (int i = 0; i < vm->objects->ptr; i++) {
    mark_object_free(vm->objects->data[i]);
  }
  free_stack(vm->objects);

  free(vm);
}
