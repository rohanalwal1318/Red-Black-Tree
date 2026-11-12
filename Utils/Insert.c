#include "rbt.h"

int insert(int data, Tree *t){

  /* New node Creation */
  Node *newnode = createNode(data, t);
  if(!newnode) return 0; /* allocation failed */

  /* The first node is always a root node */
  if(t->root == NULL){
    newnode->parent = NULL; /* Root doesn't have a parent */
    newnode->color = BLACK; /* Root's color is always Black */
    t->root = newnode; /* Update the root */
    return 1;
  }

  Node *temp = t->root; 

  /* Standard BST insertion Logic */
  while(1){

    if(data > temp->data){
      if(temp->right == t->NIL){
        newnode->parent = temp;
        temp->right = newnode;
        break;
      }
      temp = temp->right;
    }
    else{
      if(temp->left == t->NIL){
        newnode->parent = temp;
        temp->left = newnode;
        break;
      }
      temp = temp->left;
    }

  }

  /* If a parent is black Stop .. done and dusted */
  if(newnode->parent->color == BLACK) return 1;

  /* Now we know that the parent is not black .. red for sure, hence need to fix */
  fixInsert(t, newnode);
  
  return 1;

}