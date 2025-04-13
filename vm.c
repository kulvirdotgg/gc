#include "vm.h"
#include "mark_object.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void mark(vm_t *vm) {
  if (vm == NULL) {
    fprintf(stderr, "VM IS NULL CANNOT MARK\n");
    return;
  }

  for (int i = 0; i < vm->frames->ptr; i++) {
    frame_t *frame = vm->frames->data[i];
    for (int j = 0; j < frame->references->ptr; j++) {
      // this is necessary because data is of type (void **)
      // so we need to type cast it to mark object type.
      mark_t *obj = frame->references->data[j];
      obj->is_marked = true;
    }
  }
}

void trace(vm_t *vm) {
  if (vm == NULL) {
    fprintf(stderr, "VM IS NULL CANNOT TRACE\n");
    return;
  }

  stack_tt *gray_objects = new_stack(8);
  if (gray_objects == NULL) {
    fprintf(stderr, "gray objects stack couldn't be initialized\n");
  }

  for (int i = 0; i < vm->objects->ptr; ++i) {
    mark_t *obj = vm->objects->data[i];
    if (obj && obj->is_marked) {
      push(gray_objects, obj);
    }
  }

  while (gray_objects->ptr > 0) {
    mark_t *obj = pop(gray_objects);
    trace_blacken_object(gray_objects, obj);
  }

  free_stack(gray_objects);
}

void trace_blacken_object(stack_tt *gray_objects, mark_t *obj) {
  if (obj == NULL) {
    fprintf(stderr, "VM IS NULL CANNOT TRACE\n");
    return;
  }

  switch (obj->type) {
  case INT:
    return;
  case FLOAT:
    return;
  case STRING:
    return;
  case VECTOR3: {
    trace_mark_object(gray_objects, obj->data.v_vector3.x);
    trace_mark_object(gray_objects, obj->data.v_vector3.y);
    trace_mark_object(gray_objects, obj->data.v_vector3.z);
    break;
  }
  case ARRAY: {
    mark_array_t arr = obj->data.v_array;
    for (int i = 0; i < arr.capacity; ++i) {
      trace_mark_object(gray_objects, mark_arr_get(obj, i));
    }
    break;
  }
  }
}

void trace_mark_object(stack_tt *gray_objects, mark_t *obj) {
  if (obj == NULL) {
    fprintf(stderr, "OBJECT IS NULL CANNOT TRACE\n");
    return;
  }

  if (obj->is_marked) {
    // do not try to mark already marked objects because save CPU time.
    return;
  }

  obj->is_marked = true;
  push(gray_objects, (void *)obj);
}

void track_object(vm_t *vm, mark_t *obj) {
  if (vm == NULL || obj == NULL) {
    fprintf(stderr, "MARK OBJECTS ARE NULL\n");
  }
  push(vm->objects, (void *)obj);
}

// add reference of an object inside the frame.
void frame_ref_object(frame_t *frame, mark_t *obj) {
  if (frame == NULL || obj == NULL) {
    fprintf(stderr, "FRAME OR OBJECT TRYING TO REFERENCE IS NULL\n");
  }

  push(frame->references, obj);
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
    fprintf(stderr, "STACK FRAME IS ALREADY NULL\n");
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
