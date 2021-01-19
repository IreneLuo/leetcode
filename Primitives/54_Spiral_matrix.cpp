/* solution 1:
 * Use a big map with boundaries and go over the map step by step
 * If we meet the boundary, change the direction
 * time complexity = O(n)
 * space complexity = O(n)
 *
 * solution 2: layer-by-layer
 * time complexity = O(n)
 * space complexity = O(1) //save more space
 */
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {

        if (matrix.size() == 0)
            return {};
/*
        int m = matrix.size();
        int n = matrix[0].size();
        int steps = m * n;
        vector<int> ans;
        int x = 0, y = 0;
        //current direction
        int i = 0;
        // offset of right, down, left, up
        vector<vector<int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        // record each element has been visited or not
        vector<vector<int>> set;

        // initialize set
        // -1 -1 -1 -1 -1
        // -1  0  0  0 -1
        // -1  0  0  0 -1
        // -1  0  0  0 -1
        // -1 -1 -1 -1 -1
        for (int o= 0; o < m +2; o++) {
            vector<int> temp;
            for (int p = 0; p < n + 2; p++) {
                if (o >= 1 && o <= m && p >= 1 && p <= n)
                    temp.push_back(0);
                else
                    temp.push_back(-1);
            }
            set.push_back(temp);
        }        
        // traverse the matrix
        // 1. push current item into ans by reading matrix[x][y]
        // 2. set 1 in vector set as visited state
        // 3. check next item has been visited or not.
        // 4. if yes, change direction and update x, y value
        while(steps > 0) {
            ans.push_back(matrix[x][y]);
            set[x+1][y+1] = 1;       
            if(set[x+directions[i][0]+1][y+directions[i][1]+1] != 0)
                i = (i+1) % 4;
            x+=directions[i][0];
            y+=directions[i][1];
            steps--;
        }      
        return ans;
*/
        /* solution 2 */
        int r1 = 0, c1 = 0;
        int r2 = matrix.size()-1, c2 = matrix[0].size()-1;
        vector<int> ans;
        while(r1 <= r2 && c1 <= c2){
            //top
            for(int col = c1; col <= c2; col++) ans.push_back(matrix[r1][col]);
            //right
            for(int row = r1+1; row <= r2; row++) ans.push_back(matrix[row][c2]);
            //if more than 1 rows and 1 cols in the matrix
            if(r1 < r2 && c1 < c2){
                //bottom
                for(int col = c2-1; col >= c1; col--) ans.push_back(matrix[r2][col]);
                for(int row = r2-1; row > r1; row--) ans.push_back(matrix[row][c1]);
            }
            ++r1;
            ++c1;
            --r2;
            --c2;
        }
        return ans;
    }
};
