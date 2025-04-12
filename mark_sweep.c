#include "mark_object.h"
#include "new_mark_object.h"
#include "vm.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void mark_sweep() {
  vm_t *vm = new_vm();

  mark_t *obj = new_int(vm, 96);
  // object is of type integer...
  assert(obj->type == INT);

  // the object in the vm is infact our object
  assert(vm->objects->data[0] == obj);

  free(obj);
  free_vm(vm);

  // this is causing segfault so this means free vm is fine
  // assert(vm->objects->data[0] == obj);
}
