class Solution {
    /* solution 1: DP (Time limit exceeded)
     * We define a dp table that
     *  dp[i][j]: true when string[i~j] is valid
     * There are two cases:
     * Case 1:
     *      if dp[i+1][j-1]==true and s[i]== ( or * and s[j] == ) or *,
     *          dp[i][j]=true
     *      Ex: ((()))
     *           |__| 
     *             |---> this substring is true and the char before/after this substring is ( and )
     *                   so the whole string is valid too
     * Case 2:
     *      if dp[i][k]==true and dp[k+1][j]==true,
     *          dp[i][j]=true
     *      Ex: (())() 
     *             ^ ---> The substring before k and after k are all valid,
     *             k      so the whole string is valid too
     * Case 3:
     *      if i==j && s[i]==*, then dp[i][j]=true
     *
     * time complexity = O(n^3)
     * space complexity = O(n^2)
     * 
     * Solution 2: Count
     * We use min_op and max_op to track the validity for these two situations:
     *    1. min_op =  the rest of ( after handling all the characters when we treat * as a )
     *        When ch == (, ++min_op, otherwise --min_op
     *           - if min_op == 0, all the characters are pairs to pairs
     *           - if min_op > 0 -> even we treat * as ), the number of ( are still not enough to pair ) or *
     *                              return false#
     *           - if min_op < 0 -> we treat * as ), so the number of ( might not enough to pair )
     *             so we reset min_op to 0.
     *    2. max_op = the rest of ) after handling all the characters when we treat * as a (
     *        When ch!=), ++max_op, otherwise --max_op
     *           - if max_op == 0, all the characters are pairs to pairs
     *           - if max_op < 0 -> even we treat * as (, the number of ) are still not enough to pair ) or *
     *                              return false#
     *           - if max_op > 0 -> we treat * as (, so the number fo ) might not enough to pair
     * time complexity = O(n)
     * space complexity = O(1)
     *  
     *  Example:
     *      ((*))()-|--------------|
     *              v              v
     *      ( ( ) ) )  ( )           ( ( ( ) ) ( )
     *  min 1 2 1 0 -1 1 0       max 1 2 3 2 1 2 1
     *               v                       v
     *  when min = -1, we treat * as ) so the ( is not enough, we rest min to 0
     *  when max = 1, because we treat * as ( so the ) is not enough, but it's ok
     *  (because when we treat * as empty, the string will be valid)
     *  we keep modifying min and max and finally we will find that min = 0, so the ans is true
     */
public:
    bool checkValidString(string s) {
        //solution 2:
        int min_op = 0;
        int max_op = 0;
        for(char ch: s){
            if(ch == '(') ++min_op; else --min_op;
            if(ch != ')') ++max_op; else --max_op;
            if(max_op < 0) return false;
            min_op = max(0, min_op);
        }
        return min_op == 0;
        /* solution 1
        int n = s.length();
        dptbl = vector<vector<int>>(n, vector<int>(n, -1));
        return isValid(s, 0, n-1);
        */
    }
private:
    /* solution 1
    vector<vector<int>> dptbl;
    bool isValid(string& s, int i, int j){
        //if empty
        if(i > j) return true;
        //case 3
        if(i == j) return dptbl[i][j] = (s[i]=='*');
        //case 2
        if((s[i] == '(' || s[i] == '*') && (s[j] == ')' || s[j] == '*') &&
           isValid(s, i+1, j-1))
            return dptbl[i][j] = 1;
        //case 1
        for(int k = i; k < j; k++){
            if(isValid(s, i, k) && isValid(s, k+1, j))
               return dptbl[i][j] = 1;
        }
        return dptbl[i][j] = 0;
    }
    */
};
