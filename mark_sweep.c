#include "mark_object.h"
#include "new_mark_object.h"
#include "vm.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void mark_sweep() {
  /*
  // older code to test itty bitty parts of the vm and mark_sweep
  vm_t *vm = new_vm();

  mark_t *obj = new_int(vm, 96);
  // object is of type integer...
  assert(obj->type == INT);

  // the object in the vm is infact our object
  assert(vm->objects->data[0] == obj);
  assert(vm->objects->ptr == 1);

  free_vm(vm);

  // this is causing segfault so this means free vm is fine
  // assert(vm->objects->data[0] == obj);
  */

  vm_t *vm = new_vm();
  frame_t *frame = vm_new_frame(vm);

  mark_t *x = new_int(vm, 69);
  mark_t *y = new_int(vm, 420);
  mark_t *z = new_int(vm, 80085);
  mark_t *vector = new_vector3(vm, x, y, z);

  // coz rn our code is working fine and it doesn't need gc to start
  // so each and every object in our memory is not marked.
  assert(x->is_marked == false);
  assert(y->is_marked == false);
  assert(z->is_marked == false);
  assert(vector->is_marked == false);

  // because of our not so good virtual machine to try our garbage collector
  // we have to set references in the stack frames by ourself
  frame_ref_object(frame, vector);

  // here we are running out of memory so we will start mark phase
  // of mark and sweep algorithm.
  mark(vm);

  // this mark is not very robust function so it will not dig deep down the
  // references each object hold, so this will only mark the objects only
  assert(vector->is_marked == true);
  assert(x->is_marked == false);
  assert(y->is_marked == false);
  assert(z->is_marked == false);

  // we have to manually trace down the references each object hold
  trace(vm);
  // now each and every refernce vector hold should be marked tooo...
  assert(vector->is_marked == true);
  assert(x->is_marked == true);
  assert(y->is_marked == true);
  assert(z->is_marked == true);
}
