class Solution {
    /* solution: Graph
     * dp[k][v] = the cheapest price from src to v with up to k stops
     *          = price from src to u + price from u to v
     *          = dp[k-1][u] + price(u,v)
     *
     * the dp table looks like this:
     *    v  0   1   2     
     * k---------------     1. We assume that Point 0 is src, so dp[0~k][0] = 0
     * 0  |  0                (price will be 0 from src to src)
     * 1  |  0              2. All the other elements in dp table will be updated
     * 2  |  0                 while we traverse the edges
     * ...|                    Ex: [0,1,100] we consider 0 as u, 1 as v
     * k  |  0                   so dp[k][1] = from src-> u with k-1 stops + 
     *                                         price(0->1) (the last stop)
     *                                         (dp[k-1][u] + 100)
     * Ex: n = 3, k = 1
     *   A------>B------>C
     *   |---------------^
     *  ==> if k = 0, ans = price(A->C) = 500
     *      if k = 1, ans = price(A->B->C) = 100+100=200
     *  so the final answer = min(500, 200) = 200
     * 
     *  Note 1. K stops can reach K+1 cities, which means that the K+1-th stop is the
     *          the destination, so our dp table size is [K+2][n]
     *          row numbers: 0 ~ K+1
     *          dp[K+1][dst] will be the answer
     *  Note 2. We set the table with 1e9 for initialization to represent the infinitive
     *          price. We cannot set to INT_MAX, because when INT_MAX+cost will overflow.
     *          1e9 will be enough. (max price = 10000, size of flight = 100^2)
     * For DFS/BFS solution, see HuaHua's video
     */
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<vector<int>> dp(K+2, vector<int>(n, 1e9));
        dp[0][src] = 0;

        for(int k = 1; k <= K+1; k++){
            dp[k][src] = 0;
            for(auto edge: flights){
                int transfer = edge[0];
                int dst = edge[1];
                int cost = edge[2];
                dp[k][dst] = min(dp[k-1][transfer] + cost, dp[k][dst]);
            }
        }
        return (dp[K+1][dst] == 1e9) ? -1 : dp[K+1][dst];
    }
};
