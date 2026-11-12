#include "rbt.h"

extern int status;

Node* delete(int data, Node *root, Tree *t){

  if(root == NULL || root == t->NIL){
    status = 0;
    return NULL;
  }

  if(data > root->data){
    root->right = delete(data, root->right, t);
  }
  else if(data < root->data){
    root->left = delete(data, root->left, t);
  }
  else{

    if(root->left == NULL){
      Node *temp = root->right;
      free(root);
      status = 1;
      return temp;
    }

    if(root->right == NULL){
      Node *temp = root->left;
      free(root);
      status = 1;
      return temp;
    }

    else{
      Node *succ = root->right;
      while(succ->left) succ = succ->left;
      root->data = succ->data;
      root->right = delete(succ->data, root->right, t);
    }

  }

}