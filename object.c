#include "object.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

object_t *new_array(size_t capacity) {
  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "FAILED TO CREATE NEW OBJECT\n");
    return NULL;
  }

  obj->type = ARRAY;

  object_t **data = calloc(capacity, sizeof(object_t *));
  if (data == NULL) {
    fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR ARRAY\n");
    return NULL;
  }

  array_t array = {
      .capacity = capacity,
      .data = data,
  };
  obj->data.v_array = array;
  return obj;
}

bool set_array(object_t *array, size_t index, object_t *value) {
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

object_t *get_array(object_t *array, size_t index) {
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

object_t *new_vector3(object_t *x, object_t *y, object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    fprintf(stderr, "INPUT COORDINATES ARE NULL\n");
    return NULL;
  }

  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "FAILED TO CREATE NEW OBJECT\n");
    return NULL;
  }

  obj->type = VECTOR3;
  obj->data.v_vector3 = (vector_t){.x = x, .y = y, .z = z};
  return obj;
}

object_t *new_int(int value) {
  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "FAILED TO CREATE NEW OBJECT\n");
    return NULL;
  }

  obj->type = INT;
  obj->data.v_int = value;
  return obj;
}

object_t *new_float(float value) {
  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "FAILED TO CREATE NEW OBJECT\n");
    return NULL;
  }

  obj->type = FLOAT;
  obj->data.v_float = value;
  return obj;
}

object_t *new_string(char *value) {
  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "FAILED TO CREATE NEW OBJECT\n");
    return NULL;
  }

  obj->type = STRING;
  obj->data.v_string = (char *)malloc(strlen(value) + 1);
  if (obj->data.v_string == NULL) {
    fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR STRING\n");
    return NULL;
  }

  strcpy(obj->data.v_string, value);

  return obj;
}

size_t length(object_t *object) {
  switch (object->type) {
  case INT:
    return 1;
  case FLOAT:
    return 1;
  case VECTOR3:
    return 3;
  case STRING:
    return strlen(object->data.v_string);
  case ARRAY:
    return object->data.v_array.capacity;
  default:
    return -1;
  }
}

object_t *add(object_t *a, object_t *b) {
  if (a == NULL || b == NULL) {
    fprintf(stderr, "OPERANDS ARE NULL CAN'T PERFORM ADDITION OPERATION\n");
  }

  switch (a->type) {
  case INT: {
    switch (b->type) {
    case INT:
      return new_int(a->data.v_int + b->data.v_int);
    case FLOAT:
      return new_float((float)a->data.v_int + b->data.v_float);
    default:
      fprintf(stderr, "INCOMPATIBLE TYPES FOR ADD OPERATION\n");
      return NULL;
    }
  }
  case FLOAT: {
    switch (b->type) {
    case INT:
      return new_float(a->data.v_float + (float)b->data.v_int);
    case FLOAT:
      return new_float(a->data.v_float + b->data.v_float);
    default:
      fprintf(stderr, "INCOMPATIBLE TYPES FOR ADD OPERATION\n");
      return NULL;
    }
  }

  case STRING: {
    if (b->type != STRING) {
      fprintf(stderr, "TYPE INCOMPATIBLE WITH STRING\n");
      return NULL;
    }

    // +1 for NULL terminator, its C not your avg skill issue lang.
    size_t len = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;

    char *temp_str = (char *)calloc(len, sizeof(char *));

    strcat(temp_str, a->data.v_string);
    strcat(temp_str, b->data.v_string);

    // `new_string` always copies the string to create a new object.
    // So don't forget to free the `temp_str` created.
    object_t *obj = new_string(temp_str);
    free(temp_str);

    // `new_string` creates a new object in heap. So after the function call is
    // over new string created will still be there.
    // Hence returning a pointer to new string is totally fine and wouldn't
    // create any dangling pointer issue.
    return obj;
  }
  case VECTOR3: {
    if (b->type != VECTOR3) {
      fprintf(stderr, "TYPES INCOMPATIBLE FOR VECTOR ADDITION\n");
      return NULL;
    }

    return new_vector3(add(a->data.v_vector3.x, b->data.v_vector3.x),
                       add(a->data.v_vector3.y, b->data.v_vector3.y),
                       add(a->data.v_vector3.z, b->data.v_vector3.z));
  }
  case ARRAY: {
    if (b->type != ARRAY) {
      fprintf(stderr, "TYPE INCOMPATIBLE WITH ARRAY\n");
      return NULL;
    }

    size_t len = a->data.v_array.capacity + b->data.v_array.capacity;

    object_t *obj = new_array(len);

    for (size_t i = 0; i < a->data.v_array.capacity; ++i) {
      set_array(obj, i, get_array(a, i));
    }

    size_t a_len = a->data.v_array.capacity;
    for (size_t i = 0; i < b->data.v_array.capacity; ++i) {
      set_array(obj, i + a_len, get_array(b, i));
    }

    return obj;
  }
  default:
    return NULL;
  }

  return NULL;
};
