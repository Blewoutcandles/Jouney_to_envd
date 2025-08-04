/******************************** Implement Stack using Queues ********************************* */
//using two queues 
//fill in the below functions
#include <bits/stdc++.h>

using std :: cout;
using std :: cin;
using std :: endl;
using std :: vector;
using std :: queue;
using std :: max;

class MyStack {
public:
  queue<int> primary;
  queue<int> secondary;
    MyStack() {
      
    }
    
    void push(int x) {
      primary.push(x);
    }
    
    int pop() {
      int popped_element = -1;
      if(!primary.empty()){
        while(primary.size() != 1){
          secondary.push(primary.front());
          primary.pop();
        }
        
        popped_element = primary.front();
        primary.pop();

        queue<int> temp(primary);
        primary = secondary;
        secondary = temp;

      }
      return popped_element;
  
    }
    
    int top() {
        return primary.back();
    }
    
    bool empty() {
      return primary.empty();
    }
};

int main(){
  MyStack *object = new MyStack(); //create the object 
  object -> push(10);
  object -> push(5);
  object -> push(1);
  cout << object -> top() << endl;
  cout << object -> empty() << endl;
  object -> pop();


  delete object; //free the allocated object
  return 0;
}