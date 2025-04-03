#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

vm_t *new_vm() {
  vm_t *vm = malloc(sizeof(vm_t));
  if (vm == NULL) {
    fprintf(stderr, "FAILED TO INITIALIZE VM OBJECT");
    return NULL;
  }

  vm->frames = new_stack(8);
  if (vm->frames == NULL) {
    fprintf(stderr, "FAILED TO INITIALIZE VM FRAMES STACK");
    return NULL;
  }

  vm->objects = new_stack(8);
  if (vm->frames == NULL) {
    fprintf(stderr, "FAILED TO INITIALIZE VM OBJECTS STACK");
    return NULL;
  }

  return vm;
}

void free_vm(vm_t *vm) {
  if (vm == NULL) {
    fprintf(stderr, "STACK VM IS ALREADY NULL");
    return;
  }
  free_stack(vm->frames);
  free_stack(vm->objects);

  free(vm);
}
