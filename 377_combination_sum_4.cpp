/* Similar Questions
 * 39_combination_sum: return all the unique combinations that sums up to target
 * 377_combination_sum_IV: return the count of combinations that sums up to target
 *                         (the question won't ask to list all the combinations since different sequences are counted as different combinations)
 * score_combinations: similar to 39, but return the count of all the unique combinations that sums up to target --> not using recursive calls
 * 77. Combinations: return a list of k numbers at a time and k can be choose from 1 to n
 */
class Solution {
public:
    /* solution: dynamic programming
     * We use a history table to save the number of combinations of target t.
     * If we don't do this, a "Time Limit Exceeded" error will occur.
     * Note that our history table includes those duplicate cases
     * so if the question is asking for non-duplicate answer, then we cannot use this method.
     * 
     * time complexity = O(T)
     *   - branching factor = N (nums size)
     *   - depth = Target/smallest num = S
     *   generally, the time complexity = N^S, but we use a history table here
     *   so only the leftmost subtree need some time to finish (like a linked list, so actually we only spend linear time here)
     *   the rest of subtrees can be done by accessing the table, which only cost constant time
     * space complexity = O(T) T=target, for history table
     *
     * ex: [1,2,3] t= 4
     *                                     4          --> 7. after finishing these 3 nodes, update history[4] = 4 + 2 + 1 = 7 ==> the answer
     *                        [1]         [2]  [3]
     *                         |-----------|----|
     *                         3           2    1
     *               [1]      [2]  [3]     |    |-------> 6. we look up history table and get the value 1 (history[1] = 1)
     *                |--------|----|      |------------> 5. we look up history table and get the value 2 (history[2] = 2)
     *                2        1    0                      
     *      [1]      [2]  [3]  |    |-------------------> 4. after finishing these 3 nodes, update history[3] = 2 + 1 + 1 = 4
     *       |--------|----|   |------------------------> 3. we look up history table and get the value 1 (history[1] = 1)
     *       1        0   -1
     *  [1] [2] [3]   |---------------------------------> 2. after finishing these 3 nodes, update history[2]=1+1 (target 2 has 2 combinations: [1,1] and [2])
     *   |---|---|
     *   0  -1  -2
     *   |----------------------------------------------> 1. after finishing these 3 nodes, update history[1] = 1 (target 1 has 1 combination: [1])
     *
     */
    int combinationSum4(vector<int>& nums, int target) {
        int ans = 0;
        sort(nums.begin(), nums.end());
        vector<int> history(target + 1, -1);
        return try_one_number_with_history(nums, target, history);
        /* This is a failed function that might lead to a time limit exceeded error.
         * However, this function is a classic method of dealing with permutation problems.
         * So I keep the funtion here as a remind.
         */
        //try_one_number_without_history(nums, target, ans);
        //return ans;
    }
    int try_one_number_with_history(vector<int>& nums, int target, vector<int>& history){
        if(target == 0){
            return 1;
        }
        if(target < 0){
            return 0;
        }
        if(history[target] >= 0){
            return history[target];
        }

        int childWays = 0;
        for(int i = 0; i < nums.size(); i++){
            int targetLeft = target - nums[i];
            //cout<<"target - nums = "<<target<<" - "<<nums[i]<<" = "<<targetLeft<<endl;
            childWays += try_one_number_with_history(nums, targetLeft, history);
        }
        history[target] = childWays;
        //cout<<"history "<<target <<" = "<< history[target]<<endl;
        return history[target];
    }

    void try_one_number_without_history(vector<int>& nums, int target, int& ans){
        if(target == 0){
            ans++;
            return;
        }

        for(int i = 0; i < nums.size(); i++){
            int targetLeft = target - nums[i];
            if(targetLeft < 0)
                break;
            try_one_number_without_history(nums, targetLeft, ans);
        }
        return;
    }
};
