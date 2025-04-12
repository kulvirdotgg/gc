#include "mark_object.h"
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
