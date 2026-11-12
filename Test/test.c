#include "rbt.h"

int main(){

  Tree *rbt = malloc(sizeof(Tree) * 1);
  rbt->NIL = malloc(sizeof(Node) * 1);
  rbt->NIL->data = 0;
  rbt->NIL->color = BLACK;
  rbt->NIL->left = rbt->NIL->right = rbt->NIL->parent = NULL;
  rbt->root = NULL;

  int arr[] = {7, 6, 5, 4, 3, 2, 1};

  for(int i=0; i<7; i++){
    insert(arr[i], rbt);
  }

  printf("Printing\n");
  inorder(rbt->root, rbt);
  printf("NULL\n");

  int key = 4;
  Pair ans = search(key, rbt);

  if(ans.color == -1 && ans.data == -1) puts("Tree is empty");
  else if(ans.data != key) puts("Data not found !!");
  else printf("Data found %d(%c)\n", ans.data, (ans.color == 0) ? 'B' : 'R');

  deleteBST(rbt);
  free(rbt->NIL);
  free(rbt);
  return 0;
}