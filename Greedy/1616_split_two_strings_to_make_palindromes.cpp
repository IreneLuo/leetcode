/* solution: string/greedy
 * Ex: 
 *    a: abcggrr
 *    b: abvvcba
 *  1. find the longest match of string a and b
 *     ab|cggrr
 *     abvvv|ba
 *       i j
 *  2. check if middle part is palindrome
 *     string a: cgg --> no
 *     string b: vvv ---> yes
 *  ==> we can find a palindrome = abvvvba
 *
 *  Proof: If the longest matching index is l/r, can we use i
 *         that i<=l?
 *         If str[i ~ n-i-1] is a palindrome, then str[l+1, r-1] must be
 *         a palindrome as well.
 *         So if we use the longest matching index, the middle part str[l+1, r-1]
 *         must be a palindrome
 *         12 34567      l = 2, r = 6, i = 1
 *         ab|cggrr,     a bcggrr
 *         abvvv|ba      abvvvb a
 *                        |---| palindrome
 *                      since bvvvb is a palindrome,
 *                      vvv must be a palindrome too!
 *                      Hence, we can expand the matching index to l/r
 *                      and check the middle part (vvv) is a palindrome or not
 *                      to get the answer
 *  More explaination: see HuaHua's video                  
 * time complexity = O(n)
 * space complexity = O(1)
 */
class Solution {
public:
    bool checkPalindromeFormation(string a, string b) {
        return find_longest_match(a, b) || find_longest_match(b, a);
    }
    bool find_longest_match(string& a, string& b){
        int i = 0;
        int j = a.length() - 1;
        while(a[i] == b[j]){
            ++i;
            --j;
        }
        return does_middle_palin(a, i, j) || does_middle_palin(b, i, j);
    }
    bool does_middle_palin(string& str, int left, int right){
        while(str[left] == str[right]){
            ++left;
            --right;
        }
        return left >= right;
    }
};
