/* solution: dp/string
 * 1. Brute Force solution: O(n^3)
 *        1. find all the substring O(n^2)
 *        2. check if each substring is palindromic or not O(n)
 * 2. DP solution:
 *        1. assume that we are at middle point of a string
 *           and we get a substring s[i] if len(str)=odd
 *                                  s[i~i+1] if len(str) is even
 *        2. then expand the substring from middle to the left / to the right
 *           until string[left] isn't equal to string[right]
 *                    fcbabcg
 *                       ij(all points to a) 
 *                      i_j  
 *                     i___j
 *                    i     j
 *           For this example, i,j will stop at 0 and 6
 *           so the len = j-i-1=5 (-1 because i and j are out of palindromic boundary)
 *    Implicit DP concept:
 *        if dp[i+1][j-1] = true and s[i]==s[j] , then dp[i][j]=true
 *        (dp[i][j] = true means string [i~j] is palindromic)
 *
 *   time complexity = O(n^2) / best case = O(n)
 *     - O(n) indices and O(n) for each step
 *   space complexity = O(1)
 *                       
 * Reference: HuaHua's video
 */
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        int len = 0;
        int start = 0;
        for(int i = 0; i < n; i++){
            int curr_len = max(get_longest_substring(s, i, i),
                               get_longest_substring(s, i, i+1));
            //if the latest length > len, we update len and start
            //(len and start are the basic info to retrieve the substring)
            if(curr_len > len){
                len = curr_len;
                /* start = mid - half of len
                 * Ex: aaabaaa --> start=3-(7-1)/2=0 (mid=i=3, len=7)
                 *     aaaaaa --> start =2-(6-1)/2=0 (mid=i=2, len=6)
                 */
                start = i - (len-1) / 2;
            }
        }
        return s.substr(start, len);
    }
    int get_longest_substring(string& s, int left, int right){
        //boundary check must do first, if out of boundary, then
        //it won't access string and lead to an unexpected error
        while(left >= 0 && right < s.length() && s[left] == s[right]){
            --left;
            ++right;
        }
        return right - left - 1;
    }
};
