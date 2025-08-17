
/*************************Trapping Rain Water************************** */
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

int trap(vector<int>& height) {
    int amountofwatertrapped = 0;
    int size = height.size(); 
    vector<int> leftmax(size, 0);
    vector<int> rightmax(size, 0);

    leftmax[0] = height[0];
    for(int i = 1; i<size; i++){
        leftmax[i] = max(leftmax[i-1], height[i]);
    }
    
    rightmax[size-1] = height[size-1];
    for(int i = size-2; i>=0; i--){
        rightmax[i] = max(rightmax[i+1], height[i]);
    }

    for(int i = 0; i<size; i++){
        amountofwatertrapped += min(leftmax[i], rightmax[i]) - height[i];
    }

    return amountofwatertrapped;

}

int main(){
    vector<int> blocks{0,1,0,2,1,0,1,3,2,1,2,1};
    /*pictorial representation
    
          |
     |----||-|
--|--||--||||||
- -> is the water trapped inside
we need to find out how much water can be stored with the gap between the blocks

Method 1 of solving this is using the 2 arrays to store the maximum height so far encountered at each index from both 
left and right side
0,1,0,2,1,0,1,3,2,1,2,1
Have a left array and right array
        0   1   2   3   4   5   6   7   8   9   10  11 -> indices
store the maximum height so far you have seen
left :  0   1   1   2   2   2   2   3   3   3   3   3   -> height maximum encountered sofar at each index
right:  3   3   3   3   3   3   3   3   2   2   2   1
minhght:0   1   1   2   2   2   2   3   2   2   2   1
hieight:0   1   0   2   1   0   1   3   2   1   2   1
minh-ht:0   0   1   0   1   2   1   0   0   1   0   0

when calcualting the height we should get the mininum of left and right 
and minus the height each index to get the amount of water trapped 
look at the numbers of minheight - height at each index along with picture to show the water(ignore left most water trapped 
since lacking blocks to hold it)
trapped at each index

*/

    cout << "The amount of water that can be trapped is : " << trap(blocks) << endl;
    return 0;
}

