/* solution: memorization
 * Use a block of memory to store the numbers in
 * each row, column and box (here we use bitset)
 * We iterate over the matrix and check if the number
 * is in memeory or not.
 * time complexity = O(1)
 * space complexity = O(1)
 *
 */
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bitset<9> row[9], col[9], box[9];
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] == '.') continue;
                int num = board[i][j] - '0';
                if(row[i][num]) return false;
                row[i][num] = true;
                if(col[j][num]) return false;
                col[j][num] = true;
                int box_id = 3 * (i/3) + (j/3);
                if(box[box_id][num]) return false;
                box[box_id][num] = true;
            }
        }
        return true;
    }
};
