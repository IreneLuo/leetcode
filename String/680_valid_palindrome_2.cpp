class Solution {
    /* solution:
     *          i       j
     * Example: abbccbbea
     *          ||_____||
     *          |_______|
     * move i from left to right
     * move j from right to left
     * compare s[i] with s[j] until they are not match
     * then check:
     *   if we remove s[i], will s[i+1~j] be palindromic?
     *   if we remove s[j], will s[i~j-1] be palindromic?
     * For example: will bbccbb be palindromic if we remove e?
     *              will bccbbe be palindromic if we remove b?
     * if one of these checking is true, then return true
     * otherwise return false
     * 
     * time complexity = O(n)
     * space complexity = O(1)
     */
public:
    bool validPalindrome(string s) {
        int i = 0;
        int j = s.length() - 1;
        while(i < j){
            if(s[i] != s[j])
                return is_palindrome(s, i+1, j) || is_palindrome(s, i, j-1);
            i++;
            j--;
        }
        return true;
    }
    bool is_palindrome(string& s, int left, int right){
        while(left < right){
            if(s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};
