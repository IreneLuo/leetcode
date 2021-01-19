class Solution {
public:
    /* solution 1: dynamic programming
     * We use an array to record the result of each subproblem.
     *  - arr[i] = the length the increasing subsequence that ends up at index[i]
     * ex: 
     *      we initialize each element to 1 since arr[i] is the smallest
     *      increasing subsequence.
     *
     *      [10,9,2,5,3,101,18]
     * arr    1 1 1 1 1  1  1   // default 1
     *        1 1 1 2           -> only 2>5, so 2,5 is increasing, arr[3]=1+arr[2]
     *        1 1 1 2 2  3      -> we have to get the max so the max is 1+2=3
     *        1 1 1 2 2  3  4   -> 4 is the final answer
     *      so our longest increasing subsequence is
     *      2,5,101,18 or 2,3,101,18
     *
     * note) non-decreasing != strictly increasing
     *       (because of a sequence of same value)
     *   but,strictly increasing == non-decreasing
     */
    /*
    int lengthOfLIS(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
 
        //initialize elements to 1
        vector<int> history(nums.size(), 1);
        //start to calculate the longest increasing subsequence at index i
        int maxSoFar = 1;
        for(int i = 1; i < nums.size(); i++){
            for(int j = 0; j < i; j++){
                if(nums[i] > nums[j]){
                    history[i] = max(history[i], 1 + history[j]);
                }
            }
            maxSoFar = max(maxSoFar, history[i]);
        }
        return maxSoFar;
    }*/

    /* solution 2: binary search tree + dp
     * We use a dynamic programming vector "dp" here.
     * dp[i] = the element that has an increasing subsequence of length i
     * We iterate over the input nums,
     * and insert num into our vector "dp" by using binary search algorithm
     * the insert position will be at i which dp[i] is the first element >= num.
     *
     * Ex:    [4,10,4,3,8,9] len
     *  dp =   4               1  --> initialize dp[0] = nums[0], len = 1
     *     =   4,10            2  --> i = 1, 10 > 4 so add 10 after 4
     *     =   4,10            2  --> i = 2, we have to find a position for nums[2] in dp table
     *                                by bst_find_pos(), we find dp[0] is the first element that
     *                                >= nums[2], so update dp[0] = nums[2]
     *     =   3,10            2  --> i = 3, dp[0] = 4 is the first element that > nums[3]
     *                                so update dp[0] = nums[3]
     *     =   3,8             2  --> i = 4, dp[1] = 10 is the first element that > nums[4]
     *                                so update dp[1] = nums[4]
     *     =   3,8,9           3  --> i = 5, dp[1] = 8 < nums[5], so add 9 after 8
     *    now, we can return len = 3
     *    How can we explain dp[]?
     *   idx = 0  1  2
     *    dp = 3, 8, 9
     *         |  |  |---> the LIS before 9 (include 9) = 3
     *         |  |------> the LIS before 8 (include 8) = 2
     *         |---------> the LIS before 3 (include 3) = 1
     *   ==> dp[n] means : the LIS before dp[n] (include dp[n]) = n+1
     *
     * time complexity = O(nlogn)
     * space complexity = O(n)
     *
     * More test case
     * [4,10,4,3,8,9]
     * [10,9,2,5,3,7,101,18]
     * [1,3,6,7,9,4,10,5,6]
     * [3,5,6,2,5,4,19,5,6,7,12]
     */
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty())
            return 0;
        vector<int> dp(nums.size(), 0);
        int len = 1;
        dp[0] = nums[0];
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] > dp[len-1]){
                dp[len++] = nums[i];
            }else{
                int pos = bst_find_pos(dp, 0, len-1, nums[i]);
                dp[pos] = nums[i];
            }
        }
        return len;
    }
    /* binary search
     * return the first element that is equal or bigger than target
     */
    int bst_find_pos(vector<int>& dp, int left, int right, int target){
        while(right > left){
            int m = left + (right - left)/2;
            if(target == dp[m]) //if find the same value, return middle
                return m;
            /* ex: 2,5,6 target=4
             *     l m r
             *  1. if(target < dp[m]) right = m-1
             *     --> 2, 5  --> then we'll get a position at 2 but it't wrong
             *        lrm 
             *  2. if(target < dp[m]) right = m
             *     --> 2, 5 --> 2, 5 --> then we'll get a position at 5 correct.
             *         lm r        lr  
             */
            else if(target < dp[m])
                right = m;
            else
                left = m + 1;
        }
        if(right < 0)
            return 0;
        else if (right >= dp.size())
            return dp.size()-1;
        return right;
    }
};
