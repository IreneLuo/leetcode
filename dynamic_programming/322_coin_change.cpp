//#define SOLUTION_1
#define SOLUTION_2
class Solution {
public:
    /* solution: bottom-up dynamic programming
     * time complexity = O(A*C)
     * space complexity = O(A)
     * 
     * method 1
     *  amount: 0   1  2 .... i
     *  ans   :               x
     *  if choose coin 1: 1 + dp[i-1] //amountleft = i-1
     *  if choose coin 2: 1 + dp[i-2] //amountleft = i-2
     *  if choose coin 5: 1 + dp[i-5] //amountleft = i-5
     *  x = max(1 + dp[i-1], 1 + dp[i-2], 1 + dp[i-5])
     *
     * note that for top-down method
     * see "back to back swe"
     */
    int coinChange(vector<int>& coins, int amount) {
#ifdef SOLUTION_1
        //history[i] = the min coin change of the amount i
        // ex: amount = 11 --> we create a vector in size amount+1
        //     idx: 0   1  2 .... 11
        // default: 12 12 12 .....11
        vector<int> history(amount+1, amount+1);
        //base case: the min coin change for 0 is 0
        history[0] = 0;
        // ex: coins = 1,2,5
        // every time, we consider that amount = coins[i] * 1 + amountleft --> we choose 1 of coins[i] and x of amountleft
        // x is the history that we saved in  history[amountleft]
        // so the total coin change  = 1 + x = 1 + history[amountleft]
        for(int a = 1; a <= amount; a++){
            for(int c = 0; c < coins.size(); c++){
                if(coins[c] <= a)
                    //we have to get the min value because we calculate with several coins
                    history[a] = min(history[a-coins[c]] + 1, history[a]);
            }
        }
        // if the history[amount] = default value return -1
        return history[amount] > amount ? -1 : history[amount];
#endif
#ifdef SOLUTION_2
        vector<int> history(amount+1, INT_MAX);
        history[0] = 0;
        return _coinChange(coins, history, amount);
#endif
    }
#ifdef SOLUTION_2
    int _coinChange(vector<int>& coins, vector<int>& history, int amountLeft){
        if(amountLeft < 0)
            return -1;
        if(amountLeft == 0)
            return 0;
        if(history[amountLeft] != INT_MAX)
            return history[amountLeft];

        int min = INT_MAX;
        for(int i = 0; i < coins.size(); i++){
            int change = _coinChange(coins, history, amountLeft - coins[i]);
            //if change is -1, coin is not large enough to change, so we don't update history[]
            if(change >= 0 && change < min)
                min = change + 1;
        }
        //if coins are larger than amountLeft, the history[] will be INT_MAX
        //because we cannot find any solution to change coins
        history[amountLeft] = (min == INT_MAX) ? -1 : min;
        return history[amountLeft];
    }
#endif
};
