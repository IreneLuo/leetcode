class Solution {
public:
    /* solution: dynamic programming
     * for position [m][n], the number of paths could be:
     *    from its up position: [m-1][n]
     *    or from its left position: [m][n-1]
     *    --> the number of paths  = [m-1][n] + [m][n-1]
     *           [m-1][n]
     *            |
     *            v
     *     [m][n-1]-->[m][n]
     * Example: 
     *   m = 3, n = 3
     *   start-> _1_ _1_ _1_
     *           _1_ __ __
     *           _1_ __ __ <--end
     *   1. initialize table[0][col] and table[row][0] to 1 --> only 1 path
     *   2. calculate the rest of answers
     *      ex: table[1][1] = table[0][1] + table[1][0] = 2 --> total 2 paths
     *   start-> _1_ _1_ _1_
     *           _1_ _2_ _3_
     *           _1_ _3_ _6_ <--end
     *  time complexity = O(mn)
     *  space complexity = O(mn)
     */
    int uniquePaths(int m, int n) {
        int path[m][n];
        for(int row = 0; row < m; row++)
            path[row][0] = 1;
        for(int col = 0; col < n; col++)
            path[0][col] = 1;

        for(int row = 1; row < m; row++){
            for(int col = 1; col < n; col++){
                path[row][col] = path[row-1][col] + path[row][col-1];
            }
        }
        return path[m-1][n-1];
    }
};
