#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include <string.h>
#include <math.h>

#include "panic_cond.h"
#include "harness.h"
#include "part6.h"  

// A comparator function used by qsort 
int compare(const void * a, const void * b) 
{ 
    return ( *(int*)a - *(int*)b ); 
} 

Node* generate_tree(size_t len, size_t* len1, int* aseq, int* a) {
  Node* root;
  init(&root);
  for (int i = 0; i < len; i++) {
    int d = random() % 100;
    insert(&root, d);
    aseq[i] = d;
    a[i] = d;
  }
  
  qsort(a, len, sizeof(int), &compare);

  int prev = -1;
  int dupl = 0;
  int i = 0;
  while (i < len - dupl) {
    if (a[i] == prev) {
      for (int j = i; j < len - 1; j++) {
        a[j] = a[j + 1];
      }
      dupl++;
    } else {
      prev = a[i];
      i++;
    }
  }

  for (int i = len - dupl; i < len; i++) a[i] = -1;
  *len1 = len - dupl;
  return root;
}

void clear_gold(Node* root) {
  if (root == NULL) return;
  clear_gold(get_left(root));
  clear_gold(get_right(root));
  free(root);
}

int ttoa_helper(Node* head, int* a, int i) {
  if (head == NULL) return i;
  int il = ttoa_helper(get_left(head), a, i);  
  a[il] = get_data(head);
  return ttoa_helper(get_right(head), a, il + 1);
}

void ttoa(Node* head, int* a, int len) {
  int len1 = ttoa_helper(head, a, 0);
  for (int i = len1; i < len; i++) a[i] = -1;
}

void test_insert(size_t len) {
  int a[len];
  int aseq[len];
  size_t len1;
  Node* root = generate_tree(len, &len1, aseq, a);
  int a_actual[len];
  ttoa(root, a_actual, len);
  char* sa = array_to_string(a, len1);
  char* saseq = array_to_string(aseq, len);
  char* sa_actual = array_to_string(a_actual, len1);

  int cond = 1;
  for (int i = 0; i < len && cond; i++) {
    cond = cond && a[i] == a_actual[i];
  }
  panic_cond(cond,
             "test insert sequence %s into empty tree\n"
             "expected: %s\n"
             "actually: %s\n",
             saseq, sa, sa_actual);

  if (len > 0) {
    int res = insert(&root, a[0]);
    panic_cond(res == 0,
               "test insert(t, %d) where t is %s\n"
               "expected return value %d, actually %d",
               a[0], sa_actual, 0, res);

    res = insert(&root, a[0] - 1);
    panic_cond(res == 1,
               "test insert(t, %d) where t is %s\n"
               "expected return value %d, actually %d",
               a[0] - 1, sa_actual, 1, res);
  }
  clear_gold(root);
  free(sa);
  free(sa_actual);
}

void test_delete_min(size_t len) {
  int a[len];
  int aseq[len];
  size_t len1;
  Node* root = generate_tree(len, &len1, aseq, a);
  char* saseq = array_to_string(aseq, len);

  Node* min;
  root = delete_min(root, &min);
  int a_actual[len1];
  ttoa(root, a_actual, len1);
  char* sa_actual = array_to_string(a_actual, len1 - 1);
  char* sa_expected = array_to_string(a+1, len1 - 1);
  
  int cond = a[0] == get_data(min);
  for (int i = 1; i < len1 && cond; i++) {
    cond = cond && a[i] == a_actual[i - 1];
  }
  panic_cond(cond,
             "test delete_min(t) where t is obtained from %s\n"
             "  expected: %d, %s\n"
             "  actually: %d, %s\n",
             saseq, a[0], sa_expected, get_data(min), sa_actual);

  clear_gold(root);
  free(saseq);
  free(sa_actual);
}

void test_delete(size_t len) {
  int a[len];
  int aseq[len];
  size_t len1;
  Node* root = generate_tree(len, &len1, aseq, a);
  char* saseq = array_to_string(aseq, len);

  int i = len1 > 0 ? random() % len1 : 0;

  int k = random() % 2;

  int del = i < len && a[i] + k == a[i] || i < ((int) len1) - 1 && a[i] + k == a[i + 1];

  int x = i < len1 ? a[i] + k : 0;

  int del_actual = delete(&root, x);

  int len2 = ((int) len1) - del > 0 ? len1 - del : 0;
  int a_expected[len2];

  int seen = 0;
  for (int j = 0; j < len2; j++) {
    seen = seen || a[j] == x;
    if (!seen) a_expected[j] = a[j];
    else a_expected[j] = a[j + 1];
  }
  char* sa_expected = array_to_string(a_expected, len2);

  int a_actual[len2];
  ttoa(root, a_actual, len2);  
  char* sa_actual = array_to_string(a_actual, len2);

  int cond = 1;
  for (int i = 0; i < len2 && cond; i++) {
    cond = cond && a_expected[i] == a_actual[i];
  }
  
  panic_cond(cond,
             "test delete(t, %d) where t is obtained from %s\n"
             "  expected: %d, %s\n"
             "  actually: %d, %s\n",
             x, saseq, del, sa_expected, del_actual, sa_actual);

  clear_gold(root);
  free(saseq);
  free(sa_actual);
  free(sa_expected);
}

void test_clear(size_t len) {
  int a[len];
  int aseq[len];
  size_t len1;
  Node* root = generate_tree(len, &len1, aseq, a);
  clear(root);
}

int main(int argc, char** argv)
{
  printf("part6: testing get_left, get_right, get_data, insert...\n");
  for (int i = 0; i < 100; i++) {
    test_insert(i);
  }
  printf("part6: get_left OK\n");
  printf("part6: get_right OK\n");
  printf("part6: get_data OK\n");
  printf("part6: insert OK\n");
  
  printf("part6: testing delete_min...\n");
  for (int i = 1; i < 100; i++) {
    test_delete_min(i);
  }
  printf("part6: delete_min OK\n");
  
  printf("part6: testing delete...\n");
  for (int i = 0; i < 100; i++) {
    test_delete(i);
  }
  printf("part6: delete OK\n");

  printf("part6: testing clear...\n");
  for (int i = 0; i < 100; i++) {
    test_clear(i);
  }
  printf("part6: clear OK\n");

  return 0;
}
