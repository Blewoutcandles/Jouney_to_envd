#include<stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_SIZE 100
typedef struct {
  //implement the queue data structures here
  int front;
  int rear;
  int size;
  int arr[]; 
} MyStack;


MyStack* myStackCreate() {
  MyStack* newstack = (MyStack*) malloc(sizeof(MyStack) + sizeof(int) * STACK_SIZE); //using flexible array requires memory allocation to be in done during the memory allocation of stack itself
  newstack -> front = -1;
  newstack -> rear = -1;
  newstack -> size = 0; 
  return newstack;
}

void myStackPush(MyStack* obj, int x) {
  if(obj -> front == -1) ++obj->front; 
  if(obj -> rear == obj -> front == obj -> rear) return;
  if(obj -> rear+1 < STACK_SIZE){ //check condition for stack overflow
    obj->arr[++obj -> rear] = x;
    if(obj -> front == -1){
      ++obj -> front;
    }
    ++obj->size;
  }
}
bool myStackEmpty(MyStack* obj) {
  if(obj -> rear == -1 && obj -> size == 0){
    return true;
  }
  return false;
}

int myStackPop(MyStack* obj) {
  if(myStackEmpty(obj)){
    return -1;
  }
  int popelement = obj -> arr[obj -> rear--];//decremeent the rear pointer
  obj->size--;
  return popelement;
}

int myStackTop(MyStack* obj) {
  int topelement = obj -> arr[obj -> rear];
  return topelement;
}



void myStackFree(MyStack* obj) {
  free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/
int main(){
  MyStack *stack = myStackCreate();
  myStackPush(stack, 10);
  myStackPush(stack, 20);
  myStackPush(stack, 30);
  myStackPush(stack, 40);

  printf("Popped element is : %d\n", myStackPop(stack));

  printf("TOp element is : %d\n", myStackTop(stack));


  return 0;
}