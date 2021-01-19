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
