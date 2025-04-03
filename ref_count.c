#include "object.h"
#include <assert.h>
#include <stdio.h>

void gc() {
  object_t *int_obj = new_int(10);
  assert(int_obj->ref_count == 1);

  object_t *float_obj = new_float(420.69);
  ref_count_incr(float_obj);
  assert(float_obj->ref_count == 2);

  ref_count_decr(float_obj);
  assert(float_obj->ref_count == 1);

  object_t *str = new_string("your mum");
  assert(str->ref_count == 1);
  ref_count_decr(str);

  // Seg fault means This object is GCED!!!!!!
  // printf("%s\n", str->data.v_string);

  object_t *x = new_int(1);
  object_t *y = new_int(2);
  object_t *z = new_int(3);
  object_t *vec = new_vector3(x, y, z);

  assert(x->ref_count == 2);
  assert(y->ref_count == 2);
  assert(z->ref_count == 2);

  ref_count_decr(x);
  assert(x->ref_count == 1);

  object_t *one = new_int(1);
  object_t *arr = new_array(1);
  set_array(arr, 0, one);
  assert(one->ref_count == 2);

  ref_count_decr(one);
  ref_count_decr(one);

  // Garbage value hence it means object is cleared
  // printf("%p\n", one);
}
