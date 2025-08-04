/******************************************* Implement Trie (Prefix Tree)  *********************** */

#include <bits/stdc++.h>

using std :: cout;
using std :: cin;
using std :: endl;
using std :: vector;
using std :: queue;
using std :: string;
using std :: max;
#define ALPHABET_SIZE 26
class Trie {
public:
  bool endofword;
  Trie* children[ALPHABET_SIZE];

  Trie() {
    endofword = false;
    for(int i = 0; i<ALPHABET_SIZE; i++){ //ALPHABET_SIZE children pointers assign to nullptr
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

  bool isempty(){
    Trie *root = this;
    for(int i = 0; i<ALPHABET_SIZE; i++){
      if(root -> children[i] != nullptr){
        return false;
      }
    }
    return true;
  }

  //delete a word from the structure 
  Trie* deleteWord(Trie* currentnode, string word, int index){
    //base condition reaching end of the word
    if(index == word.size()){
      if(currentnode -> endofword){
        currentnode -> endofword = false; //mark the endof word as false (clearing the word from trie)
        //check for any children if no delete the currentnode otherwise return the currentnode

        for(int i = 0; i<ALPHABET_SIZE; i++){
          if(currentnode -> children[i] != nullptr){
            return currentnode;
          }
        }
        
        delete(currentnode); //currentnode has no children so delete the node
        currentnode = nullptr;
        return currentnode;
      }
    }

    
    int j = word[index] - 'a';

    if(currentnode -> children[j] != nullptr){
      //starting from the root so when backtracing root->children[someindex] = same node from the successive call (same nodehere
      //means which is recursively passed to the next call)
      currentnode -> children[j] = deleteWord(currentnode -> children[j], word, index+1);
    }

    for(int i = 0; i<ALPHABET_SIZE; i++){
      if(currentnode -> children[i] != nullptr){
        return currentnode;
      }
    }
    delete currentnode;
    currentnode = nullptr;
    return currentnode;

  }

  void removeword(string word){
    Trie *currentnode = this;
    deleteWord(currentnode, word, 0);
  }

  void print_all_words_trie(Trie* currentnode, string bufferword){
    
    for(int i = 0; i<ALPHABET_SIZE; i++){
      if(currentnode -> children[i] != nullptr){
        bufferword.append(1, char('a' + i)); //parameters numberof times, character
        print_all_words_trie(currentnode -> children[i], bufferword);
        bufferword.pop_back();
      }      
    }
    if(currentnode -> endofword){
      cout << bufferword << endl;
    }  
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

  if(root -> isempty()){
    cout << "Trie structure is empty" << endl;
  }else{
    cout << "Trie structure contains elements" << endl;
  }

  root -> removeword("and");
  root -> print_all_words_trie(root, "");
  
  return 0;
}
/*planning to implement the trie using  as:
create an ALPHABET_SIZE pointers to accomodate the letter at each level as a tree
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

Cases on deleting from the structure
"and" if this is the case then we cannot remove a since it has other children like 'r'.
then proceed to the next letter (descendant from the parent 'a') 'n'
since we cannot remove the letter n as it has two children 't' and 'd'
then proceed to next letter 'd' which has no children we can remove this completely also set as endofword as false

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