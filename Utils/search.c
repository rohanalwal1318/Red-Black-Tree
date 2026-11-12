#include "rbt.h"

Pair search(int data, Tree *t){

  if(t->root == NULL) return (Pair){-1, -1};

  Node *temp = t->root;

  while(temp != t->NIL){

    if(temp->data == data) return (Pair){data, temp->color};

    if(data > temp->data) temp = temp->right;

    else temp = temp->left;

  }

  return (Pair){0, 0};

}

Pair max(Node *root, Tree *t){

  if(root->right == t->NIL) return (Pair){root->data, root->color};

  return max(root->right, t);

}

Pair findMax(Tree *t){

  if(t->root == NULL){
    puts("Tree is Empty !!");
    return (Pair){-1, -1};
  }

  return max(t->root, t);

}

Pair min(Node *root, Tree *t){

  if(root->left == t->NIL) return (Pair){root->data, root->color};

  return min(root->left, t);
}

Pair findMin(Tree *t){

  if(t->root == NULL){
    puts("Tree is Empty !!");
    return (Pair){-1, -1};
  }

  return min(t->root, t);
}