#pragma once
#include "stack.h"
#include <stdbool.h>

// early declaration so that we can reference object_t before its definition.
// its named mark_t because it will used by mark and sweep algorithm
typedef struct Object mark_t;

typedef enum ObjectType { INT, FLOAT, STRING, ARRAY, VECTOR3 } mark_type_t;

void mark_object_free(mark_t *obj);

typedef struct Array {
  size_t capacity;
  mark_t **data;
} mark_array_t;

// actual vector not cpp vector!!
typedef struct Vector {
  mark_t *x;
  mark_t *y;
  mark_t *z;
} mark_vector_t;

typedef union ObjectData {
  int v_int;
  float v_float;
  char *v_string;
  mark_array_t v_array;
  mark_vector_t v_vector3;
} mark_data_t;

typedef struct Object {
  bool isMarked;

  mark_type_t type;
  mark_data_t data;
} mark_t;
