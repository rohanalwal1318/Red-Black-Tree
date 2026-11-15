#include "rbt.h"

void leftRotate(Node *x, Tree *t){

  /* y is the right child of x */
  Node *y = x->right;

  /* y's left subtree becomes x's right subtree */
  x->right = y->left;
  if(y->left != t->NIL) { 
    y->left->parent = x;
  }

  /* x's parent becomes y's parent */
  y->parent = x->parent;

  /* if x is a root node itself */
  if(x == t->root){
    t->root = y;
  }
  /* if x is the right child of its parent */
  else if(x == x->parent->right){
    x->parent->right = y;
  }
  else x->parent->left = y;

  /* put x on y's left */
  y->left = x;
  x->parent = y;

}

void rightRotate(Node *x, Tree *t){

  /* y is the right child of x */
  Node *y = x->left;

  /* y's right subtree becomes x's left subtree */
  x->left = y->right;
  if(y->right != t->NIL) { 
    y->right->parent = x;
  }

  /* x's parent becomes y's parent */
  y->parent = x->parent;

  /* if x is a root node itself */
  if(x == t->root){
    t->root = y;
  }
  /* if x is the right child of its parent */
  else if(x == x->parent->right){
    x->parent->right = y;
  }
  else x->parent->left = y;

  /* put x on y's right */
  y->right = x;
  x->parent = y;

}


void fixInsert(Tree *t, Node *newnode){

  Node *temp = newnode, *uncle;

  while(temp != t->root && temp->parent->color == RED){

    Node *parent = temp->parent;
    Node *grand = parent->parent;   /* always exists: a red parent can never be the root */

    if(parent == grand->left) uncle = grand->right;
    else uncle = grand->left;

    /* Check uncle's Color*/

    /* Case 1 - RED { Just recolouring needs to be done }*/
    if(uncle->color == RED){
      parent->color = BLACK;
      uncle->color = BLACK;
      grand->color = RED;
      temp = grand;
      continue;
    }
    
    /* Uncle is BLACK (or NIL) from here on */

    if(parent == grand->left){  /* parent is a LEFT child */

      /* Case 3 - inner child (left-right): rotate left at parent,
         it becomes a straight line, then Case 2 finishes the job */
      if(temp == parent->right){
        leftRotate(parent, t);
        temp = parent; /* old parent is now the outer child */
        continue;
      }

      /* Case 2 - outer child (left-left): swap colours, rotate right at grandparent */
      int ttt = parent->color;
      parent->color = grand->color;
      grand->color  = ttt;
      rightRotate(grand, t);
      break;

    }
    else{  /* parent is a RIGHT child */

      /* Case 3 - inner child (right-left): rotate right at parent */
      if(temp == parent->left){
        rightRotate(parent, t);
        temp = parent;
        continue;
      }

      /* Case 2 - outer child (right-right): swap colours, rotate left at grandparent */
      int ttt = parent->color;
      parent->color = grand->color;
      grand->color  = ttt;
      leftRotate(grand, t);
      break;
    }
  }

  t->root->color = BLACK;  /* always safe */   

}


/* x is carrying an extra black (double black), keep fixing till it is gone */
void fixDelete(Tree *t, Node *x){

  Node *s; /* sibling of x */

  while(x != t->root && x->color == BLACK){

    if(x == x->parent->left){  /* x is a LEFT child */

      s = x->parent->right;

      /* Case 1 - sibling is RED: rotate so that the sibling becomes BLACK */
      if(s->color == RED){
        s->color = BLACK;
        x->parent->color = RED;
        leftRotate(x->parent, t);
        s = x->parent->right;  /* new sibling */
      }

      /* Case 2 - sibling BLACK and both its children BLACK: push the extra black up */
      if(s->left->color == BLACK && s->right->color == BLACK){
        s->color = RED;
        x = x->parent;
      }
      else{

        /* Case 3 - near child RED, far child BLACK: rotate the sibling to make it a Case 4 */
        if(s->right->color == BLACK){
          s->left->color = BLACK;
          s->color = RED;
          rightRotate(s, t);
          s = x->parent->right;
        }

        /* Case 4 - far child RED: rotate at parent and recolour, extra black is gone */
        s->color = x->parent->color;
        x->parent->color = BLACK;
        s->right->color = BLACK;
        leftRotate(x->parent, t);
        x = t->root;  /* done, come out of the loop */

      }

    }
    else{  /* x is a RIGHT child, same as above with left and right swapped */

      s = x->parent->left;

      /* Case 1 */
      if(s->color == RED){
        s->color = BLACK;
        x->parent->color = RED;
        rightRotate(x->parent, t);
        s = x->parent->left;
      }

      /* Case 2 */
      if(s->left->color == BLACK && s->right->color == BLACK){
        s->color = RED;
        x = x->parent;
      }
      else{

        /* Case 3 */
        if(s->left->color == BLACK){
          s->right->color = BLACK;
          s->color = RED;
          leftRotate(s, t);
          s = x->parent->left;
        }

        /* Case 4 */
        s->color = x->parent->color;
        x->parent->color = BLACK;
        s->left->color = BLACK;
        rightRotate(x->parent, t);
        x = t->root;

      }

    }

  }

  /* If x is RED it just turns BLACK (extra black absorbed), also keeps the root BLACK */
  x->color = BLACK;

}

/* Returns NULL if failed to allocate memory, else return newnode with default values */
Node *createNode(int data, Tree *t){

  Node *newnode = malloc(sizeof(Node) * 1);
  if(!newnode) return NULL;
  newnode->data = data;
  newnode->color = RED;
  newnode->left = t->NIL;
  newnode->parent = t->NIL;
  newnode->right = t->NIL;

  return newnode;

}

/* Recursive deletion using post-order traversal */
void freeNodes(Node *root, Tree *t){

  if(root == t->NIL) return;

  freeNodes(root->left, t);

  freeNodes(root->right, t);

  free(root);

}

/* Delete the entire binary search tree ... a wrapper */
void deleteBST(Tree *t){

  if(t->root == NULL) return;

  freeNodes(t->root, t);

  t->root = NULL;

}