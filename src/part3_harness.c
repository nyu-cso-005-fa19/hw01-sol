#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include <string.h>

#include "panic_cond.h"
#include "harness.h"
#include "part3.h"  

void test_initialize_array(int* a, int n) {
  init_random_array(a, n, 100);
  initialize_array(a, n);

  for (int i = 0; i < n; i++) {
    panic_cond(a[i] != 0,
               "test array length %d, index %d: "
               "expected non-zero value, actually 0\n", n);
  }
}

void mark_multiples_gold(int *arr, int n, int p) 
{
  for (int i = 2*p; i < n; i = i+p) {
    arr[i] = 0;
  }
}


void test_mark_multiples(int* a, int n, int p) {
  initialize_array(a, n);
  //init_random_array(a, n, 2);
  char* sa = array_to_string(a, n);

  int a_gold[n];
  memcpy(a_gold, a, sizeof(int) * n);
  mark_multiples_gold(a_gold, n, p);
  
  mark_multiples(a, n, p);
  
  for (int i = 0; i < n; i++) {
    panic_cond(a[i] == a_gold[i],
               "test mark_multiples on arr:%s, p: %d\n"
               "  expected new value of arr[%d]: %d\n"
               "  actually: %d\n",
               sa, i, a_gold[i], a[i]);
  }
  
  free(sa);
}

void prime_number_sieves_gold(int *arr, int n)
{
  initialize_array(arr, n);
  
  for (int i = 2; i < n / 2; i++) {
    if (arr[i] != 0) mark_multiples_gold(arr, n, i);
  }
}


void test_prime_number_sieves(int* a, int n) {
  prime_number_sieves(a, n);
  int a_gold[n];
  prime_number_sieves_gold(a_gold, n);

  for (int i = 2; i < n; i++) {
    panic_cond(a[i] == a_gold[i],
               "test prime_number_sieves on n: %d\n"
               "  expected new value of arr[%d]: %d\n"
               "  actually: %d\n",
               n, i, a_gold[i], a[i]);
  }
}

int find_smallest_divisor_gold(int n, int *divisor)
{
  // TODO: Replace the following with your code.
  // assert(0);

  int arr[n];
  prime_number_sieves_gold(arr, n);

  for (int i = 2; i < n; i++) {
    if (arr[i] && n % i == 0) {
      *divisor = i;
      return 1;
    }
  }
  
  *divisor = n;
  return 0;
}

void test_smallest_divisor(int n) {
  int divisor, divisor_actual;
  int prime_actual = find_smallest_divisor(n, &divisor_actual);
  int prime = find_smallest_divisor_gold(n, &divisor); 
  
  panic_cond(prime == prime_actual,
             "test find_smallest_divisor with n: %d\n"
             "  expected return value: %d\n"
             "  actually: %d\n",
             n, prime, prime_actual);

  panic_cond(divisor == divisor_actual,
             "test find_smallest_divisor with n: %d\n"
             "  expected divisor: %d\n"
             "  actually: %d\n",
             n, divisor, divisor_actual);
}


int main(int argc, char** argv)
{
  printf("part3: testing initialize_array...\n");
  for (int i = 0; i < 10; i++) {
    int a[i];
    test_initialize_array(a, i);
  }
  printf("part3: initialize_array OK\n");

  printf("part3: testing mark_multiples...\n");
  for (int i = 0; i < 20; i++) {
    int a[i];
    for (int p = 2; p < i; p++) {
      test_mark_multiples(a, i, p);
    }
  }
  printf("part3: mark_multiples OK\n");
  
  printf("part3: testing prime_number_sieves...\n");
  for (int i = 0; i < 100; i++) {
    int a[i];
    test_prime_number_sieves(a, i);
  }
  printf("part3: prime_number_sieves OK\n");
  
  printf("part3: testing find_smallest_divisor...\n");
  for (int i = 0; i < 100; i++) {
    test_smallest_divisor(i);
  }
  printf("part3: find_smallest_divisor OK\n");

  return 0;
}
