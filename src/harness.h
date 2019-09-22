#pragma once

#include <string.h>

void init_random_array(int* a, int n, int p) {
  for (int i = 0; i < n; i++) {
    a[i] = random() % p;
  }  
}

char* array_to_string(int* a, int n) {
  char* sa = malloc(sizeof(char) * n * 5 + 3);
  assert(sa != 0);
  int index = 0;
  index += sprintf(sa + index, "[");
  for (int i = 0; i < n; i++) {
    if (i < n - 1) index += sprintf(sa + index, "%d, ", a[i]);
    else index += sprintf(sa + index, "%d", a[i]);
  }
  index += sprintf(sa + index, "]");
  return sa;
}
