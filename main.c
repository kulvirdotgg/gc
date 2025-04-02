#include "object.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("--- Main Function I am inside you ---\n");

  object_t *int_obj = new_int(69);
  assert(int_obj->type == INT);
  assert(int_obj->data.v_int == 69);

  object_t *float_obj = new_float(69);
  assert(float_obj->type == FLOAT);
  assert(float_obj->data.v_float == 69);

  char *wisom_quote = "iladies nuts on your face";
  object_t *str_obj = new_string(wisom_quote);

  assert(str_obj->data.v_string != wisom_quote);
  assert(*str_obj->data.v_string == *wisom_quote);
  printf("%s\n", str_obj->data.v_string);

  object_t *vector = new_vector3(NULL, NULL, NULL);
  assert(vector == NULL);

  object_t *x = new_int(1);
  object_t *y = new_int(2);
  object_t *z = new_int(3);
  object_t *vec = new_vector3(x, y, z);

  assert(vec->data.v_vector3.x == x);
  assert(vec->data.v_vector3.y == y);
  assert(vec->data.v_vector3.z == z);

  assert(vec->data.v_vector3.x->data.v_int == 1);
  assert(vec->data.v_vector3.y->data.v_int == 2);
  assert(vec->data.v_vector3.z->data.v_int == 3);

  object_t *arr = new_array(2);
  assert(arr->type == ARRAY);
  assert(arr->data.v_array.capacity == 2);

  assert(arr->data.v_array.data[0] == NULL);
  assert(arr->data.v_array.data[1] == NULL);

  set_array(arr, 0, x);
  set_array(arr, 1, z);

  object_t *get1 = get_array(arr, 0);
  object_t *get2 = get_array(arr, 1);

  assert(get1 == x);
  assert(get2 == z);

  assert(length(arr) == 2);

  object_t *add_ints = add(get1, get2);
  assert(add_ints->data.v_int == 4);

  free(arr->data.v_array.data);
  free(arr);

  return 0;
}
