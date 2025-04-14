#include "mark_object.h"
#include "new_mark_object.h"
#include "stack.h"
#include "vm.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  /*
  // stuff we have to do without writing our own garbage collector
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
  */

  /* vm_t *vm = new_vm();
  frame_t *f1 = vm_new_frame(vm); // du du du max verstappen..

  mark_t *str = new_string(vm, "GG! I have completed my gc it better work");
  frame_ref_object(f1, str);

  // frame is still in use so our str should exist;
  vm_collect_garbage(vm);
  assert(str->data.v_string != NULL);

  // Its printing the correct string hence nothing weird happened.
  // printf("%s\n", str->data.v_string);

  frame_free(f1);
  vm_collect_garbage(vm);

  // Segfault this means that string was garbaed collected. GG!
  // printf("%s\n", str->data.v_string); */

  // The FINAL TEST OF OUR GC!!!
  vm_t *vm = new_vm();

  // each frame stack represents different scope
  /*
  def func:
    def inner:
      def more_inner:
        pass
  */
  frame_t *f1 = vm_new_frame(vm);
  frame_t *f2 = vm_new_frame(vm);
  frame_t *f3 = vm_new_frame(vm);

  mark_t *s1 = new_string(vm, "string in frame 1");
  frame_ref_object(f1, s1);

  mark_t *s2 = new_string(vm, "string in frame 1");
  frame_ref_object(f2, s2);

  mark_t *s3 = new_string(vm, "string in frame 1");
  frame_ref_object(f3, s3);

  mark_t *x = new_int(vm, 420);
  mark_t *y = new_int(vm, 69);
  mark_t *z = new_int(vm, 80085);

  mark_t *vec = new_vector3(vm, x, y, z);

  frame_ref_object(f2, vec);
  frame_ref_object(f3, vec);

  assert(vm->objects->ptr == 7);

  // remove the most_inner function because we exit that scope
  frame_free(pop(vm->frames));

  // because f3 is out of scope so its items should be gc'ed.
  vm_collect_garbage(vm);

  // segfault hence this means my gc is doing a good job
  // good job gc, I am proud of you!!!
  // printf("the string after being gced is\n%s\n", s3->data.v_string);

  // items not being garbage collected....
  printf("the string after not being gced is\n%s\n", s1->data.v_string);
  printf("the string after not being gced is\n%s\n", s2->data.v_string);

  frame_free(pop(vm->frames));
  frame_free(pop(vm->frames));
  vm_collect_garbage(vm);

  // These things cause segmentation error so ig GOOD JOB GC
  // printf("the string after being gced is\n%s\n", s1->data.v_string);
  // printf("the string after being gced is\n%s\n", s2->data.v_string);
  // printf("%d\n", vec->data.v_vector3.x->data.v_int);

  assert(vm->objects->ptr == 0);
  free_vm(vm);
}
