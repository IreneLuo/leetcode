/* solution: dfs
 * dfs(123456579) = 1+dfs(23456579)
 *                   = 1+2+dfs(3456579)
 *                       = 1+2+3+dfs(456579) --> false
 *                   = 1+23+dfs(456579) --> false
 *                   = 1+234+dfs(56579) --> false
 *                = 12+dfs(3456579)
 *                = ...
 *                = 123+456+789
 * note that:
 *  F[i] might be 0 or 2^31-1 (10digits) --> i's range can be choosen from 0 to 10
 * 
 * time compelxity = O(2^n) -->  after pruning = O(10*10*n)
 *    - F[0] and F[1] can be choosen arbitrarily --> 10*10 possible choices
 *      and F[3] F[4]... will be fixed values (no backtracking)
 *
 * space complexity = O(n) / general case can be O(logn)
 *   - if input = 000000000...00, then we have to call n times of dfs()
 *     and it will create n times stack
 *   - for general case, it will be logn
 * Reference: HuaHua's video
 */
class Solution {
public:

    bool dfs(string s, int index, vector<int> &ans) {
        long next = 0;
        // set the boundary to avoid any numbers from being append with '0', e.g: '01', '02'
        int boundary = (s[index] == '0') ? 1 : 10;
        int len = s.length();

        // meet the end of string, so return true if there are more than 3 items in ans.
        if (index == len) return (ans.size() >= 3);

        for (int i = index; i < min(index+boundary, len); i++) {   
            
            next = next * 10 + (s[i]-'0');
            // if next value > INT_MAX, then we sould not push into ans
            if (next >= INT_MAX) return false;

            if (ans.size() >= 2) {
                // we cannot add two values directly to avoid signed integer overflow
                //long sum = ans.rbegin()[0] + ans.rbegin()[1];
                long sum = ans.rbegin()[0];
                sum += ans.rbegin()[1];
                if (sum > next) continue;
                else if (sum < next) break;
            }
            ans.push_back(next);
            if (dfs(s, i+1, ans)) return true;
            ans.pop_back();  
        }
        return false;
    }

    vector<int> splitIntoFibonacci(string S) {
        vector<int> ans;
        dfs(S, 0, ans);
        return ans;
    }
};
