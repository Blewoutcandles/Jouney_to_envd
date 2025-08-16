
/********************************Rotate Array*********************************
Array
Math
Two Pointers
 */

#include <bits/stdc++.h>

using std :: cout;
using std :: cin;
using std :: endl;
using std :: vector;
using std :: queue;
using std :: max;
using std :: map;
using std :: set;

void swap_elements(int* a, int* b){//there are many ways to swap the elements
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
    /*consider this example
    swap 1 and 3
    using bit wise operation
    1 = 001 = a
    3 = 011 = b
    a^b = 010 = 2
    a = 2

    a = 010
    b = 011
    a^b=001
    b = 1

    a = 010
    b = 001
    a^b=011
    a = 3
    now a vaue = 3, b value = 1

    */
}


void rotate_the_array_by_k_times(int* array, int k, int arraysize, int method){
    switch(method){
        case 0:{

            /*method2: use temporary array : time complexity : o(n), with additional space of size of the array*/
            int temp[arraysize], o = 0; //this temporary array is created in stack
            for(int i = k; i<arraysize; i++){//first copy the elements from index k to end of the array
                temp[o++] = array[i]; //adding the elements
            } 
            //now copy the elements from the index 0 to k-1 to the temporary array
            for(int i = 0; i<k; i++){
                temp[o++] = array[i];
            }
            //now copy the elements from the temporary array to original array since we need the original one not the 
            //one that is created on the stack
            for(int i = 0; i<arraysize; i++){
                array[i] = temp[i];
            }
        }
        break;

        case 1:
        default:{
            //method 1: without using the extra space
            //reverse the entire array
            //use two pointers 
            int left = 0, right = arraysize-1; //left = index 0, right = last element index in the array
            while(left < right){
                swap_elements(&array[left], &array[right]);
                left++;
                right--;
            }

            //now reverse the first k-1 elements
            left = 0, right = k-2;
            while(left < right){
                swap_elements(&array[left], &array[right]);
                left++;
                right--;
            }

            left = k-1, right = arraysize-1;
            while(left < right){
                swap_elements(&array[left], &array[right]);
                left++;
                right--;
            }
        }
        break;
    }

}


int main(){
    int array[5] = {1,2,3,4,5};
    int k = 3;
    int tellme = 0;
    printf("Tell me which method you want method 1 or 2 specify the number: ");
    scanf("%d", &tellme);
    rotate_the_array_by_k_times(array, k, sizeof(array)/sizeof(int), tellme-1);

    //print the array
    for(int i = 0; i < sizeof(array)/sizeof(int); i++){
        printf("%d ", array[i]);
    }
    return 0;
}
/*logic to rotate the array - in place algorithm
first reverse the whole array
array = {1,2,3,4,5}
after reversing
array = {5,4,3,2,1};

sice k = 3, reverse the first k elements
so the array becomes
array = {3,4,5,2,1}

then reverse the n-k elements in the array where
n = number of elements in the array
k = no of times to rotate the array
n-k = 5 - 3 = 2

reverse the n-k which is 2 from the end of the array {2,1} (this is the last tow elements)

array = {3,4,5,1,2}


Method2 : use additional space to store the elements 
use temporary array
array2 = {};

copy the elements from index k to end of the array to the temporary array
k =3
array = {1,2,3,4,5}
        0,1,2,3,4
        copy from 3 to 4 to the temporary array
array2 = {4,5};

now copy the first k elements to the temporary array
copying the elements from index 0 to k-1 to the temporary array
array2 = {4,5,1,2,3};

now return the array
*/