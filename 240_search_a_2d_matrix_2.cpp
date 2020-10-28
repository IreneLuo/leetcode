class Solution {
public:
    /* solution:
     * if we set matrix[0][cols-1] (the right-up item) as a starter and start searching the target
     * we could use following properties to find the target
     *  - if target > starter, search the matrix[1][cols-1] (increase the row idx to search a bigger value)
     *  - if target < starter, search the matrix[0][cols-1-1] (decrease the column idx to search a smaller value)
     * We could also set the starter to matrix[rows-1][0] (the left-bottom item)
     *  - if target > starter, search the matrix[rows-1][1] (increase the column idx to search a bigger value)
     *  - if target < starter, search the matrix[rows-1-1][0] (decrease the row idx to search a smaller value)
     *
     * time complexity: O(m+n), which m is number of columns, n is number of rows
     * space complexity: O(1)
     *
     * ex:  the worst case:
     *     [
     *      [1,   4,  7, 11, 15], --> if starter is 15
     *      [2,   5,  8, 12, 19],  |
     *      [3,   6,  9, 16, 22],  |
     *      [10, 13, 14, 17, 24],  | we have to go down for n steps, go left for m steps --> O(m+n)
     *      [18, 21, 23, 26, 30]   |
     *     ] |---------------------|
     *       v
     *     target is 18
     */
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0)
            return false;

        int starter_row = 0;
        int starter_col = matrix[0].size() - 1;

        while(starter_col >= 0 && starter_row <= matrix.size() - 1){
            int starter = matrix[starter_row][starter_col];
            if(target == starter)
                return true;
            else if(target < starter)
                starter_col--;
            else
                starter_row++;
        }
        return false;
    }
};
