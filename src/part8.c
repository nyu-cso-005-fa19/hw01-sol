#include <stdio.h>
#include <stdlib.h>

typedef struct list_node Node;

struct list_node {
  int data;
  Node* next;
};

void foo(Node* n) {
  free(n->next);
}

Node* create(int x, Node* n) {
  Node* n1 = malloc(sizeof(Node));
  n1->data = x;
  n1->next = n;
  
  return n1;
}

int main() {
  Node* n1 = create(1, NULL);
  Node* n2 = create(2, n1);
  
  foo(n2);
  Node* n3 = create(3, NULL);
  
  n1->data = 42;
  
  printf("%d\n", n3->data);
  free(n2);
  free(n3);
 
  return 0;
}
