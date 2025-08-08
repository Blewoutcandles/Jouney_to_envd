#include <bits/stdc++.h>
/************************************************************ AVL (Adelson-Velsky and Landis) trees************************************** */
//about the rotations to make the tree balanced (which means having balanced right and left subtrees)
using std :: cout;
using std :: cin;
using std :: endl;
using std :: vector;
using std :: unordered_map; 
using std :: map;
using std :: sort;
using std :: max;
using std :: min;

class treenode{
  public:
    int val;
    treenode* leftchild;
    treenode* rightchild;
    int height;
    
    treenode(int value): leftchild(nullptr), rightchild(nullptr), val(value), height(1){}
    ~treenode(){}
};

void LLrotation(treenode** root){
  treenode*p = *root;
  treenode* pl = (*root) -> leftchild;
  
  p -> leftchild = pl -> rightchild; //inorder successor
  pl -> rightchild = p;
  *root = pl;

  p -> height = 1 + max(getheight(p -> leftchild), getheight(p -> rightchild));
  pl -> height = 1 + max(getheight(pl -> leftchild), getheight(pl -> rightchild));

}

void RRrotation(treenode**root){
  treenode*p = *root;
  treenode* pr = (*root) -> rightchild;
  
  p -> rightchild = pr -> leftchild; //inorder successor
  pr -> leftchild = p;
  *root = pr;

  p -> height = 1 + max(getheight(p -> leftchild), getheight(p -> rightchild));
  pr -> height = 1 + max(getheight(pr -> leftchild), getheight(pr -> rightchild));

}

void LRrotation(treenode **root){
  treenode* p = *root;
  treenode* pl = p -> leftchild;
  treenode* plr = pl -> rightchild;

  pl -> rightchild = plr -> leftchild;
  p -> leftchild = plr -> rightchild;
  plr -> leftchild = pl;
  plr -> rightchild = p;
  *root = plr;
  p -> height = 1 + max(getheight(p -> leftchild), getheight(p -> rightchild));
  pl -> height = 1 + max(getheight(pl -> leftchild), getheight(pl -> rightchild));
  plr -> height = 1 + max(getheight(plr -> leftchild), getheight(plr -> rightchild));

}

void RLrotation(treenode ** root){
  treenode* p = *root;
  treenode* pr = p -> rightchild;
  treenode* prl = pr -> leftchild;

  pr -> leftchild = prl -> rightchild;
  p -> rightchild = prl -> leftchild;
  prl -> leftchild = p;
  prl -> rightchild = pr;
  *root = prl;

  p -> height = 1 + max(getheight(p -> leftchild), getheight(p -> rightchild));
  pr -> height = 1 + max(getheight(pr -> leftchild), getheight(pr -> rightchild));
  prl -> height = 1 + max(getheight(prl -> leftchild), getheight(prl -> rightchild));
}

int getheight(treenode* root){
  return root? root -> height : -1; //-1 indicate no node (nullptr)
}

int balanceFactor(treenode* node){
  int hl = node && node->leftchild? node -> leftchild -> height : 0;
  int hr = node && node->rightchild? node -> rightchild -> height : 0;

  return hl - hr;

}

void Insert_into_binary_tree(treenode** root, int insertion_value){
  if(root && *root == NULL){
    *root = new treenode(insertion_value);
    return;
  }

  if(insertion_value < (*root) -> val){ //here -> have higher precedence then *
    Insert_into_binary_tree(&(*root) -> leftchild, insertion_value);
  }else{
    Insert_into_binary_tree(&(*root) -> rightchild, insertion_value);
  }

  (*root) -> height = 1 + max(getheight((*root) -> leftchild), getheight((*root) -> rightchild));

  int balancefactor = balanceFactor(*root);
  int balancefactor_leftchild = balanceFactor((*root)->leftchild);
  int balancefactor_rightchild = balanceFactor((*root) -> rightchild);

  //perform rotation wherever there is an imbalance occurs
  if(balancefactor == 2){
    if(balancefactor_leftchild == 1){
      LLrotation(root);
    }else if(balancefactor_leftchild == -1){
      LRrotation(root);
    }
  }else if(balancefactor == -2){
    if(balancefactor_rightchild == 1){
      RLrotation(root);
    }else if(balancefactor_rightchild == -1){
      RRrotation(root);
    }
  }
  
}

int getPredecessorValue(treenode* node){

  while(node && node -> rightchild != nullptr){
    node = node -> rightchild;//find the rightmost child of the leftsubtree
  }

  return node -> val;
}

int getSuccessorValue(treenode* node){

  while(node->leftchild != nullptr){
    node = node -> leftchild;//find the leftmost child of the rightsubtree
  }

  return node -> val;
}

treenode* delete_from_binary_tree(treenode* node, int deletekey){
  if(node == nullptr){
    return nullptr;
  }

  if(node -> val > deletekey){
    node -> leftchild = delete_from_binary_tree(node -> leftchild, deletekey);
  }else if(node -> val < deletekey){
    node -> rightchild = delete_from_binary_tree(node -> rightchild, deletekey);
  }
  else{
    //if the current node contains the values delete the key and replace it with the inorder successor or predecessor
    //check the height of leftsubtree and rightsubtree. take the predecessor or successor from the greater subtree
    if(node -> leftchild == nullptr && node -> rightchild == nullptr){
      delete node;
      return nullptr;
    }

    int heightof_leftsubtree = getheight(node -> leftchild);
    int heightof_rightsubtree = getheight(node -> rightchild);

    if(heightof_leftsubtree > heightof_rightsubtree){
      //if the leftsubtree is taller then delete the node (predecessor)
      node -> val = getPredecessorValue(node -> leftchild);
      node -> leftchild = delete_from_binary_tree(node -> leftchild, node -> val);
    }else if(heightof_leftsubtree <= heightof_rightsubtree){
      node -> val = getSuccessorValue(node -> rightchild);
      node -> rightchild = delete_from_binary_tree(node -> rightchild, node -> val);
    }
  }
  
  node -> height = 1+ std:: max(getheight(node -> leftchild), getheight(node -> rightchild));

  int balancefactor = balanceFactor(node);
  int balancefactor_leftchild = balanceFactor(node ->leftchild);
  int balancefactor_rightchild = balanceFactor(node -> rightchild);

  //perform rotation wherever there is an imbalance occurs
  if(balancefactor == 2){
    if(balancefactor_leftchild >= 0){
      LLrotation(&node);
    }else if(balancefactor_leftchild == -1){
      LRrotation(&node);
    }
  }else if(balancefactor == -2){
    if(balancefactor_rightchild > 0){
      RLrotation(&node);
    }else if(balancefactor_rightchild <= 0){
      RRrotation(&node);
    }
  }

  return node;

}

int main(){
  //create a avl tree with ll, rr, lr, rl rotations
  treenode* root = nullptr;

  Insert_into_binary_tree(&root, 30);
  Insert_into_binary_tree(&root, 50);
  Insert_into_binary_tree(&root, 10);

  Insert_into_binary_tree(&root, 40);
  Insert_into_binary_tree(&root, 50);

  root = delete_from_binary_tree(root, 10);
  
  delete root;

  return 0;
}

/*rough notes: 
LL rotations:
  performing the ll rotations means bringing the left child to the root position and the root node to the right child
  
      30
     /
   20
  /
10

Insertion design of the avl tree

[Start]
   |
[Insert as BST]
   |
[Update height]
   |
[Calculate balance factor]
   |
[Is balanced?] --Yes--> [End]
   |
  No
   |
[Which case?]
   |         |         |         |
  LL        RR        LR        RL
   |         |         |         |
[Right]   [Left]   [Left-]   [Right-]
[Rotate]  [Rotate] [Right]   [Left]
                   [Rotate]  [Rotate]
   |
[End]


Insert node and height update

30  height = 0
create the  node and assign the value

now add 20 

20 less than 30

    30, 1 + max(height(leftchild), height(rightchild)) = 1 + max(0, -1 /*no right child/*) = 1 + 1 = 2
   /
  20 

  ok now add 10
        30 1+max(l, r) = 1+max(leftchildheight = 1, rightchildheight = -1) = 1 + 1 = 2 
       /
      20 1+ max(l, r) = 1 + max(leftchildheight = 0, rightchild = -1) = 1 + 0 = 1
      /
    10 here height = 0
  

    method to use LL rotation
    bring the leftchild to root - 20 to root position
    move the root to the right child - 30 to the rightchild position
    leftchild of 20 remains the same

    steps:
    The left child becomes the new root of the subtree.
    The original root becomes the right child of the new root.
    The new root’s right subtree becomes the left subtree of the old root.
    Heights are updated.

        20
        / \
     10    30

next example
     30 0-2 = -2
      \
      40 0-1 = -1
      \ 
       50 0-0 = 0

    PERFORM rr rotations

       40
       /\
      30 50

next example:
      30 2-0=2 L
    /
  20 0-1= -1  R
    \
      25 0 -0 = 0 
LR rotation:
20 -> rightchild = 25 -> leftchild
25 -> leftchild = 30 -> leftchild
30 -> leftchild = 25 -> rightchild
25->rigthchild = 30

result:

      25
    /   \ 
  20      30
/   \     /
   25lc  25rc



*/
/*key flow diagram for deletion
            ┌──────────────────────────────────────┐
            │ delete_from_binary_tree(node, key)    │
            └──────────────────────────────────────┘
                          │
                          ▼
              Is node NULL? ────► YES ──► return NULL
                          │
                         NO
                          │
                          ▼
            ┌─────────────────────────────────────┐
            │ 1. Search for key (BST property)     │
            └─────────────────────────────────────┘
                          │
       ┌───────────────────────────────────────┐
       │ IF key < node->val                     │
       │     node->leftchild = delete(left, key)│
       └───────────────────────────────────────┘
                          │
       ┌───────────────────────────────────────┐
       │ ELSE IF key > node->val                │
       │     node->rightchild = delete(right,key)│
       └───────────────────────────────────────┘
                          │
                          ▼
   ┌────────────────────────────────────────────┐
   │ ELSE  (node->val == key)                    │
   │   CASE 1: No child                          │
   │       delete node, return NULL              │
   │   CASE 2: One child                         │
   │       Replace node with child, delete old   │
   │   CASE 3: Two children                      │
   │       Choose predecessor/successor based    │
   │       on subtree height                     │
   │       Replace node->val with pred/succ val  │
   │       Recursively delete pred/succ from     │
   │       corresponding subtree                 │
   └────────────────────────────────────────────┘
                          │
                          ▼
            ┌─────────────────────────────────────┐
            │ 2. Update node height                │
            └─────────────────────────────────────┘
                          │
                          ▼
            ┌─────────────────────────────────────┐
            │ 3. Calculate balance factor          │
            └─────────────────────────────────────┘
                          │
                          ▼
  ┌────────────────────────────────────────────────────────┐
  │ 4. Perform rotations if unbalanced                     │
  │   IF balance > 1 and left child's balance >= 0 → LL     │
  │   IF balance > 1 and left child's balance < 0  → LR     │
  │   IF balance < -1 and right child's balance <= 0 → RR   │
  │   IF balance < -1 and right child's balance > 0  → RL   │
  └────────────────────────────────────────────────────────┘
                          │
                          ▼
                  return node
*/