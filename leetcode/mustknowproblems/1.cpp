/*************************Two Sum************************** */
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

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> result;
    sort(nums.begin(), nums.end());
    int left = 0, right = nums.size()-1;

    while(left < right){
        if(nums[left] + nums[right] == target){
            result.push_back(left);
            result.push_back(right);
            left++;
            right--;
        }else if(nums[left] < nums[right]){
            right--;
        }else{
            left++;
        }
    }

    return result;
}

int main(){
    vector<int> nums{2,7,11,15};
    int target = 9;
    vector<int> output = twoSum(nums, target);
    for(int i : output){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}