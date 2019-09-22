#include <stdio.h>

void foo() {
  int i;
  printf("%d ", i++);
}

int main() {
  int j = 1;
  while (j <= 10) {
    foo();
    j = j + 1;
  }
}
