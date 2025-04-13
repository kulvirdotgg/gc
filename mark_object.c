#include "mark_object.h"
#include <stdio.h>
#include <stdlib.h>

void mark_object_free(mark_t *obj) {
  switch (obj->type) {
  case INT:
  case FLOAT:
    break;
  case STRING:
    free(obj->data.v_string);
    break;
  case VECTOR3: {
    break;
  }
  case ARRAY: {
    free(obj->data.v_array.data);
    break;
  }
  }
  free(obj);
}

bool mark_arr_set(mark_t *array, size_t index, mark_t *value) {
  if (array == NULL || value == NULL) {
    fprintf(stderr, "ARRAY DOES NOT EXIST OR VALUE IS NULL\n");
    return false;
  }

  if (array->type != ARRAY) {
    fprintf(stderr, "OBJECT IS NOT OF TYPE ARRAY\n");
    return false;
  }

  if (array->data.v_array.capacity <= index) {
    fprintf(stderr, "INDEX OUT OF BOUND\n");
    return false;
  }

  array->data.v_array.data[index] = value;
  return true;
}

mark_t *mark_arr_get(mark_t *array, size_t index) {
  if (array == NULL) {
    fprintf(stderr, "ARRAY DOES NOT EXIST\n");
    return NULL;
  }

  if (array->data.v_array.capacity <= index) {
    fprintf(stderr, "INDEX OUT OF BOUND\n");
    return NULL;
  }

  return array->data.v_array.data[index];
}
