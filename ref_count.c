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
}
