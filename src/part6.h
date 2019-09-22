#pragma once

typedef struct tree_node Node;

struct tree_node {
  int data;
  Node* left;
  Node* right;
};

void init(Node** root);
Node* get_left(Node* n);
Node* get_right(Node* n);
int get_data(Node* n);
int insert(Node** root, int d);
Node* delete_min(Node* root, Node** min);
int delete(Node** root, int d);
void clear(Node *root);
