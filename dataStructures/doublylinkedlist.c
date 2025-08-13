#include <stdio.h>
#include <stdlib.h>


typedef struct dl{
  struct dl* next;
  struct dl* prev;
  int val;
  //can use function pointer but not the function itself here inside the structure
} dll;

dll* head = NULL;
dll* tail = NULL;

dll* createdllnode(int val){
  dll *newnode = (dll*) malloc(sizeof(dll));
  newnode -> next = NULL;
  newnode -> prev = NULL;
  newnode -> val = val;
  return newnode;
}

int findlength(){
  dll* traverse = head;
  int length = 0;

  while(traverse){
    traverse = traverse -> next;
    ++length;
  }

  return length;
}

void Insert_into_dll_beginning(int val){
  dll *newnode = createdllnode(val);
  
  newnode -> next = head;
  
  if(head == NULL){
    head = newnode;
    tail = newnode;
    return;
  } 
  head -> prev = newnode;
  head = newnode;
}

void Insert_into_dll_end(int val){
  dll *newnode = createdllnode(val);
  if(tail == NULL){
    head = newnode;
    tail = newnode;
    return;
  }
  tail -> next = newnode;
  newnode -> prev = tail;
  tail = newnode;
}

void Insert_into_dll_at_specific_pos(int val, int pos){
  dll *newnode = createdllnode(val);
  int length = findlength();
  dll *traverse = head;
  int current = 0;

  if(pos >= length){
    printf("Sorry provided input exceeding the dll size\n");
    return;
  }
  while(current < pos && traverse != NULL){
    ++current;
    traverse = traverse -> next;
  }

  dll *previousnode = traverse -> prev;
  if(previousnode == NULL){
    Insert_into_dll_beginning(val);
    return;
  }

  newnode -> next = traverse;
  newnode -> prev = previousnode;
  traverse -> prev = newnode;
  previousnode -> next = newnode;
}

void displayvaluesfront(){
  dll* traverse = head;
  printf("Values from the front : ");
  while(traverse != NULL){
    printf("%d->", traverse -> val);
    traverse = traverse -> next;
  }
  printf("NULL\n");
}

void displayvaluesback(){
  dll* traverse = tail;
  printf("Values from the back : ");
  while(traverse != NULL){
    printf("%d->", traverse -> val);
    traverse = traverse -> prev;
  }
  printf("NULL\n");
}

void find_the_node(int searchthiselement){
  dll * traverse = head;
  int returnpos = 0;
  while(traverse){
    if(searchthiselement == traverse -> val){
      printf("The searching element found at position : %d\n", returnpos);
      return;
    } 
    traverse = traverse -> next;
    ++returnpos;
  }
  printf("The searching element was not found");
  return ;
}

void freeallnodes(){
  dll* traverse = head;
  while(traverse!= NULL){
    dll* freethisnode = traverse;
    traverse = traverse->next;
    free(freethisnode);
  }
  return;
}

int main(){
  int pos = 0;

  scanf("%d", &pos);
  Insert_into_dll_beginning(10); 
  Insert_into_dll_end(1);
  Insert_into_dll_at_specific_pos(5, 1);

  displayvaluesback();
  displayvaluesfront();

  find_the_node(10);

  deletefrombeginning();
  deletefromend();
  deletefromposition();
  freeallnodes();
  
  return 0;
}