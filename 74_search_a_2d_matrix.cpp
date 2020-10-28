class Solution {
public:
    /* solution: binary search
     * we can consider the input as a sorted array since it has properties that mentioned in the problem
     * 1. set the left/right boundery
     * 2. get the middle idx and retrieve the value
     *    if middle value < target, reset the left boundery -->left = middle + 1
     *    if middle value > target, reset the right boundery --> right = middle - 1
     * 3. searching the target by using the new left and right boundery
     *
     * time complexity = O(log(rc)), which r is number of rows, c is number of columns, r*c is the total number of items in matrix
     * space complexity = O(1)
     */
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0)
            return false;

        int rows = matrix.size();
        int columns = matrix[0].size();
        int left = 0;
        int right = (rows * columns) - 1;

        while(left <= right){
            int middle = (left + right) / 2;
            int middle_val = matrix[middle / columns][middle % columns];
            if(middle_val == target)
                return true;
            else if(middle_val < target)
                left = middle + 1;
            else
                right = middle - 1;
        }
        return false;
    }
};
