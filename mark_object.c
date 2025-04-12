#include "mark_object.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mark_t *_create_object(vm_t *vm) {
  mark_t *obj = malloc(sizeof(mark_t));
  if (obj == NULL) {
    fprintf(stderr, "FAILED TO CREATE NEW MARK OBJECT\n");
    return NULL;
  }

  track_object(vm, obj);
  return obj;
}

mark_t *new_array(vm_t *vm, size_t capacity) {
  mark_t *obj = _create_object(vm);
  obj->type = ARRAY;

  mark_t **data = calloc(capacity, sizeof(mark_t *));
  if (data == NULL) {
    fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR ARRAY\n");
    return NULL;
  }

  mark_array_t array = {
      .capacity = capacity,
      .data = data,
  };
  obj->data.v_array = array;
  return obj;
}

mark_t *new_vector3(vm_t *vm, mark_t *x, mark_t *y, mark_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    fprintf(stderr, "INPUT COORDINATES ARE NULL\n");
    return NULL;
  }

  mark_t *obj = _create_object(vm);
  obj->type = VECTOR3;
  obj->data.v_vector3 = (mark_vector_t){.x = x, .y = y, .z = z};

  return obj;
}

mark_t *new_int(vm_t *vm, int value) {
  mark_t *obj = _create_object(vm);
  obj->type = INT;
  obj->data.v_int = value;
  return obj;
}

mark_t *new_float(vm_t *vm, float value) {
  mark_t *obj = _create_object(vm);
  obj->type = FLOAT;
  obj->data.v_float = value;
  return obj;
}

mark_t *new_string(vm_t *vm, char *value) {
  mark_t *obj = _create_object(vm);
  obj->type = STRING;

  obj->data.v_string = (char *)malloc(strlen(value) + 1);
  if (obj->data.v_string == NULL) {
    fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR STRING\n");
    return NULL;
  }

  strcpy(obj->data.v_string, value);

  return obj;
}
