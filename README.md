# 🌳 Red-Black Tree in C

![Language](https://img.shields.io/badge/language-C11-blue)
![Complexity](https://img.shields.io/badge/search%20%7C%20insert%20%7C%20delete-O(log%20n)-brightgreen)
![Dependencies](https://img.shields.io/badge/dependencies-none-lightgrey)

A complete **self-balancing Red-Black Tree**, built **from scratch in C**: no libraries, no copied code. It supports insertion, deletion, search, min/max and delete-min/max, with a menu-driven program to play with it.

Every insert and delete rebalances the tree automatically, so operations stay **O(log n)** no matter what order the data arrives in.

---

## Table of contents

1. [Why a Red-Black Tree?](#why-a-red-black-tree)
2. [The 5 rules](#the-5-rules)
3. [Features](#features)
4. [How it works](#how-it-works)
5. [Project structure](#project-structure)
6. [Build and run](#build-and-run)
7. [Demo](#demo)
8. [API reference](#api-reference)
9. [Complexity](#complexity)
10. [Testing](#testing)
11. [Design decisions](#design-decisions)
12. [What I learned](#what-i-learned)
13. [Future improvements](#future-improvements)
14. [Author](#author)

---

## Why a Red-Black Tree?

A normal binary search tree (BST) is fast only while it stays bushy. Insert sorted data and it collapses into a linked list:

```
Insert 1, 2, 3, 4, 5 into a plain BST:

1
 \
  2
   \
    3
     \
      4
       \
        5        → search is now O(n), not O(log n)
```

A Red-Black Tree gives every node a colour (red or black) and keeps a few simple rules true. After each insert or delete it fixes itself using **recolouring** and **rotations**, so the height always stays around log n.

---

## The 5 rules

1. Every node is either **red** or **black**.
2. The **root** is black.
3. All leaves (NIL) are black.
4. A **red node never has a red child** (no two reds in a row).
5. Every path from a node down to its NIL leaves contains the **same number of black nodes**.

**Why this keeps the tree balanced:** the shortest possible path is all black. The longest possible path alternates black and red. Both have the same number of blacks, so the longest path is at most **twice** the shortest.

---

## Features

| Operation | Function | Status |
|---|---|---|
| Insert with rebalancing | `insert()` + `fixInsert()` | ✅ |
| Delete with rebalancing | `delete()` + `fixDelete()` | ✅ |
| Search | `search()` | ✅ |
| Find minimum / maximum | `findMin()` / `findMax()` | ✅ |
| Delete minimum / maximum | `deleteMin()` / `deleteMax()` | ✅ |
| Left / right rotation | `leftRotate()` / `rightRotate()` | ✅ |
| In-order display with colours | `inorder()` | ✅ |
| Free the whole tree | `deleteBST()` | ✅ |
| Menu-driven program | `Src/main.c` | ✅ |

---

## How it works

### Rotations (the rebalancing tool)

A rotation lifts one node up a level and pushes its parent down, **without breaking the BST order**.

```
Left rotation at X:               Right rotation at Y:

   X                 Y                Y                X
  / \               / \              / \              / \
 a   Y     ==>     X   c            X   c    ==>     a   Y
    / \           / \              / \                   / \
   b   c         a   b            a   b                 b   c
```

### Insertion

1. Insert like a normal BST and colour the new node **red** (a red node can't break rule 5).
2. If the parent is black, stop.
3. If the parent is red, look at the **uncle**:

| Uncle | Shape | Fix |
|---|---|---|
| 🔴 Red | any | Recolour parent and uncle black, grandparent red, then repeat from the grandparent |
| ⚫ Black | inner child (zig-zag) | Rotate at the parent first, which makes it a straight line |
| ⚫ Black | outer child (straight line) | Swap colours of parent and grandparent, rotate at the grandparent. Done. |

4. Finally, force the root to black.

**Example: inserting `5, 3, 8, 1, 4, 2`**

```
after 5:   5B
after 3:   5B(3R,)
after 8:   5B(3R,8R)
after 1:   5B(3B(1R,),8B)           ← red uncle, recolour only
after 4:   5B(3B(1R,4R),8B)         ← parent is black, nothing to fix
after 2:   5B(3R(1B(,2R),4B),8B)    ← red uncle again, recolour, problem moves up and stops

Final tree:
          5(B)
        /      \
      3(R)     8(B)
     /    \
   1(B)   4(B)
     \
     2(R)
```

(Notation: `value` + `B`/`R`, then `(left,right)`.)

### Deletion

1. Find the node. If it has **two children**, copy its in-order **successor's** value into it and remove the successor instead. The successor has at most one child, which makes removal simple.
2. Remove the node and put its child (or NIL) in its place.
3. If the removed node was **red**, nothing breaks. If it was **black**, one black is missing on every path through that spot. The child carries an extra black ("double black"), and `fixDelete()` removes it by looking at the **sibling**:

| Sibling | Fix |
|---|---|
| 🔴 Red | Recolour and rotate at the parent so the sibling becomes black, then continue below |
| ⚫ Black, both children black | Recolour the sibling red and push the problem up to the parent |
| ⚫ Black, near child red, far child black | Rotate at the sibling to turn this into the next case |
| ⚫ Black, far child red | Recolour and rotate at the parent. Done. |

Each case has a left-side version and a mirrored right-side version.

**Example: deleting `1` from `2B(1B,4B(3R,))`**

```
    2(B)                   2(B)                    3(B)
   /    \     remove 1         \    near child    /    \
 1(B)   4(B)  ========>        4(B)  red: rotate  2(B)  4(B)
        /                      /     + recolour
      3(R)                   3(R)
```

`deleteMin` and `deleteMax` simply find the smallest or largest value and reuse `delete()`.

---

## Project structure

```
Red-Black Tree/
├── Include/
│   └── rbt.h            # Node and Tree structs, all function declarations
├── Helper/
│   └── rbtHelper.c      # Rotations, fixInsert, fixDelete, createNode, deleteBST
├── Utils/
│   ├── Insert.c         # insert()
│   ├── delete.c         # delete(), deleteMin(), deleteMax()
│   ├── search.c         # search(), findMin(), findMax()
│   └── display.c        # inorder() with colours
├── Src/
│   └── main.c           # Menu-driven program
├── Test/
│   └── test.c           # Non-interactive test program
└── makefile
```

---

## Build and run

Requires **gcc** (any C11 compiler works).

```bash
make          # builds the executable "RBT"
./RBT         # starts the menu
make clean    # removes build files
```

The project compiles with `-Wall -Wextra -std=c11` and no warnings.

---

## Demo

```
1. Create a Tree
2. Display
3. Search a Node
4. Find Maximum Node in Tree
5. Find Minimum Node in Tree
6. Delete a Node
7. Delete Minimum Node
8. Delete Maximum Node
9. Exit
```

A sample session (insert `18, 12, 89, 14, 28`, then explore):

```
Enter the Choice: 2
12(B)-> 14(R)-> 18(B)-> 28(R)-> 89(B)-> NULL

Enter the Choice: 3
Enter the Data to Search: 14
Data found 14(R)

Enter the Choice: 4
The Maximum: 89

Enter the Choice: 6
Enter the Data to Delete: 18

Deleted 18

Enter the Choice: 2
12(B)-> 14(R)-> 28(B)-> 89(B)-> NULL

Enter the Choice: 6
Enter the Data to Delete: 500

500 not found, nothing deleted
```

Each node prints as `value(colour)` in sorted order.

---

## API reference

| Function | Description |
|---|---|
| `int insert(int data, Tree *t)` | Inserts a value and rebalances. Returns `1` on success, `0` if memory allocation fails. |
| `Node* delete(int data, Node *root, Tree *t)` | Deletes a value and rebalances. Pass `t->root` as `root`. Sets the global `status` to `1` if found and deleted, `0` if not found. Returns the new root. |
| `Pair search(int data, Tree *t)` | Returns `{data, colour}` if found, `{0, 0}` if not found, `{-1, -1}` if the tree is empty. |
| `Pair findMin(Tree *t)` / `Pair findMax(Tree *t)` | Returns the smallest / largest value with its colour, or `{-1, -1}` if the tree is empty. |
| `void deleteMin(Tree *t)` / `void deleteMax(Tree *t)` | Deletes the smallest / largest value. |
| `void inorder(Node *root, Tree *t)` | Prints the tree in sorted order with colours. |
| `void deleteBST(Tree *t)` | Frees every node. |
| `void leftRotate(Node *x, Tree *t)` / `void rightRotate(Node *x, Tree *t)` | Rotations. |
| `void fixInsert(Tree *t, Node *newnode)` / `void fixDelete(Tree *t, Node *x)` | Rebalancing after insert / delete. |

`Pair` holds `{ int data; int color; }` where `BLACK = 0` and `RED = 1`.

### Using it in your own code

```c
int status;   /* delete() reports found / not found through this global */

Tree *rbt = malloc(sizeof(Tree));
rbt->NIL = malloc(sizeof(Node));
rbt->NIL->color = BLACK;
rbt->NIL->left = rbt->NIL->right = rbt->NIL->parent = NULL;
rbt->root = NULL;

insert(10, rbt);
insert(20, rbt);
insert(30, rbt);

rbt->root = delete(20, rbt->root, rbt);
inorder(rbt->root, rbt);        /* 10(B)-> 30(R)-> */

deleteBST(rbt);
free(rbt->NIL);
free(rbt);
```

---

## Complexity

| Operation | Time | Notes |
|---|---|---|
| Search | O(log n) | |
| Insert | O(log n) | At most 2 rotations |
| Delete | O(log n) | At most 3 rotations |
| Find / delete min and max | O(log n) | |
| Space | O(n) | One node per value, plus one shared NIL |

---

## Testing

`Test/test.c` is a non-interactive program (it has its own `main`, so compile it instead of `Src/main.c`):

```bash
gcc -Wall -Wextra -std=c11 -IInclude Test/test.c Helper/rbtHelper.c Utils/*.c -o rbt_test
./rbt_test
```

It inserts `7, 6, 5, 4, 3, 2, 1` (the worst case for a plain BST), searches, finds min and max, then deletes several nodes (including one that doesn't exist) and finally runs delete-min and delete-max.

```
1(R)-> 2(B)-> 3(R)-> 4(R)-> 5(B)-> 6(B)-> 7(B)-> NULL
Data found 7(B)
Maxi - > 7
Mini - > 1

Deleted 4
1(B)-> 2(R)-> 3(R)-> 5(B)-> 6(B)-> 7(B)-> NULL
...
```

Scenarios worth trying by hand:

- **Insert:** red uncle (recolour), zig-zag (double rotation), straight line (single rotation), on both the left and right side. Try ascending, descending and random order.
- **Delete:** red leaf, black node with a red child, node with two children, value not present, the last remaining node.
- **Delete fix-up:** all four sibling cases, on both sides.
- **Delete everything** one value at a time and check the tree stays valid after each step.

---

## Design decisions

- **Sentinel NIL node.** All leaves point to one shared black NIL node, so the code never checks for `NULL` children. NIL is a real node, so it can also hold a `parent` pointer, which `fixDelete` needs.
- **Parent pointers.** Every node knows its parent, which makes finding the uncle, sibling and grandparent easy.
- **Successor copy on delete.** For a node with two children, the successor's value is copied up and the successor is removed. This reduces every delete to the "at most one child" case.
- **Empty tree is `root == NULL`.** `delete()` sets the root back to `NULL` when the last node is removed.
- **Headers, helpers and operations are separated** into `Include/`, `Helper/` and `Utils/` so each file has one job.

---

## What I learned

- Why a plain BST degrades, and how simple colour rules force balance.
- How rotations change a tree's shape without breaking its ordering.
- Why insertion needs at most two rotations, and how the "double black" idea explains deletion.
- How a sentinel node removes a whole class of NULL-pointer bugs.
- How to structure a multi-file C project with a header, helper module and makefile.

---

## Future improvements

- A validator function that checks all 5 rules after every operation.
- A function that prints the tree's actual shape (indented), not just the sorted order.
- Generic keys (strings, structs) using function pointers for comparison.
- Replace the `status` global with a return value.
- Unit tests as a `make test` target.

---

## Author

Built by [rohanalwal1318](https://github.com/rohanalwal1318) as a data structures project.

⭐ If this helped you understand Red-Black Trees, consider starring the repo.
