/******************************** Count Number of Maximum Bitwise-OR Subsets ********************************* */
/*Array
Backtracking
Bit Manipulation
Enumeration
Weekly Contest 263*/

#include <bits/stdc++.h>

using std :: cout;
using std :: cin;
using std :: endl;
using std :: vector;
using std :: queue;
using std :: max;


void dfs_backtracking(vector<int>&nums, int index, vector<vector<int>>&dp, vector<int>&sub_dp, int maxORsum, int sofarmaxsum){
    
    if(sofarmaxsum == maxORsum){
        dp.push_back(sub_dp);
    }
    
    if(index == nums.size()){
        
        return;
    }

    for(int i = index; i<nums.size(); i++){
        sub_dp.push_back(nums[i]);
        dfs_backtracking(nums, i+1, dp, sub_dp, maxORsum, sofarmaxsum|nums[i]);
        sub_dp.pop_back();
    }
}
int countMaxOrSubsets(vector<int>& nums) {
    vector<vector<int>> dp;
    vector<int> sub_dp;
    int maxORsum = 0;
    for(auto i : nums){
        maxORsum |= i;
    }
    dfs_backtracking(nums, 0, dp, sub_dp, maxORsum, 0);
    return dp.size();
}


int main(){
    vector<int> nums{2,2,2};
    cout << "Total subsets are ;  " << countMaxOrSubsets(nums) << endl;
    nums.clear();
    nums.assign({3,5,2,1});
    cout << "Total subsets are ;  " << countMaxOrSubsets(nums) << endl;

    return 0;
}