#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "part6.h"

/* In part6.c you will implement a sorted binary tree
 A binary tree is a tree in which each node has 
 at most two children (referred to as left and right).
 Each node also holds a user value (which is an int value in 
 this exercise).  In a sorted binary tree, for each node n, the values stored
 in the nodes of the left subtree of n are smaller than n's value and the
 values stored in the nodes of the right subtree of n are greater. Note
 that the ordering is strict, i.e., we do not allow duplicate values in
 the tree.

 Binary trees can be complicated if one is to keep them balanced.
 They are much simpler if we don't care about balancing. You will 
 implement the simple, unbalanced binary in this exercise.
 Specifically, after inserting 3, 7, 5, 8 (in the order specified),
 your binary tree will look like this simplified representation:
       3
        \
	 7
	/ \
       5   8

Your task: implement functions get_left, get_right, get_data, insert, delete, delete_min, and clear
*/

void init(Node** root) {
  *root = NULL;
}

// get_left returns a pointer to the left child node of the node pointed to by n
Node* get_left(Node* n) {
  // assert(0);
  // return NULL;
  return n->left;
}

// get_right returns a pointer to the right child node of the node pointed to by n
Node* get_right(Node* n) {
  // assert(0);
  // return NULL;
  return n->right;
}

// get_data returns the int value stored at the node pointed to by n
int get_data(Node* n) {
  // assert(0);
  // return 0;
  return n->data;
}


// new_node allocates a new tree node and initializes its fields properly.
// In particular, it will store the given value d in the new node.
// Note: before implementing this function, you must decide what 
// fields the tree node should contain and complete the 
// type definition of tree_node in part6.h
static Node* new_node(int d) 
{
  // TODO: Replace the following with your code.
  // assert(0);
  // return NULL;
  Node* n = malloc(sizeof(Node));
  n->left = NULL;
  n->right = NULL;
  n->data = d;
  return n;
}

// insert stores a value d in the sorted binary tree,
// specified by its root (*root).
// It returns 1 if d has been successfully inserted 
// (i.e. d was not already present in the tree)
// It returns 0 if d has not been inserted (because it was already present).
// If the tree was empty before insertion, *root is set to the new root node.
int insert(Node** root, int d)
{
  // TODO: Replace the following with your code.
  Node* parent = NULL;
  Node* curr = *root;
  int go_left = 0;
  while (curr != NULL) {
    parent = curr;
    go_left = d < curr->data;
    if (go_left) {
      curr = curr->left;
    } else if (curr->data < d) {
      curr = curr->right;
    } else {
      return 0;
    }
  }
  if (parent == NULL) {
    Node* n = new_node(d);
    *root = n;
    return 1;
  } else {
    Node* n = new_node(d);
    if (go_left) {
      parent->left = n;
    } else {
      parent->right = n;
    }
    return 1;
  }
}

// delete_min removes the node with the minimum value from the tree rooted at root.
// It returns a pointer to the root of the new tree after the removal
// Additionally, it sets the value of the variable pointed to by min to the
// removed node.
//
// delete_min assumes that root is not NULL (i.e. the tree is non-empty).
//
// For example, for the tree below
//      3
//       \
//	  7
//	 / \
//      5   8
//
// delete_min will return a pointer to the root of the new tree
//	 7
//	/ \
//     5   8
// and sets min to point to the node storing 3.
//
// Here is another example:
//       7
//      / \
//     5   8
//    /
//   3
// In this case, delete_min will again return a pointer to the root of the tree
//       7
//      / \
//     5   8
// and set min to point to the node storing 3.
// If the input tree only contains a single node, delete_min should return
// NULL and set min to root.
Node* delete_min(Node* root, Node** min)
{
  // TODO: Replace the following with your code.
  //assert(0);
  //return NULL;
  Node* parent = NULL;
  Node* curr = root;
  while (curr->left != NULL) {
    parent = curr;
    curr = curr->left;
  }
  *min = curr;
  if (parent != NULL) {
    parent->left = curr->right;
    return root;
  } else {
    return root->right;
  }
}

// delete searches for and removes the value d from the sorted binary tree,
// specified by its root (*root).
// It returns 1 if d was present in the tree and 0 otherwise.
// Additionally, it sets *root to the new root of the tree obtained after deletion.
//
// For example, for the tree below
//      3
//       \
//	  7
//	 / \
//      5   8
//
// A call to delete with value 2 will return 0 and leave the tree
// and *root unchanged.
// A call to delete with value 3 will return 1, modify the tree to
//	  7
//	 / \
//      5   8
// and set *root to the node storing 7.
// A call to delete with value 7 on the original tree will return 1
// and modify the tree to
//      3
//       \
//	  5
//	   \
//          8
// but leave *root unchanged.
//
// Do not forget to free the removed node.
// Hint: use delete_min to handle one of the cases.
int delete(Node** root, int d) {
  Node* parent = NULL;
  Node* curr = *root;

  int go_left = 0;
  while (curr != NULL && curr->data != d) {
    parent = curr;
    go_left = d < curr->data;
    if (go_left) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  if (curr == NULL) return 0;

  Node* min;

  if (curr->right != NULL) {
    Node* min_right = delete_min(curr->right, &min);
    min->right = min_right;
    min->left = curr->left;
  } else {
    min = curr->left;
  }

  if (parent != NULL) {
    if (go_left) parent->left = min;
    else parent->right = min;
  } else {
    *root = min;
  }

  free(curr);
  
  return 1;
}

// clear de-allocates all nodes in the tree rooted at the node pointed to by root
void clear(Node *root)
{
  // TODO: Replace the following with your code.
  // assert(0)
  if (root == NULL) return;
  clear(root->left);
  clear(root->right);
  free(root);
}
