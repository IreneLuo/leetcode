/* Solution: dynamic programming
 * Key point is to "find the pattern"
 * Before looking into the example, let's define a dp table
 *  dp[i][j] = numbers of line segments when nodes = i and segements = j
 *                           i = 0    1    2   3
 * Example: n = 4, k = 2         *    *    *   *
 *                               |---||---|        |
 *                               |---||--------|   |--> 1. if we pick i=1, and fix a segment(0,1), then we only have 3 points left to decide 1 segment
 *                               |---|    |----|   |       ==> dp[n,k] = dp[n-1, k-1]
 *                               |--------||---|   |--> 2. if we pick i=2, and fix a segment(0,2), then we only have 2 points left to decide 1 segment
 *                                                         ==> dp[n,k] = dp[n-2, k-1]
 *                                    |---||---|   |--> 3. if we ignore the first point, then we only have 3 points left to decide 2 segments
 *                                                         ==> dp[n,k] = dp[n-1, k]
 *   We can combine cases 1 and cases 2 together
 *   ==> dp[n,k] = dp[n-i, k-1], 1<=i<n-k
 *       (if we pick i, then n-i-1 nodes left --> can draw n-i-2 lines and n-i-2 must >= k-1 --> n-i-1 >= k --> n-k>=i+1 --> i <= n-k-1)
 *   Let's combine case 1,2,3 together
 *   ==> dp[n,k] = sum(dp[n-i, k-1]) + dp[n-1, k] ##
 *                  |--> 1<=i<n-k
 *
 * Implements: we use a dp table to calculate the answer
 *
 *   step 1: initialize                            step 2: fill-in the blanks
 *     k =  0  1  2                                k =  0   1    2
 *      --|----------                               --|------------
 *   n = 0| 0  0  0  ---->(1)                    n = 0| 0  |0|   0
 *       1| 1                                        1| 1  |0|   0
 *       2| 1                         ------->       2| 1  |1|   0
 *       3| 1                                        3| 1  |3|  |1| 
 *       4| 1 ----------> (2)                        4| 1   5    5 --> (3)
 *   (1) when n = 0, it's impossible to get any segments
 *   (2) when k = 0, there's only 1 way to get 0 segments
 *   (3) dp[4][2] = dp[0 to 4][1] + dp[3][2]
 *
 *  time complexity = O(nk)
 *  space complexity = O(nk)
 */
class Solution {
public:
    int numberOfSets(int n, int k) {
        //since we starts from 0, so our table size will be (n+1)*(k+1)
        int dp_row = n + 1;
        int dp_col = k + 1;
        int mod = pow(10, 9) + 7;
        int dp[dp_row][dp_col];
        //initialize
        for(int col = 0; col < dp_col; col++)
            dp[0][col] = 0;
        //initialize
        for(int row = 1; row < dp_row; row++)
            dp[row][0] = 1;
        //fill-in the blanks (note that we fill in column by column)
        for(int col = 1; col < dp_col; col++){
            int sum = dp[0][col-1];
            for(int row = 1; row < dp_row; row++){
                dp[row][col] = (sum + dp[row-1][col]) % mod;
                //we add dp[row][col-1] to sum for the next iteration (dp[row+1][col]) can use
                sum = (sum + dp[row][col-1]) % mod;
            }
        }
        return dp[n][k];
    }
};
