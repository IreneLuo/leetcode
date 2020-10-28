//[[1,1,1],[1,1,1],[1,1,1]]
#include <unordered_set>
class Solution {
  public:
                    //up left right down
    int offsetX[4] = {-1, 0, 0, 1};
    int offsetY[4] = {0, -1, 1, 0};
    // x means index of rows, y means index of columns
    void explore(vector<vector<int>>& grid, int x, int y, string& path){
      //set this node to "visited' status
      grid[x][y] = 0;
      // check all the adjacent nodes
      for(int i = 0; i < 4; i++){
        int next_x = x + offsetX[i];
        int next_y = y + offsetY[i];
        if(next_x < grid.size() && next_x >= 0 &&
           next_y < grid[x].size() && next_y >= 0 &&
           grid[next_x][next_y] == 1){
             //if next position is legal, add direction into path
              path += to_string(i);
              explore(grid, next_x, next_y, path);
            }
      }
      path+='b';
    }
    int numberOfDistinctIslands(vector<vector<int>>& grid) {
        unordered_set<string> islands;
        //go through each node and explore it by checking all the adjacent nodes
        for(int i = 0; i < grid.size(); i++){
          for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j]){
              string path = "";
              explore(grid, i, j, path);
              // we use path to save the directions of an islands
              // the direction can help us identiy the island is distinct or not
              islands.insert(path);
            }
          }
        }
        return islands.size();
    }
};
