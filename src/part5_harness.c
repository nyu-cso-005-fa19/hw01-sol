#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include <string.h>

#include "panic_cond.h"
#include "harness.h"
#include "part5.h"  

Node* generate_list(size_t len) {
  Node* head;
  init(&head);
  for (int i = 0; i < len; i++) {
    insert(&head, random() % 100);
  }
  return head;
}

void ltoa(Node* head, int* a) {
  int i = 0;
  while (head != NULL) {
    a[i] = head->data;
    i++;
    head = head->next;
  }
}

void test_length(size_t len) {
  Node* head = generate_list(len);
  int a[len];
  ltoa(head, a);
  char* sa = array_to_string(a, len);

  size_t len_actual = length(head);
  
  panic_cond(len == len_actual,
             "test length on list %s\n"
             "expected length %d, actually %d\n",
             sa, len, len_actual);

  clear(&head);
  free(sa);
}

void test_last(size_t len) {
  Node* head = generate_list(len);
  int a[len];
  ltoa(head, a);
  char* sa = array_to_string(a, len);

  Node* last_actual = last(head);

  if (len == 0) {
    panic_cond(last_actual == NULL,
               "test last on list %s\n"
               "expected last to return NULL",
               sa);
  } else {
    panic_cond(last_actual != NULL,
               "test last on list %s\n"
               "expected last to be != NULL");
    
    panic_cond(last_actual->data == a[len - 1],
               "test last on list %s\n"
               "expected last to contain %d, actually %d\n",
               sa, a[len - 1], last_actual->data);
  }
  clear(&head);
  free(sa);
}

void test_reverse(size_t len) {
  Node* head = generate_list(len);
  int a[len];
  ltoa(head, a);
  char* sa = array_to_string(a, len);

  int ar[len];
  for (int i = 0; i < len; i++) {
    ar[len - i - 1] = a[i];
  }
  
  char* sar = array_to_string(ar, len);

  Node* r = reverse(head);

  int ar_actual[len];
  ltoa(r, ar_actual);
  char* sar_actual = array_to_string(ar_actual, len);
   
  int cond = 1;
  for (int i = 0; i < len; i++) {
    cond = cond && ar[i] == ar_actual[i];
  }

  panic_cond(cond,
             "test reverse on list %s\n"
             "  expected\n"
             "  %s\n"
             "  actually\n"
             "  %s\n",
             sa, sar, sar_actual);
  
  clear(&r);
  free(sa);
  free(sar);
  free(sar_actual);
}

int main(int argc, char** argv)
{
  printf("part5: testing length...\n");
  for (int i = 0; i < 100; i++) {
    test_length(i);
  }
  printf("part5: length OK\n");

  printf("part5: testing last...\n");
  for (int i = 0; i < 100; i++) {
    test_length(i);
  }
  printf("part5: last OK\n");

  printf("part5: testing reverse...\n");
  for (int i = 0; i < 100; i++) {
    test_reverse(i);
  }
  printf("part5: reverse OK\n");
  
  return 0;
}
