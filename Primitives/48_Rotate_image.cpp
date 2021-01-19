/* 
 * solution 1: reverse(bottom->top) + transpose
 * solution 2: 
 * Rotate clockwise: transpose  +  reverse
 *                   (row->col)   (left->right)
 *
 *    1  2  3  4     t   1  5  9 13   r  13  9 5 1
 *    5  6  7  8    -->  2  6 10 14  --> 14 10 6 2
 *    9 10 11 12         3  7 11 15      15 11 7 3
 *   13 14 15 16         4  8 12 16      16 12 8 4
 *
 * solution 3: move in rectangles
 */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        /* solution 1: reverse(bottom->top) + transpose */
        reverse(matrix.begin(), matrix.end());
        for(int i = 0; i < matrix.size(); i++){
            for(int j = i; j < matrix.size(); j++){
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        /* solution 2
        for(int i = 0; i < matrix.size(); i++){
            for(int j = i; j < matrix.size(); j++){
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        int col = matrix[0].size();
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix.size()/2; j++){
                swap(matrix[i][j], matrix[i][col-j-1]);
            }
        }*/
        /* solution 3:
        int n = matrix.size();
        for(int i = 0; i < (n+1)/2; i++){
            for(int j = 0; j < n/2; j++){
                int tmp = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = matrix[i][j];
                matrix[i][j] = tmp;
            }
        }*/
    }
};

    
