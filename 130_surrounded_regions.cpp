#define SAFE 'X'
#define UNSAFE 'O'
#define VISITED 'V'

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        //for edge cases like []
        if(board.size() == 0)
            return;

        /*1. check the borders, if there's any 0 at the border,
         *   flip it to symbol 'V', and investigate it's neighbors
         * 
         *  ex: 4 borders of a matrix are as follow
         * left  right
         *   ^     ^
         *  [X X X X]  top
         *   X O O X
         *   X X O X 
         *  [X O X X]  down
         *   v |    v
         *     |-------> we find an 'O' here, so investigate its neighbors to check  "O" 's regions, and mark them into "V" 
         *   
         *   after checking all the borders and marking all "O"(those related to the borders) to "V"
         *   we can mark all "O" (those unrelated to the borders) to "X"
         *   Finally, recover the matrix by chaning "V" to "O"
         *
         *  time complexity = O(|V|+|E|) = O(mn)
         *  space complexity = O(1)
         */
        check_border(board);
        //2. flipping all '0' into 'x'
        //3. recover the board(flip all 's' into '0')
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                if(board[i][j] == UNSAFE)
                    board[i][j] = SAFE;
                if(board[i][j] == VISITED)
                    board[i][j] = UNSAFE;
            }
        }
    }
    void check_border(vector<vector<char>>& board){
        //check left and right
        for(int row = 0; row < board.size(); row++){
            if(board[row][0] == UNSAFE)
                explore_unsafe_region(board, row, 0);
            if(board[row][board[0].size()-1] == UNSAFE)
                explore_unsafe_region(board, row, board[0].size()-1);
        }
        //check top and down
        for(int col = 0; col < board[0].size(); col++){
            if(board[0][col] == UNSAFE)
                explore_unsafe_region(board, 0, col);
            if(board[board.size()-1][col] == UNSAFE)
                explore_unsafe_region(board, board.size()-1, col);
        }
    }
    void explore_unsafe_region(vector<vector<char>>& board, int row, int col){
        const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        //base case
        if(!is_valid(board, row, col) || board[row][col] != UNSAFE)
            return;
        //flip '0' to 'V' and investigate it's neighbors
        board[row][col] = VISITED;
        for(int dir = 0; dir < 4; dir++){
            int next_row = row + directions[dir][0];
            int next_col = col + directions[dir][1];
            explore_unsafe_region(board, next_row, next_col);
        }
    }
    bool is_valid(vector<vector<char>>& board, int row, int col){
        if(row < 0 || row >= board.size())
            return false;
        if(col < 0 || col >= board[0].size())
            return false;
        return true;
    }
};
