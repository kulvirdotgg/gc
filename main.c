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

  return 0;
}
