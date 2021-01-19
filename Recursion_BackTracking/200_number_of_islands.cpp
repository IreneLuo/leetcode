class Solution {
    /* solution: DFS
     * Choice: search each item in grid with 4 directions
     *         if grid[x][y] == '1'--> we find an island
     *         keep reversing all the '1's adjacent to it to '0'
     * Constraints: x<n, y<m (out of boundary)
     * Goal: Traverse all the items in grid
     *
     * time complexity: O(mn)
     * space complexity: O(mn)
     */
public:
    int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
        int row = grid.size();
        int col = grid[0].size();
        for(int x = 0; x < row; x++){
            for(int y = 0; y < col; y++){
                //when we see a '1', increase the ans
                //then call dfs() to reverse all the '1' in this island
                //(reverse from 1 to 0)
                if(grid[x][y] == '1'){
                    ans++;
                    dfs(grid, x, y);
                }   
            }
        }
        return ans;
    }
    void dfs(vector<vector<char>>& grid, int x, int y){
        if(x < 0 || y < 0 || x == grid.size() || y == grid[0].size()) return;
        if(grid[x][y] == '0') return;
        grid[x][y] = '0';
        dfs(grid, x + 1, y);
        dfs(grid, x - 1, y);
        dfs(grid, x, y + 1);
        dfs(grid, x, y - 1);
    }
};
