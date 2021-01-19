class Solution {
    /* solution: recursion + memorization
     * 1. iterate the board
     * 2. find a char == word[0]
     * 3. then visit this char's neighbors to check word[1-n]
     * time complexity = O(mn + 4^wordlength)
     *  - (dfs) branching factor: 4
     *  - (dfs) depth: wordlength
     *  - main func: 2 for loops: mn
     * space complexity = O(wordlength)
     */
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty())
            return false;
        int row = board.size();
        int col = board[0].size();
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                if(dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }
    bool dfs(vector<vector<char>>& board, string word, int x, int y, int wordidx){
        if(x < 0 || x == board.size() || y < 0 || y == board[0].size() ||
          board[x][y] != word[wordidx])
            return false;
        /*  we cannot use (wordidx == word.length())
         *  use (wordidx == word.length() - 1) to find
         *  the last char of the word.
         */
        if(wordidx == word.length() - 1)
            return true;
        /* tricks: set board[x][y] to 0
         * to avoid visiting this position again in its dfs() calls
         */
        char temp = board[x][y];
        board[x][y] = 0;
        bool ans = dfs(board, word, x-1, y, wordidx+1)||
                   dfs(board, word, x+1, y, wordidx+1)||
                   dfs(board, word, x, y-1, wordidx+1)||
                   dfs(board, word, x, y+1, wordidx+1);
        /* recover the board */
        board[x][y] = temp;
        return ans;
    }
};
