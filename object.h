#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// early declaration so that we can reference object_t before its definition.
typedef struct Object object_t;

typedef enum ObjectType { INT, FLOAT, STRING, ARRAY, VECTOR3 } object_type_t;

typedef struct Array {
  size_t capacity;
  object_t **data;
} array_t;

// actual vector not cpp vector!!
typedef struct Vector {
  object_t *x;
  object_t *y;
  object_t *z;
} vector_t;

typedef union ObjectData {
  int v_int;
  float v_float;
  char *v_string;
  array_t v_array;
  vector_t v_vector3;
} object_data_t;

typedef struct Object {
  int ref_count;

  object_type_t type;
  object_data_t data;
} object_t;

object_t *new_int(int value);
object_t *new_float(float value);
object_t *new_string(char *value);
object_t *new_vector3(object_t *x, object_t *y, object_t *z);
object_t *new_array(size_t capacity);
bool set_array(object_t *array, size_t index, object_t *value);
object_t *get_array(object_t *array, size_t index);
size_t length(object_t *object);
object_t *add(object_t *a, object_t *b);

void ref_count_incr(object_t *obj);
void ref_count_decr(object_t *obj);
void ref_count_free(object_t *obj);
