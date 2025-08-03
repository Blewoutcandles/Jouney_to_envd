#include <bits/stdc++.h>
/*                                Maximum Depth of Binary Tree                                        */
using std :: cout;
using std :: cin;
using std :: endl;
using std :: vector;
using std :: queue;
using std :: max;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int maxDepth(TreeNode* root) {
  if(root == NULL){
    return 0;
  }
  if(root -> left == nullptr && root -> right == nullptr) return 1;
  
  return max(maxDepth(root -> left), maxDepth(root -> right)) + 1;
}

int maxheight(TreeNode* root){
  if(root == NULL) return 0;

  int height = 0;
  queue<TreeNode*> q;

  q.push(root);

  while(!q.empty()){
    
    int currentlevel_no_of_nodes = q.size();

    //for each level push the nodes into queue once complemented increment the height variable
 
    for(int i = 0; i<currentlevel_no_of_nodes; i++){
      TreeNode* frontnode = q.front();
      q.pop();
      if(frontnode -> left){
        q.push(frontnode->left);
      }

      if(frontnode -> right){
        q.push(frontnode -> right);
      }
    }
    ++height;
  }

  return height;
}

int main(){
  TreeNode newnode(3);
  TreeNode leftone(9);
  TreeNode rightone(20);
  TreeNode rightchild1(15);
  TreeNode rightchild2(7);
  newnode . left = &leftone;
  newnode . right = &rightone;
  rightone. left = &rightchild1;
  rightone. right = &rightchild2;
  cout << "using dfs, the height is : " << maxDepth(&newnode) << endl;

  cout << "using bfs, the height is : " << maxheight(&newnode) << endl;

  return 0;
}