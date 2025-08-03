#include <bits/stdc++.h>
/*                                Binary Tree Level Order Traversal                                        */
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

vector<int> levelOrderTraversal(TreeNode* root){
  queue<TreeNode*> q;
  vector<int> levelorder;
  q.push(root);

  while(q.empty() == false){
    TreeNode *frontnode = q.front();

    levelorder.push_back(frontnode -> val);

    q.pop();
    
    if(frontnode -> left){
      q.push(frontnode -> left);
    }

    if(frontnode -> right){
      q.push(frontnode -> right);
    }
  }
  return levelorder;
}

int height(TreeNode* root){
  if(root == nullptr){
    return 0;
  }
  if(root -> left == NULL && root -> right == NULL){
    return 1;
  }

  return max(height(root -> left), height(root -> right)) + 1;
}
void eachlevel_levelorder(TreeNode* node, vector<vector<int>>& result, int index, int heightvalue){
  if(node == nullptr || index == heightvalue){
    return;
  }

  result[index].push_back(node->val);

  eachlevel_levelorder(node->left, result, index+1, heightvalue);
  eachlevel_levelorder(node -> right, result, index+1, heightvalue);

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

  vector<int> result = levelOrderTraversal(&newnode);

  cout << "The level order is : ";

  for(auto i :result){
    cout  << i << " ";
  }

  cout << endl;

  int find_the_max_height_of_tree = height(&newnode);

  vector<vector<int>> result1(find_the_max_height_of_tree);
  
  eachlevel_levelorder(&newnode, result1, 0, find_the_max_height_of_tree);

  for(auto i : result1){
    for(auto n : i){
      cout << n << " ";
    }
    cout << endl;
  }

  return 0;
}

/*class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        queue<TreeNode*>q;
        if(!root)return ans;
        q.push(root);
        while(!q.empty())
        {
            int levelsize=q.size();
            vector<int>level;
            for(int i=0;i<levelsize;i++)
            {
                TreeNode* curr=q.front();
                  q.pop();

                level.push_back(curr->val);
              
            if(curr->left )q.push(curr->left);
            if(curr->right)q.push(curr->right);
            }
            ans.push_back(level);
        }
        return ans;
        
    }*/