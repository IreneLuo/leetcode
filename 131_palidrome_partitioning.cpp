class Solution {
public:
    /* solution:
     * branch factor = 2 (choose this divider or not)
     * dividor = n - 1
     *               a|a|b     --> n = 3, divider = 3-1 = 2
     *              /     \    --> choose the first divider or not
     *           a|ab     aa|b
     *           /  \     /  \ --> choose the second divider or not
     *        a|a|b a|ab aa|b aab --> 4 results = branch factor^dividor= 2^2
     */
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        _partition(0, {}, s, ans);
        return ans;
    }
    // to check if string is palindrome or not
    bool isPalindrome(string s){
        int left = 0;
        int right = s.size() - 1;
        while(left < right){
            if(s[left]!=s[right])
                return false;
            left++;
            right--;
        }
        return true;
    }
    void _partition(int start, vector<string> cand,
                    string& input, vector<vector<string>>& ans){
        if(start == input.size()){
            ans.push_back(cand);
            return;
        }
        // branching factor = n - 1
        // it means we need to decide n-1 dividers to seperate the input
        for(int i = start; i < input.size(); i++){
            // i - start + 1 is the length of substring
            string snippet = input.substr(start, i - start + 1);
            if(isPalindrome(snippet)){
                cand.push_back(snippet);
                _partition(i+1, cand, input, ans);
                cand.pop_back();
            }
        }
    }
};
