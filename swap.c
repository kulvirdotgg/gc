#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a very generic swap method, could be used to swap any types.
void swap(void *one, void *two, size_t size) {
  void *temp = malloc(size);
  if (temp == NULL) {
    fprintf(stderr, "unable to allocate memory on heap for temp.");
    return;
  }

  // temp = one;
  // memcpy needs to pass the size(no of bytes) we want to copy from source
  memcpy(temp, one, size);
  // one = two;
  memcpy(one, two, size);
  // two = temp;
  memcpy(two, temp, size);

  free(temp);
}
