#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include <getopt.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>

#include "panic_cond.h"
#include "harness.h"
#include "part1.h"

void test_pincr() {
  int old_x = random() % 100;
  int x = old_x;
  int y = incr(&x);
  panic_cond(old_x == y,
             "test incr on *p:%d\n"
             "  expected return value: %d\n"
             "  actually: %d",
             old_x, old_x, y);
  panic_cond(x == old_x + 1,
             "test incr on *p:%d\n"
             "  expected new value of *p: %d\n"
             "  actually: %d",
             old_x, old_x + 1, x);
}

void test_max(int* a, int n) {
  int index = 0;

  init_random_array(a, n, 100);
  char* sa = array_to_string(a, n);
  
  int m = INT_MIN;
  for (int i = 0; i < n; i++) {
    if (a[i] > m) m = a[i];
  }
  
  int m_actual = max(a, n);
  panic_cond(m == m_actual,
             "test max on array %s\n"
             "  expected return value %d\n"
             "  actually: %d",
             sa, m, m_actual);
  free(sa);
}

int main(int argc, char** argv)
{
  printf("part1: testing incr...\n");
  for (int i = 0; i < 10; i++) {
    test_pincr();
  }
  printf("part1: incr OK\n");

  printf("part1: testing max...\n");
  for (int i = 0; i < 4; i++) {
    int a[i];
    for (int j = 0; j < 10; j++) {
      test_max(a, i);
    }
  }
  printf("part1: max OK\n");
  
  return 0;
}
