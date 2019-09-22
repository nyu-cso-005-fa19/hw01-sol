#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include <string.h>

#include "panic_cond.h"
#include "harness.h"
#include "part2.h"

void test_swap() {
  int old_p1 = random() % 100;
  int old_p2 = random() % 100;
  int p1 = old_p1;
  int p2 = old_p2;
  swap(&p1, &p2);
  panic_cond(old_p1 == p2,
             "test swap on *p1:%d, *p2:%d\n"
             "  expected new value of *p2: %d\n"
             "  actually: %d\n",
             old_p1, old_p2, old_p1, p2);
  panic_cond(old_p2 == p1,
             "test swap on *p1:%d, *p2:%d\n"
             "expected new value of *p1: %d\n"
             "actually: %d\n",
             old_p1, old_p2, old_p2, p1);
}

// A comparator function used by qsort 
int compare(const void * a, const void * b) 
{ 
    return ( *(int*)a - *(int*)b ); 
} 
  

void test_insertion_sort(int* a, int n) {
  init_random_array(a, n, 100);
  char* sa = array_to_string(a, n);

  int a_gold[n];
  memcpy(a_gold, a, sizeof(int) * n);

  qsort(a_gold, n, sizeof(int), &compare);
  char* sa_gold = array_to_string(a_gold, n);

  insertion_sort(a, n);
  char* sa_actual = array_to_string(a, n);
  
  for (int i = 0; i < n; i++) {
    panic_cond(a[i] == a_gold[i],
               "test insertion_sort on array %s:\n"
               "  expected: %s\n"
               "  actually: %s\n", sa, sa_gold, sa_actual);
  }
  free(sa); free(sa_gold); free(sa_actual);
}

int main(int argc, char** argv)
{
  printf("part2: testing swap...\n");
  for (int i = 0; i < 10; i++) {
    test_swap();
  }
  printf("part2: swap OK\n");

  printf("part2: teseting insertion_sort...\n");
  for (int i = 0; i < 5; i++) {
    int a[i];
    for (int j = 0; j < 10; j++) {
      test_insertion_sort(a, i);
    }
  }
  printf("part2: insertion_sort OK\n");
  
  return 0;
}
