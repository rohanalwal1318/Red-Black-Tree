#include "rbt.h"

extern int status;

Node* delete(int data, Node *root, Tree *t){

  /* Empty tree, nothing to delete */
  if(root == NULL || root == t->NIL){
    status = 0;
    return NULL;
  }

  /* Search for the node which holds the data */
  Node *z = root;
  while(z != t->NIL && z->data != data){
    if(data > z->data) z = z->right;
    else z = z->left;
  }

  /* Data is not in the tree, so change nothing */
  if(z == t->NIL){
    status = 0;
    return t->root;
  }

  status = 1;

  /* Two children: copy the successor's data here and remove the successor node instead */
  if(z->left != t->NIL && z->right != t->NIL){
    Node *succ = z->right;
    while(succ->left != t->NIL) succ = succ->left;
    z->data = succ->data;
    z = succ;
  }

  /* Now z has at most one child, x is that child (NIL if it has none) */
  Node *x;
  if(z->left != t->NIL) x = z->left;
  else x = z->right;

  /* Put x in z's place, NIL is a real node so it can hold a parent too */
  x->parent = z->parent;

  if(z == t->root) t->root = x;
  else if(z == z->parent->left) z->parent->left = x;
  else z->parent->right = x;

  /* Remember z's colour before it is gone */
  NodeColor removedColor = z->color;
  free(z);

  /* That was the last node, tree is empty now */
  if(t->root == t->NIL){
    t->root = NULL;
    return NULL;
  }

  /* Removing a RED node breaks nothing, a BLACK one leaves x with an extra black to fix */
  if(removedColor == BLACK) fixDelete(t, x);

  return t->root;

}


void deleteMax(Tree *t){

  Pair ans = findMax(t);

  if(ans.data == -1 && ans.color == -1) return;

  delete(ans.data, t->root, t);

  if(status == 1) puts("Maximum node deleted Successfully!!!");
  else puts("Failed!!");

}

void deleteMin(Tree *t){

  Pair ans = findMin(t);

  if(ans.data == -1 && ans.color == -1) return;

  delete(ans.data, t->root, t);

  if(status == 1) puts("Minimum node deleted Successfully!!!");
  else puts("Failed!!");

}