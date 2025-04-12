#include "mark_object.h"
#include "vm.h"

mark_t *new_int(vm_t *vm, int value);
mark_t *new_float(vm_t *vm, float value);
mark_t *new_string(vm_t *vm, char *value);
mark_t *new_vector3(vm_t *vm, mark_t *x, mark_t *y, mark_t *z);
mark_t *new_array(vm_t *vm, size_t capacity);
