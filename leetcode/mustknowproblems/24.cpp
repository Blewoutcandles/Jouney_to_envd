/*************************Swap Nodes in Pair************************** */
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

struct LinkedList{
    int val;
    struct LinkedList* next;
    LinkedList(int data):val(data), next(nullptr){}
    LinkedList(int val, LinkedList* pointer):val(val), next(pointer){}
    void print_the_elements(LinkedList* root){//this is possible only in c++ not c in c only function pointers are allowed
        while(root){
            cout << root -> val << "->";
            root = root -> next;
        }
        cout << "nullptr" << endl;
    }
};

/*solution*/
LinkedList* swapPairs(LinkedList* head) {
    if(head == nullptr || head -> next == nullptr) return nullptr;

    LinkedList samplenode(0, head);
    LinkedList *current = head, *nextnode, *prevnode = &samplenode;

    while(current != nullptr && current-> next != nullptr){
        nextnode = current -> next;
        current -> next = nextnode -> next;
        nextnode -> next = current;
        prevnode -> next = nextnode;
        prevnode =  current;
        current = current->next;
    }

    return samplenode.next;
    
}


int main(){ 
    LinkedList head(1);
    LinkedList node1(2);
    head.next = &node1;
    LinkedList node2(3);
    LinkedList node3(4);
    node1.next = &node2;
    node2.next = &node3;
    node3.next = nullptr;
    head.print_the_elements(&head);

    LinkedList* newhead = swapPairs(&head);
    head.print_the_elements(newhead);
    /*try the test input as 1 -> 2 -> 3 -> nullptr*/


    return 0;
    
}
/*similar problem refer : Reverse Nodes in k-Group problem no: 25*/