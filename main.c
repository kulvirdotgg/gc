#include "swap.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("--- Main Function I am inside you ---\n");

  char str1[] = "I am a string.";
  char str2[] = "I am b string.";

  size_t size = strlen(str1) + 1;
  swap(str1, str2, size);
  printf("first: %s \nsecond: %s\n", str1, str2);

  return 0;
}
