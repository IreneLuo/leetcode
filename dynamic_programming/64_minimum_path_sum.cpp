class Solution {
public:
    /* solution 1: Dynamic Programming
     * Use an 2-D vector to save the minimum sum of each position.
     *  
     *  ex: dp[3][3], grid = [[1,3,1],[1,5,1],[4,2,1]]
     *  1 4 5
     *  2 x _   --> x = min(dp[1][0], dp[0][1]) + itself = min(2,4)+5=7
     *  6 _ _       (look up/left to find out a min sum)
     *  time complexity = O(mn)  //m,n are the row and col of grid
     *  space complexity = O(mn)
     *  
     * solution 2: recursive calls + memorization
     */
    int minPathSum(vector<vector<int>>& grid) {
    /* solution 1: */
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> dp(row, vector<int>(col));

        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                dp[i][j] = grid[i][j];
                if(i == 0 && j == 0)
                    continue;
                else if(i-1 < 0)
                    dp[i][j] += dp[i][j-1];
                else if(j-1 < 0)
                    dp[i][j] += dp[i-1][j];
                else
                    dp[i][j] += min(dp[i][j-1],dp[i-1][j]);
            }
        }
        return dp[row-1][col-1];

     /* solution 2
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> dp(row, vector<int>(col));
        return minSum(grid, row-1, col-1, dp);
     */
    }
    /*
    int minSum(vector<vector<int>>& grid, int x, int y, vector<vector<int>>& dp){
        if(x < 0 || y < 0)
            return INT_MAX;
        if(x == 0 && y == 0)
            return grid[0][0];
        if(dp[x][y] > 0)
            return dp[x][y];
        int left = minSum(grid, x, y-1, dp);
        int top =  minSum(grid, x-1, y, dp);
        dp[x][y] =  (min(left, top) + grid[x][y]);
        return dp[x][y];
    }
    */
};
