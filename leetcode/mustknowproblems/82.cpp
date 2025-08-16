/*************************Remove Duplicates from Sorted List II************************** */
#include<bits/stdc++.h>

using std :: max;
using std :: cin;
using std :: cout;
using std :: endl;
using std :: min;
using std :: vector;
using std :: set;
using std :: map;
using std :: sort;
using std :: stack;

struct ListNode{
    int val;
    struct ListNode* next;
    ListNode(int val= 0): val(val), next(nullptr) {}
    ListNode(int val, struct ListNode* pointer): val(val), next(pointer){}
};

void print_the_ListNode( ListNode *root){
    ListNode* temp = root;
    while(temp != nullptr){
        cout << temp -> val << "-";
        temp  = temp -> next;
    }
    cout << "nullptr" <<endl;
}

ListNode* deleteDuplicates(ListNode* head) {
    if(head == nullptr || head -> next == nullptr) return head;

    ListNode temp(0, head);
    ListNode*fakehead = &temp;
    bool duplicateflag = false;
    //creation of dummy node to handle varying head

    ListNode* currentnode = &temp , *nextnode = head;
    while(nextnode != nullptr){
        while(nextnode -> next != nullptr &&  nextnode -> val == nextnode -> next ->val){
            //compare the currentelemeent with the immediate next element
            //nextnode null check is performed in the while condition, then no need to include the \
            //same case while comparing
            //if both current and immediate element are same then continue moving forward

            nextnode = nextnode -> next;
            duplicateflag = true;//set the duplicate flag
        }
        
        if(nextnode == nullptr || duplicateflag == true){//if the duplicate flag is set then skip to the next node since we are 
            //required not to include any element that are duplicate in the linked list
            duplicateflag = false;//reset the duplicate flag and continue with the next node
            nextnode = nextnode -> next;
            continue;
        }
        //if no duplicate is found for the current node then add the nodes to our current node -> next (which is after dummy node)
        currentnode -> next = nextnode;
        currentnode = nextnode;//make sure to move the currentnode to the latest node
        nextnode = nextnode -> next;//proceed to the nextnode
    }
    currentnode -> next = nullptr;//once done mark the currentnode -> next = nullptr to make sure the new linked list has its end 
    //null terminated

    return fakehead -> next;//return after the dummy node which dummynode -> next
}

int main(){
    ListNode rootnode(1);
    ListNode newnode(2, nullptr);
    ListNode new2node(2, nullptr);
    ListNode new3node(3,nullptr);
    ListNode new4node(4,nullptr);
    ListNode new5node(4,nullptr);
    ListNode new6node(5, nullptr);
    rootnode.next = &newnode;
    newnode.next = &new2node;
    new2node.next = &new3node;
    new3node.next = &new4node;
    new4node.next = &new5node;
    new5node.next = &new6node;
    new6node.next = nullptr;

    print_the_ListNode(&rootnode);
    
    print_the_ListNode(deleteDuplicates(&rootnode));

    return 0;
}