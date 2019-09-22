#pragma once

typedef struct node Node;

struct node {
  int data;
  Node* next;
};

void init(Node** pHead);
void clear(Node** pHead);

int has_next(Node* head);
Node* get_next(Node* head);
int get_data(Node* head);

void insert(Node** pHead, int d);

size_t length(Node* head);
Node* last(Node* head);
Node* reverse(Node* head);
