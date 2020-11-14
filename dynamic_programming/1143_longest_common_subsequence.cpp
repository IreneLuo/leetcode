class Solution {
public:
    /* solution: dynamic programming
     *
     * Main concept:
     *     lcs("abcde","ace")  //compare "e"
     *     = 1 + lcs("abcd","ac") //compare "d" and "c"
     *           = MAX(lcs("abcd", "a"), lcs("abc", "ac"))
     *                 = MAX(lcs("abc", "a"),lcs("abcd", "")),....
     *    
     * We use a table to illustrate that how can we get the longest
     * common subsequence by using dynamic programming.
     * 1. if arr[row] == arr[col], then return 1 + arr[row-1][col-1]
     * 2. if arr[row] != arr[col], then return arr[row-1][col] + arr[row][col-1]
     * ex: str1 = "abc" , str2="dac"
     *     let's look into each element in the table.
     *     arr[2][1] --> compare str "da" and str "a"
     *               a == a --> ret 1 + arr[1][0] = 1
     *     arr[3][2] --> compare str "dab" and str "ab"
     *               b == b --> ret 1 + arr[2][1] = 2
     * 
     *     col/  "" a b c
     *     row  ----------
     *      "" | 0  0 0 0
     *       d | 0  0 0 0
     *       a | 0  1 0 0 
     *       b | 0  1 2 0
     *
     * time complexity = O(mn)
     * space complexity = O(mn)
     *    m,n are length of string 1 and string 2.
     */
    int longestCommonSubsequence(string text1, string text2) {
        int rowlen = text2.size();
        int collen = text1.size();
        int cache[rowlen+1][collen+1];

        for(int row = 0; row <= rowlen; row++){
            for(int col = 0; col <= collen; col++){
                // empty string " " doesn't have any common subsequence with others
                if(row == 0 || col == 0)
                    cache[row][col] = 0;
                else if(text1[col - 1] == text2[row - 1])
                    cache[row][col] = 1 + cache[row - 1][col - 1];
                else
                    cache[row][col] = max(cache[row-1][col], cache[row][col-1]);
            }
        }
        return cache[rowlen][collen];
        
    }
};
