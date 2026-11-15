#include "rbt.h"

int status; /* delete() sets this: 1 if the data was found and deleted, 0 if not found */

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

  int key = 7;
  Pair ans = search(key, rbt);

  if(ans.color == -1 && ans.data == -1) puts("Tree is empty");
  else if(ans.data != key) puts("Data not found !!");   /* BLACK == 0 */
  else printf("Data found %d(%c)\n", ans.data, (ans.color == 0) ? 'B' : 'R');

  ans = findMax(rbt);

  printf("Maxi - > %d\n", ans.data);

  ans = findMin(rbt);

  printf("Mini - > %d\n", ans.data);

  /* Delete a few nodes (100 is not in the tree on purpose) */
  int del[] = {4, 100, 7, 1, 6};

  for(int i=0; i<5; i++){
    rbt->root = delete(del[i], rbt->root, rbt);

    if(status) printf("\nDeleted %d\n", del[i]);
    else printf("\n%d not found, nothing deleted\n", del[i]);

    inorder(rbt->root, rbt);
    printf("NULL\n");
  }

  deleteMax(rbt);
  deleteMin(rbt);
  inorder(rbt->root, rbt);

  deleteBST(rbt);
  free(rbt->NIL);
  free(rbt);
  return 0;
}