class Solution {
    /* solution 1: recursion + memorization
     * dp[i] = min cost to reach the i-th step(not including climbing i-th)
     *       = min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2]);
     *
     *  pos  i-2  i-1  i
     *        |--------^  If I pay the cost[i-2], I can climb 2 steps to reach i
     *             |---^  If I pay the cost[i-1], I can climb 1 steps to reach i
     *  the answer is dp[n+1] since we have to climb n steps to reach the top floor
     * time complexity = O(n)
     * space complexity = O(n)
     *
     * solution 2: dynamic programming
     */
public:
    int minCostClimbingStairs(vector<int>& cost) {
        /* solution 1:
        vector<int> dp(cost.size() + 1, 0);
        return find_cost(cost, dp, dp.size() - 1);
        */
        /* solution 2: */
        vector<int> dp(cost.size() + 1, 0);
        for(int i = 2; i <= cost.size(); i++){
            dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
        }
        return dp[cost.size()];
    }
    int find_cost(vector<int>& cost, vector<int>& dp, int i){
        //0 cost for step 0 and 1
        if(i <= 1) 
            return 0;
        if(dp[i] > 0)
            return dp[i];
        dp[i] = min(find_cost(cost, dp, i-1) + cost[i-1],
                   find_cost(cost, dp, i-2) + cost[i-2]);
        return dp[i];
    }
};
