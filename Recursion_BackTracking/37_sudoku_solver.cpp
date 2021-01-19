class Solution {
public:
    /* solution: recursive calls
     * choice: char '1'-'9'
     * constraints: row/col/subbox , each char appears once
     * goal: fill all the entries
     * time complexity = O(n^(n^2))
     * space complexity = O(n^2)
     * For reference, see HuaHua's video
     */

    //time complexity = O(n^2)
    bool canplacevalue(vector<vector<char>>& board, char ch, int row, int col){
        //check the entries on this row --> O(n)
        for(int i = 0; i < board[row].size(); i++){
            if(board[row][i] == ch)
                return false;
        }
        //check the entries on this column --> O(n)
        for(int i = 0; i < board.size(); i++){
            if(board[i][col] == ch)
                return false;
        }
        //check the entries on this subbox--> O(n^2)
        int startOfSubbox_row = (row / 3) * 3;
        int startOfSubbox_col = (col / 3) * 3;
        for(int i = startOfSubbox_row; i < startOfSubbox_row+3; i++){
            for(int j = startOfSubbox_col; j < startOfSubbox_col+3; j++){
                if(board[i][j] == ch)
                    return false;
            }
        }
        return true;
    }
    bool solvefromcell(vector<vector<char>>& board, int row, int col){
        static char EMPTY = '.';
        // if col is out of bound, move to the next row
        // if both row and col is out of bound, return true because it means we hit the end of the board
        if(col == board[0].size()){
            col = 0;
            row++;
            if(row == board.size())
                return true;
        }
        // if this entry is not empty, go to the next entry
        if(board[row][col] != EMPTY){
            return solvefromcell(board, row, col+1);
        }
        //branching factor = n (1 node has )
        //depth = n^2 (because each path must has n^2 nodes to finish sudoku)
        //total = O(bf^depth) =  O(n^(n^2))
        //      abcd....        //the answer set
        //   / / /  \ \ \ ...\
        //  1 2 3   5 6 7    n  //for entry "a"      -
        //     / \                                   | => depth = n^2
        //   31_ 3n_            //for entry "b"      |
        //   ..  ..             //for the last entry -
        for(int i = 1; i <= board.size(); i++){
            char cand = (char)(i + '0');
            //can we put cand to this position?
            //if we can, go to the next entry
            //if the next entry still works fine, then return true.
            //otherwise we clean the cand, reset to EMPTY and keep trying next character
            if(canplacevalue(board, cand, row, col)){
                board[row][col] = cand;
                if(solvefromcell(board, row, col+1))
                    return true;
                board[row][col] = EMPTY;
            }
        }
        return false;
    }
    void solveSudoku(vector<vector<char>>& board) {
        solvefromcell(board, 0, 0);
    }
};
