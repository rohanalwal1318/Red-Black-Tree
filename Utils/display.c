#include "rbt.h"


/* Print down the nodes with color in-order fashion .. ascending data */
void inorder(Node *root, Tree *t){

  if(root == NULL) return;

  inorder(root->left, t);

  if(root != t->NIL) printf("%d(%c)-> ", root->data, (root->color) == 0 ? 'B' : 'R');

  inorder(root->right, t);

}