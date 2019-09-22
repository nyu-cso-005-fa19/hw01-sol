#include <assert.h>

// Your task: implement functions swap and insertion_sort

// Swap the values of the integer variables pointed to by p1 and
// p2.  After the function returns, the variable pointed to by p1
// should have the value once pointed to by p2, and vice-versa.
void swap(int *p1, int *p2)
{
  assert(p1 != 0);
  assert(p2 != 0);
  
  // TODO: Replace the following with your code.
  //assert(0);
  int t = *p2;
  *p2 = *p1;
  *p1 = t;
}

// insertion_sort implements the insertion sort algorithm.
// https://en.wikipedia.org/wiki/Insertion_sort
// It is given an integer array "arr" of "n" elements. 
// Upon return, the integer array should contain the sorted numbers
// in increasing order. 
// You should use the previous swap function when implementing insertion_sort
void insertion_sort(int *arr, int n)
{
  // TODO: Replace the following with your code.
  //assert(0);
  for (int i = 1; i < n; i++) {
    int j = i;
    for (int j = i; j > 0 && arr[j-1] > arr[j]; j--) {
      swap(arr + j - 1, arr + j);
    }
  }
}
