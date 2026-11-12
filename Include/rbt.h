#ifndef RBT_H
#define RBT_H

#include <stdio.h>
#include <stdlib.h>

// Color enumeration
typedef enum { BLACK, RED } NodeColor;

/* Red-Black Tree node's Structure */
typedef struct Node{
  int data; /* Data which the node holds */
  NodeColor color; /* Color of that node either Red/Black */
  struct Node* parent; /* Parent pointer of the current node .. Null if root */
  struct Node* left; /* Left child pointer */
  struct Node* right; /* Right child pointer */
}Node;

/* Red-Black Tree */
typedef struct RBT{
  struct Node* root; /* Root of the tree */
  struct Node* NIL; /* NIL node */
}Tree;

typedef struct{
  int data;
  int color;
}Pair;

/* Returns NULL if failed to allocate memory, else return newnode with default values */
Node *createNode(int data, Tree *t);

/* left rotate at x */
void leftRotate(Node* x, Tree *t);

/* Right rotate at x */
void rightRotate(Node* x, Tree *t);

/* Fix insert a function or rather a loop untill the parent is RED */
void fixInsert(Tree *t, Node *newnode);

/* Insertion of node in RBT */
int insert(int data, Tree *t);

/* Search the given node in RBT, Returns {-1, -1} if tree is empty, {0, 0} if data not found, else returns the data and its color as a pair */
Pair search(int data, Tree *t);

/* Delete the node which is holding the 'data' and marks status = 1, if not found marks status = 0, Deletes nothing */
struct Node* delete(int data, Node *root, Tree *t);

/* Find the maximum node in tree */
Pair findMax(Tree *t);

/* Find the minimum node in tree */
Pair findMin(Tree *t);

/* Print the tree in-order */
void inorder(Node *root, Tree *t);

/* Delete the entire tree */
void deleteBST(Tree *t);


#endif