#include "rbt.h"

int status;

int main(){

  int ch, f;

  Tree *rbt = malloc(sizeof(Tree) * 1);
  rbt->NIL = malloc(sizeof(Node) * 1);
  rbt->NIL->data = 0;
  rbt->NIL->left = rbt->NIL->right = rbt->NIL->parent = NULL;
  rbt->NIL->color = BLACK;
  rbt->root = NULL;

  while(1){

    puts("1. Create a Tree");
    puts("2. Display");
    puts("3. Search a Node");
    puts("4. Find Maximum Node in Tree");
    puts("5. Find Minimum Node in Tree");
    puts("6. Delete a Node");
    puts("7. Delete Minimum Node");
    puts("8. Delete Maximum Node");
    puts("9. Exit");
    printf("Enter the Choice: ");
    scanf("%d", &ch);

    switch(ch){

      case 1 : {
        int data;
        printf("Enter the Element: ");
        scanf("%d", &data);
        f = insert(data, rbt);
        if(f == 0) puts("Insertion Failed!!");
        else puts("Successfull!!");
        break;
      }

      case 2 : {
        inorder(rbt->root, rbt);
        printf("NULL\n");
        break;
      }

      case 3 : {
        int key;
        Pair ans;
        printf("Enter the Data to Search: ");
        scanf("%d", &key);
        ans = search(key, rbt);
        if(ans.color == -1 && ans.data == -1) puts("Tree is empty");
        else if(ans.data != key) puts("Data not found !!");   /* BLACK == 0 */
        else printf("Data found %d(%c)\n", ans.data, (ans.color == 0) ? 'B' : 'R');
        break;
      }

      case 4 : {
        Pair ans = findMax(rbt);
        if(ans.color == -1 && ans.data == -1) puts("Tree is empty");
        else printf("The Maximum: %d\n", ans.data);
        break;
      }

      case 5 : {
        Pair ans = findMin(rbt);
        if(ans.color == -1 && ans.data == -1) puts("Tree is empty");
        else printf("The Minimum: %d\n", ans.data);
        break;
      }

      case 6 : {
        int key;
        printf("Enter the Data to Delete: ");
        scanf("%d", &key);
        rbt->root = delete(key, rbt->root, rbt);
        if(status) printf("\nDeleted %d\n", key);
        else printf("\n%d not found, nothing deleted\n", key);
        break;
      }

      case 7 : {
        Pair ans = findMin(rbt);
        if(ans.color == -1 && ans.data == -1) {
          puts("Tree is empty");
          break;
        }
        rbt->root = delete(ans.data, rbt->root, rbt);
        if(status) printf("\nDeleted %d\n", ans.data);
        else printf("\n%d not found, nothing deleted\n", ans.data);
        break;
      }

      case 8 : {
        Pair ans = findMax(rbt);
        if(ans.color == -1 && ans.data == -1) {
          puts("Tree is empty");
          break;
        }
        rbt->root = delete(ans.data, rbt->root, rbt);
        if(status) printf("\nDeleted %d\n", ans.data);
        else printf("\n%d not found, nothing deleted\n", ans.data);
        break;
      }

      case 9 : {
        deleteBST(rbt);
        free(rbt->NIL);
        free(rbt);
        printf("Exiting ....\n");
        return 0;
      }

    }

  }

}