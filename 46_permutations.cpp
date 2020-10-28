class Solution {
public:
    /* solution:
     * for permutation problems
     * the recursive calls will need n * n-1 * n-2 * ... * 1 = n!
     * ex: 
     *             1,2,3
     *        /      |      \       --> 3 choices
     *      1__     2__     3__
     *      / \     / \     / \     --> 2 choices
     *    12_ 13_  21_ 23_ 31_ 32_
     *     |   |    |   |   |   |   --> 1 choice
     *    123 132  213 231 312 321
     *
     * time complexity = O(n!) // e*n! =O(n1)
     * space complexity = O(n) // the depth of the call stack
     * note: can I use a queue instead of using a for loop?
     */
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        //use to record that the member in nums has been used or not
        vector<bool> numsAlreadyUse(nums.size(), false);
        _permute(nums, numsAlreadyUse, {}, ans);
        return ans;
    }
    void _permute(vector<int>& nums, vector<bool>& numsAlreadyUse,
                  vector<int> cand, vector<vector<int>>& ans){

        if(cand.size() == nums.size()){
            ans.push_back(cand);
            return;
        }
        for(int i = 0; i < nums.size(); i++){
            if(numsAlreadyUse[i])
                continue;
            cand.push_back(nums[i]);
            numsAlreadyUse[i] = true;
            _permute(nums, numsAlreadyUse, cand, ans);
            cand.pop_back();
            numsAlreadyUse[i] = false;
        }
    }
};
