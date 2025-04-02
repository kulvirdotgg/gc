#include "ref_count.c"
#include <stdio.h>

int main() {
  printf("--- Main Function I am inside you ---\n");

  gc();

  return 0;
}
