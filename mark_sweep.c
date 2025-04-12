#include "vm.h"
#include <assert.h>

void mark_sweep() {
  vm_t *vm = new_vm();

  vm_new_frame(vm);
  free_vm(vm);

  // this causes seg fault this means that vm doesn't exist anymore
  // assert(vm->frames->ptr == 1);
}
