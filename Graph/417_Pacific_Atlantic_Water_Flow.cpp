class Solution {
    /* solution 1: Brute Force
     * Investigate each node to see if it can reach the Pacific ocean
     * and the Atlantic ocean (using DFS)
     *  - Choice: 4 directions (up, down, left, right)
     *  - Constraint: adjnode(h)<=current(h)
     *  - Goal: reach the Pacific Ocean (x<0 or y<0)
     *          reach the Atlantic Ocean(x > size or y > size)
     *          collect the nodes that can reach both
     * time complexity = O(4^mn) --> exceed time limit
     * (4 : branching factor = 4 directions)
     *
     */
public:
    /* solution 1
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<int>> ans; 
        for(int row = 0; row < matrix.size(); row++){
            for(int col = 0; col < matrix[0].size(); col++){
                    vector<int> temp;
                    if(dfs(matrix, row, col, matrix[row][col]) == 3){
                        temp.push_back(row);
                        temp.push_back(col);
                        ans.push_back(temp);
                    }
            }
        }
        return ans;
    }
    int dfs(vector<vector<int>>& matrix, int x, int y, int prev_height){
        if(x < 0 || y < 0) return 1;
        if(x == matrix.size() || y == matrix[0].size()) return 2;
        if(matrix[x][y] > prev_height) return 0;
        prev_height = matrix[x][y];
        //avoid considering current node when its neighbors make decisions
        matrix[x][y] = INT_MAX;
        int result = dfs(matrix, x-1, y, prev_height) |
                     dfs(matrix, x+1, y, prev_height) |
                     dfs(matrix, x, y-1, prev_height) |
                     dfs(matrix, x, y+1, prev_height);
        //recover current node's height
        //here's the root cause of this solution that lead to a exceed time limit
        matrix[x][y] = prev_height;
        return result;
    }
    soltuion 1*/
    /*  
     * solution 2:
     * 1. Collect the nodes in set A that these nodes can reach the Pacific Ocean
     * 2. Collect the nodes in set B that these nodes can reach the Atlantic Ocean
     * 3. Get the union of set A and B to find the answer
     * time complexity = O((m+n)+mn)
     * solution 3: dynamic programming
     * see HuaHua's video
     * might exceed time limit
     */
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
         if(matrix.size() == 0)
             return matrix;
         int row = matrix.size();
         int col = matrix[0].size();
         vector<vector<int>> ans;
         //to collect the nodes can reach the Pacific Ocean
         vector<vector<int>> pacific(row, vector<int>(col));
         //to collect the nodes can reach the Atlantic Ocean
         vector<vector<int>> atlantic(row, vector<int>(col));
         //try the nodes on left and right-> find the nodes that can
         //reach the Pacific and Atlantic Ocean
         for(int x = 0; x < row; x++){
             dfs(matrix, x, 0, matrix[x][0], pacific);//left
             dfs(matrix, x, col-1, matrix[x][col-1], atlantic);//right
         }
         //try the nodes on top and down-> find the nodes that can
         //reach the Pacific and Atlantic Ocean
         for(int y = 0; y < col; y++){
             dfs(matrix, 0, y, matrix[0][y], pacific);//top
             dfs(matrix, row-1, y, matrix[row-1][y], atlantic);//down
         }
         //collect the union
         for(int x = 0; x < row; x++){
             for(int y = 0; y < col; y++){
                 vector<int> temp;
                 if(pacific[x][y] && atlantic[x][y]){
                     temp.push_back(x);
                     temp.push_back(y);
                     ans.push_back(temp);
                 }
             }
         }
         return ans;
     }
    void dfs(vector<vector<int>>& matrix, int x, int y,int prev_height,
             vector<vector<int>>& reach){
        if(x < 0 || y < 0 || x == matrix.size() || y == matrix[0].size()) return;
        if(reach[x][y] || (matrix[x][y] < prev_height)) return;
        //mark this node as visited(1) so we won't visit it again
        //this will decrease the time complexity from exponential to linear
        reach[x][y] = 1;
        //try 4 directions
        dfs(matrix, x-1, y, matrix[x][y], reach);
        dfs(matrix, x+1, y, matrix[x][y], reach);
        dfs(matrix, x, y-1, matrix[x][y], reach);
        dfs(matrix, x, y+1, matrix[x][y], reach);
    }
};
