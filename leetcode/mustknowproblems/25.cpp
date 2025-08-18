/*************************Reverse Nodes in k-Group************************** */
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

LinkedList* reverse_linkedlist(LinkedList* start){
    LinkedList*prev = nullptr, *next = nullptr;
    while(start != nullptr){
        next = start -> next;
        start -> next = prev;
        prev = start;
        start = next;
    }
    return prev;//or return tail
}
/*solution*/
LinkedList* reverseKGroup(LinkedList* head, int k) {
    if(!head || k == 1){
        return head;
    }
    /*swap the nodes but in group wise*/
    /*method of solving : traverse to find the head and tail of the list such that length is k and perform reversing operations*/
    LinkedList samplenode(0);
    samplenode.next = head;
    LinkedList*previousnode = &samplenode, *end = &samplenode;

    while(true){//keep the loop running until the node becomes nullptr

        for(int i = 0; i<k; i++){//removed k-1 since starting from dummynode
            end = end -> next;
            if(!end){
                return samplenode.next;
            }
        } 

        //nodes to remember- the node that is next to the end node and the node with which we are starting
        LinkedList* start = previousnode -> next;//store the starting node
        LinkedList* nextnode = end -> next; //store the node after k nodes

        //The nodes we have in hand are from start to end and null terminate the end node
        end -> next = nullptr;
        //now the nodes from start to end becomes a separate linked list, which can easily be reversed

        previousnode -> next = reverse_linkedlist(start);

        //reconnect the nodes from start th node to the nextnode
        start -> next = nextnode;
        previousnode = start;
        end = previousnode;
    }

    return samplenode.next;
}

int main(){ 
    LinkedList head(1);
    LinkedList node1(2);
    head.next = &node1;
    LinkedList node2(3);
    LinkedList node3(4);
    LinkedList node4(5);
    LinkedList node5(6);
    LinkedList node6(7);
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = nullptr;
    head.print_the_elements(&head);

    LinkedList* newhead = reverseKGroup(&head, 3);
    head.print_the_elements(newhead);
    /*try the test input as 1 -> 2 -> 3 -> nullptr*/


    return 0;
    
}