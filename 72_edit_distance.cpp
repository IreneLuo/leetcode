class Solution {
public:
    /* solution: dynamic programming
     *
     *   if s[i]!=s[j], arr(i, j) = min(1+d, 1+I, 1+R)    _Replace_|__Delete__
     *   else arr(i, j) = 0 + R(the case except i,j)
     *    s2 " " r  o  s                                  _Insert__|__CurrPos_
     *    s1|------------
     *   " "| 0  1  2  3 --> [1]
     *    h | 1  1  2  3  
     *    o | 2  2  1  2
     *    r | 3  2  2  2
     *    s | 4  3  3  2
     *    e | 5  4  4  3 --> [3]
     *        |------------> [2]
     *  
     *  For row 0 and column 0, see [1][2]
     *  [1]: " " -> r needs 1 op, " " -> ro needs 2 ops, " " -> ros needs 3 ops
     *  [2]: h -> " " needs 1 op, ho -> " " needs 2 ops ...etc
     *
     *  For the rest of elements
     *  [3]: for hors"e" -> ro"s"
     *   1) if we choose delete "e", then the word will be hors -> ros, so we reference [row][col-1]
     *    --> cost(delete) = 1 (delete) + 2([row][col-1]) = 3
     *   2) if we choose insert "s", then the word will be horses -> ros, so now we have to
     *  check "e" with "o", so we reference [row-1][col]
     *    --> coss(insert) = 1 (insert) + 4 = 5
     *   3) if we choose replace "e", then the word will be horss->ros, so now we have to
     *  check "s" with "o", so we reference [row-1][col-1]
     *    --> cost(replace) = 1 (replace) + 3 = 4
     *   so the min(3,5,4) = 3 --> we choose delete
     */
    int minDistance(string word1, string word2) {
        int history[word1.size()+1][word2.size()+1];
        for(int row = 0; row <= word1.size(); row++){
            for(int col = 0; col <= word2.size(); col++){
                if(row == 0){
                    history[row][col] = col; 
                }else if(col == 0){
                    history[row][col] = row;
                }else if(word1[row-1] == word2[col-1]){
                    history[row][col] = history[row-1][col-1];
                }else{
                    int deleteCost = 1 + history[row][col-1];
                    int insertCost = 1 + history[row-1][col];
                    int replaceCost = 1 + history[row-1][col-1];
                    history[row][col] = min(deleteCost, min(insertCost, replaceCost));
                }
            }
        }
        return history[word1.size()][word2.size()];
    }
};
