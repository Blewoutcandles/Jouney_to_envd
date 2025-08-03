#include <bits/stdc++.h>

using std :: cout;
using std :: cin;
using std :: endl;
using std :: vector;
using std :: swap;
using std :: sort;

/*structure for the 2-3 trees used for searching technique*/
struct tree_2_3{

  bool isleaf = false;
  int numkeys;
  int keys[2];                      //store one or two keys
  tree_2_3* children[3];            //have two or three children (two children node- 2 node and three children node - 3 node)

  tree_2_3(bool leaf){
    isleaf = leaf;
    numkeys = 0;
    keys[0] = keys[1] = 0;
    children[0] = children[1] = children[2] = nullptr;
  }
}; 

/*🔍 Explanation:
keys[2]: Holds up to 2 keys.
children[3]: Holds up to 3 children.
isLeaf: Tells whether this is a leaf node.
numKeys: 1 or 2 depending on number of keys.*/



/*When a split happens, we need to pass the middle key up and return the two new child nodes.*/
struct InsertionResult{
  bool didsplit;
  int middlekey;
  tree_2_3* left;
  tree_2_3* right;

  InsertionResult(): didsplit(false), middlekey(0), left(nullptr), right(nullptr){}
};

/*🔍 Explanation:
didSplit: Whether a split occurred.

middleKey: Key to be pushed up to the parent.

leftChild and rightChild: Resulting nodes from the split.*/


void InsertIntoNode(tree_2_3* node, int key){
  node -> keys[node -> numkeys++] = key;

  if(node -> numkeys == 2 && node -> keys[0] > node -> keys[1]){
    swap(node -> keys[0], node -> keys[1]);
  }
}

InsertionResult insertionrecursive(tree_2_3* node, int insertion_value){
  //base case if the node is the leaf node then do the insertion right away use function InsertIntoNode() above
  if(node -> isleaf){
    if(node -> numkeys < 2){
      InsertIntoNode(node, insertion_value);
      return InsertionResult(); //no split
    }

    int all[3] = {node->keys[0], node->keys[1], insertion_value};

    sort(all, all+3);
    //now we have three nodes so create two separate nodes to accomodate the splitting node value for eg.., 10,30 now insert value 20
    // 10,30,20 sort the values 10, 20, 30 we are going to push one node up; creating two nodes in the bottom and they are leaf nodes

    tree_2_3 *leftchild = new tree_2_3(true);
    tree_2_3 *rightchild = new tree_2_3(true);

    //assign the key values to them since there are two slots in the node push the values in the zeroth index, Left holds smallest, Right holds largest
    leftchild->keys[0] = all[0];
    rightchild->keys[0] = all[2]; //middle one is being sent up ward

    leftchild->numkeys = rightchild->numkeys = 1; //update the number of keys each node holds

    InsertionResult res;
    //update the InsertionResult structure for the splitting information
    res.didsplit = true;
    res.middlekey = all[1];
    res.left = leftchild;
    res.right = rightchild;

    // delete node; //delete only if it is dynamically allocated

    return res;
  }
  //end of the base case

  //if the node we are encountering right now is not the left node say it is a internal node then we should find which direction to navigate 
  //whether to rightchild or the left child
  InsertionResult childResult; //populating the splitting information to find whether splitting needed or not 
  int pos; //to find the position 

  if(insertion_value < node->keys[0]){
    pos = 0;  //proceeding to navigate to left child area
  }else if(node->numkeys == 2 && insertion_value < node->keys[1]){
    pos = 1;  //proceeding to navigate to middle child area
  }else{
    pos = 2; //proceeding to navigate to right child area
  }

  //after finding the position recursively call the childs from the current node with the position we just acquired
  childResult = insertionrecursive(node->children[pos], insertion_value);

  //check for splitting with the above acquired result
  if(childResult.didsplit == false){
    return InsertionResult(); // no changes needed
  }

  if(node->numkeys == 1){//so split happened and the parent has only one key
/*      [20]
        /    \
      [10]   [25, 30]

      now inserting 35 would break the 25 and 30, pushes the 30 upward and placing 35 as the right child (25 becomes the middle child)
       [20, 30]
      /   |    \
  [10] [25]  [35]
  this below block represents this case*/
    
    if(pos == 0){
      /*if the pos in which we sent the element to insert is lesser than the only one key 
      and now the upward element which came from the bottom should be lesser than the present node key (remember numkeys = 1 right now)*/
      //then move the element to the right side
      node -> keys[1] = node -> keys[0];
      node -> keys[0] = childResult.middlekey;  //we successfully placed the key in the node (numkeys = 2 update it)
      node -> children[2] = node -> children[1];//update children[2] to be children[1] 
      node -> children[0] = childResult.left;
      node -> children[1] = childResult.right;
      /*before splitting 
      keys:      [K]
      children: [ C0 ] [ C1 ]
      aftersplitting organizing

      keys:      [M, K]
      children: [ LC ] [ RC ] [ C1 ]
  */
    }else{
      /*this case means the position is either to be on 1 or 2*/
      node -> keys[1] = childResult.middlekey; //simply update the second key to middle element
      node -> children[1] = childResult.left;
      node -> children[2] = childResult.right; 
    }
    //after update the current node contains 2 keys update key count
    node -> numkeys = 2; //can also do node -> numkeys++;
    return InsertionResult(); // no splitting happens in this level so return the object
  }

  //HARD case : Current node already has 2 keys what to do perform the same operation as we do in leaf node
  //add this to the key list and push the middle element upward 

  //add the three keys 
  int all[3] = {node -> keys[0], node->keys[1], childResult.middlekey};
  
  sort(all, all+3);
  /*
  keys: [K1, K2]
children: [C0] [C1] [C2]
Now you insert into C0, and it splits:

Split C0 → [LC0], [RC0]

Promote middle key = M0

You now have 3 keys: [M0, K1, K2] → need to split

And 4 children:

[LC0] [RC0] [C1] [C2]*/
  tree_2_3* tempNodes[4];
  if(pos == 0){
    //store all the chldren here 
    //if the pos == 0 then we have to retain the children at indes 1 and 2
    tempNodes[0] = childResult.left;
    tempNodes[1] = childResult.right;
    tempNodes[2] = node -> children[1];
    tempNodes[3] = node -> children[2];
  }
  else if(pos == 1){
    //if the pos is 1 then we have to retain the children at index 0 and 2
    tempNodes[0] = node -> children[0];
    tempNodes[1] = childResult.left;
    tempNodes[2] = childResult.right;
    tempNodes[3] = node -> children[2];
  }else{
    //if the position is 2 then we have to retain the children at index 0 and 1.
    tempNodes[0] = node -> children[0];
    tempNodes[1] = node -> children[1];
    tempNodes[2] = childResult.left;
    tempNodes[3] = childResult.right;
  }
  //now create two separate nodes to accomodate the split at the current level
  tree_2_3 * newleftnode = new tree_2_3(false);//false indicating this is not the leaf node
  tree_2_3 * newrightnode = new tree_2_3(false);

  //assign the smaller and larger element of all 
  newleftnode -> keys[0] = all[0];
  newrightnode -> keys[0] = all[2];
  newleftnode->numkeys = 1;
  newrightnode -> numkeys = 1;

  //Distribute the children stored in tempNodes
  /*[LC0] [RC0] [C1] [C2] are the children
  the parent gets 
  leftnode          rightnode
   /  \             /    \
   lc0  rc0         c1    c2
   if the pos = 0 where the split happens
  */

  for(int i = 0; i<2; i++){
    newleftnode -> children[i] = tempNodes[i];
    newrightnode -> children[i] = tempNodes[i+2];
  }

  //indicate that the split occured
  InsertionResult res;
  res.didsplit = true;
  res.middlekey = all[1];
  res.left = newleftnode;
  res.right = newrightnode;

  // delete node; //only if it is dynamically allocated and also deletion no need in place of one key in the node
  return res;

}
int main(){

  return 0;
}