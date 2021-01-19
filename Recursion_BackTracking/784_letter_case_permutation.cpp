class Solution {
public:
    /* solution: recursion
     * choice: lowercase->lowercase
     *         lowercase->uppercase
     * constraint: transform the str[i] if it is an alphbet
     * goal: i == string length
     *
     * time complexity = O(2^n)
     *   branching factor = 2
     *   depth = n (lenght of the string)
     * space complexity = O(1)
     * 
     * ex:    a1b2
     *     /       \
     *   a1b2     A1b2     i = 0
     *    |         |
     *   a1b2     A1b2     i = 1
     *   / \       / \
     * a1b2 a1B2 A1b2 A1B2 i = 2
     *  |    |    |    |   
     * a1b2 a1B2 A1b2 A1B2 i = 3
     *
     */
    vector<string> letterCasePermutation(string S) {
        vector<string> ans;
        //start from idx 0
        permute(S, 0, ans);
        return ans;
    }
    void permute(string& str, int idx, vector<string>& ans){
        if(idx == str.length()){
            ans.push_back(str);
            return;
        }
        //phase 1: no matter str[i] is digit or alphabet, go to the deepest node
        permute(str, idx+1, ans);
        //phase 2: if str[i] is an anphabet, transform it to uppercase
        if(isalpha(str[idx])){
            str[idx] ^= (1<<5);
            permute(str, idx+1, ans);
            //reverse it back to lowercase
            str[idx] ^= (1<<5);
        }
        return;
    }
};
