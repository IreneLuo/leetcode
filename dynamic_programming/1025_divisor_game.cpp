class Solution {
public:
    /* dp[i]: can Alice win the game when N==i
     * base cases are:
     * dp[1] = false (if Alice starts with 1, she'll lose)
     * dp[2] = true  (Alice will win)
     * dp[3] = false (3-> x=1(A) ->2 ->x=1(B) -> 1(A) )
     * note that dp[0] will not use just for padding
     *
     * dp: [0] [1] [2] [3] [4] [5] ... [N]
     *          f   t   f   ?
     * for dp[4] we can find x from 1 to 3
     *    --> if Alice choose x = 1, then N = 4-1=3, then we look dp[3]
     *        dp[3] = false, so Alice will win
     *    --> if Alice choose x = 2, then N = 4-2=2, then we look dp[2]
     *        dp[2] = true, so Alice will fail
     *        However, Alice won't choose 2 since both players play optimally.
     * note that since every number can be divided by 1, so we choose x = 1,
     * then the operation will be simple, just look up the table[N-1]
     * 
     * time complexity = O(n)
     * space complexity = O(n)
     * 
     * solution 2: finding regular rules
     * If Alice starts with a even number, Alice will win.
     * dp: [0] [1] [2] [3] [4] [5] ... [N]
     *          f   t   f   t   f
     */
    bool divisorGame(int N) {
        vector<bool> dp(N+1, false);
        dp[2] = true;
        if(N <= 3)
            return dp[N];
        int x = 1;
        for(int i = 4; i <= N; i++){
            //for optimization, we fix x at 1
            //for(int x = 1; x < i; x++){
                if((i % x == 0) && (dp[i-x] == false)){
                    dp[i] = true;
                }
        }
        return dp[N];
        /*
        return ((N & 1) == 0);
        */
    }
};
