class Solution {
    /* solution: dynamic programming
     * How can we choose the house to rob?
     * if nums = [2,1,1,2]
     *     2 1 1 2
     *     v   v
     *       v   v
     *     v     v --> ?? so we have to think about x house[i-1], x house[i-2] v house[i], v house[0]
     *
     * Method 1: 
     *   nums = [A, C, D, E] B = 0
     *   house    yes             no        
     *     0       A           /-> B
     *     1      C+B         /->  A
     *     2   D+max(A,B)    /->  C+B
     *     3   E+max(A,B,C+B)  D+max(A,B)
     *
     * --> the total max amount of $ if you rob house 3 = E+max(A,B,C+B)
     *     since we can rob house 3 + any choice : (don't rob house 2 but rob house 1 or
     *                                               don't rob house 1 but rob house 0 or
     *                                               don't rob house 0)
     * --> the total max amount of $ if you don't rob house 3 = D+max(A,B)
     *     since we can rob house 2
     *
     *  time complexity = O(n)
     *  space complexity = O(n)
     * 
     * Method 2: huahua's method
     *  dp[i] = max amount of $ (choose house i, don't choose i)
     *        = max(num[i] + dp[i-2], dp[i-1])
     *
     */
public:
    int rob(vector<int>& nums) {
/* method 2 */
        if(nums.empty()) return 0;
        vector<int> dp(nums.size(), 0);
        //dp[0] = nums[0];
        //dp[1] = max(nums[1], nums[0]);
        for(int i = 0; i < nums.size(); i++){
            dp[i] = max(((i < 2) ? 0 : dp[i-2]) + nums[i],
                        ((i < 1) ? 0 : dp[i-1]));
        }
        return dp.back();
/* method 1
        if(nums.size()== 0)
            return 0;
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2));
        //dp[i][0]: the total amout of money if we choose house i
        //dp[i][1]: the total amout of money if we don't choose house i
        dp[0][0] = nums[0];
        dp[0][1] = 0;
        //the max amount of money for dp[0][1]~dp[i-1][1] --> we'll use it to decide dp[i][1]
        int max_without = dp[0][1];
         //the max amount of money for dp[0][0]~dp[i-1][0] --> we'll use it to decide dp[i][0]
        int max_with = dp[0][0];

        for(int i = 1; i < n; i++){
            dp[i][0] = nums[i] + max_without;
            dp[i][1] = max_with;
            max_without = max(max_without, dp[i][1]);
            max_with = max(max_with, dp[i][0]);
        }
        return max(dp[n-1][0], dp[n-1][1]);
*/
    }
};
