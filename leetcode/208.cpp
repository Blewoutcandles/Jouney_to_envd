/******************************************* Implement Trie (Prefix Tree)  *********************** */

#include <bits/stdc++.h>

using std :: cout;
using std :: cin;
using std :: endl;
using std :: vector;
using std :: queue;
using std :: string;
using std :: max;

class Trie {
public:
  bool endofword;
  Trie* children[26];

  Trie() {
    endofword = false;
    for(int i = 0; i<26; i++){ //26 children pointers assign to nullptr
      children[i] = nullptr;
    }
  }
  
  void insert(string word) {
    Trie * currentroot = this;
    for(int i : word){
      int j = i-97;
      if(!currentroot -> children[j]){ //if the children node is nullptr allocate memory and assign the character in that
        Trie* newnode = new Trie(); 
        currentroot -> children[j] = newnode; //assign the character here for eg., 'a'
      }
      currentroot = currentroot -> children[j];
    }
    currentroot -> endofword = true; //mark the end of the word
  }
  
  bool search(string word) {
    Trie *current = this;
    for(auto i : word){
      int j = i - 97;
      if(current -> children[j] == nullptr){
        return false;
      }
      current = current -> children[j];
    }
    if(current ->endofword){
      return true;
    }
    return false;
  }
  
  bool startsWith(string prefix) {
    Trie  *current = this;
    for(char i : prefix){
      int j = i - 97;
      if(current -> children[j] == nullptr) return false;
      current = current -> children[j];
    }
    
    return true;
  }

};

int main(){
  Trie *root = new Trie(); //do not add parenthesis here will marked as function declaration
  vector<string> addstrings{"and", "art", "are", "ant"};

  for(auto i : addstrings){
    root->insert(i);
  }

  if(root->search("and")){
    cout << "Yes the word is present in the trie structure" << endl;
  }

  if(root->startsWith("ar")){ //check for if there is any word that starts with ar
    cout << "Yes there are words that start with the one provided" << endl;
  }
  
  return 0;
}
/*planning to implement the trie using  as:
create an 26 pointers to accomodate the letter at each level as a tree
create an empty root
add the children from it for example
"ant", "and", "are", "art"
            root
            /
            a
          /   \
        n       r
      /   \    /  \
    t      d  e     t


    simillar questions and articles
Trie Delete
Trie data structure
Displaying content of Trie
Advantages of Trie Data Structure
Auto-complete feature using Trie
Pattern Searching using a Trie of all Suffixes
Practice Problems: 

Minimum Word Break
Unique rows in a binary matrix
Count of distinct substrings
Word Boggle
Sorting array of strings (or words) using Trie
*/