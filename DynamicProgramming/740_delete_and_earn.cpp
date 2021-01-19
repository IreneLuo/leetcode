class Solution {
/* Solution: dynamic programming
 * We use a dp table to record down the max number of points of
 * choosing/not to choose nums[i]
 * In this dp table, we have 2 columns:
 *  [i][0] = max points of choosing nums[i]
 *  [i][1] = max points of not choosing nums[i]
 *
 * There are 3 situations for numbers that we'll encounter in the input:
 *  1. nums[i] == nums[i-1]
 *     dp[i][YES] = nums[i] + dp[i-1][YES]
 *         => if we choose nums[i], max points = nums[i] + we choose nums[i-1]
 *            (since nums[i]==nums[i-1], so we must choose nums[i-1])
 *     dp[i][NO] = dp[i-1][NO]
 *         => if we don't choose nums[i], then we must cannot choose nums[i-1]
 *            either, since they are the same
 *  2. nums[i] - nums[i-1] = 1
 *     dp[i][YES] = nums[i] + dp[i-1][NO]
 *         => if we choose nums[i], we cannot choose nums[i-1]
 *     dp[i][1] = max(dp[i-1][YES],dp[i-1][NO]);
 *         => if we don't choose nums[i], we still can choose or not to choose
 *            nums[i-1]. Hence, we have to select a max one.
 *  3. nums[i] != nums[i-1] (General Case)
 *     dp[i][0] = nums[i] + max(dp[i-1][YES],dp[i-1][NO]);
 *         => if we choose nums[i], we still can choose or not to choose
 *            nums[i-1]. Hence, we have to select a max one.
 *     dp[i][1] = max(dp[i-1][0],dp[i-1][1]);
 *         => if we don't choose nums[i], we still can choose or not to choose
 *            nums[i-1]. Hence, we have to select a max one.
 *
 *  Note that this solution depends on the numbers' order, so we have to sort
 *  them first.
 *
 *  time complexity = O(nlogn)
 *  space complexity = O(1)
 *
 *  test case: [1,1,1,2,4,5,5,5,6] [1,1,3,3,3,4,6,8,8,10]
 *   
 *         [1, 1, 3, 3, 3, 4, 6, 8, 8, 10]
 *    yes:  1  2  5  8  11 6  12 20 28 38
 *     no:  0  0  2  2  2  11 11 12 12 28
 *                   |     |---> case 1 |--> case 3
 *                   |-> case 1
 */
public:
    int deleteAndEarn(vector<int>& nums) {
        if(nums.empty())
            return 0;
        int n = nums.size();
        //sort the input
        sort(nums.begin(), nums.end());
        //initialize dp table
        vector<vector<int>> dp(n, vector<int>(2));
        //if we choose nums[0], the max points = nums[0]
        dp[0][0] = nums[0];
        //if we don't choose nums[0], the max points is zero
        dp[0][1] = 0;
        for(int i = 1; i < n; i++){
            if(nums[i] == nums[i-1]){
                dp[i][0] = nums[i] + dp[i-1][0];
                dp[i][1] = dp[i-1][1];
            }else if((nums[i] - nums[i-1]) == 1){
                dp[i][0] = nums[i] + dp[i-1][1];
                dp[i][1] = max(dp[i-1][0],dp[i-1][1]);
            }else{
                dp[i][0] = nums[i]+max(dp[i-1][0],dp[i-1][1]);
                dp[i][1] = max(dp[i-1][0],dp[i-1][1]);
            }
        }
        return max(dp[n-1][0], dp[n-1][1]);
    }
};
