/* solution: 
 * The characteristic of palindrome is:
 *   at most 1 letter appears odd times
 *   other letters appear even times
 *  Example: aabaa -> a: 4, b: 1
 *           aabdddaa-> a: 4, b: 1, d:3
 *  b and d appear odd times, so we have to decrease one of them
 *  --> we let d=3-1=2 so aabddaa will be a valid palindrome
 *  time complexity = O(n)
 *  space complexity = O(1)
 */
class Solution {
public:
    int longestPalindrome(string s) {
        //count the numbers of each letters
        vector<int> count(128, 0);
        for(auto ch: s)
            count[ch]++;
        //accumulate the letters
        int ans = 0;
        for(auto c: count){
            //if the count is even
            if(c % 2 == 0) ans += c;
            //solution1: just decrease 1 if the count is odd
            else if((c % 2 == 1)) ans += (c-1);
            /* solution2:
            if the count is odd and it's the first odd
            else if((c % 2 == 1) && (ans % 2 == 0)) ans += c;
            if the count is odd but it's not the first odd
            else if((c % 2 == 1) && (ans % 2 == 1)) ans += (c-1);
            */
        }
        //solution1: if there's any letters left,
        //ans+1 to be the centre of the palindrome
        if(ans < s.length()) ans++;
        return ans;
    }
};
