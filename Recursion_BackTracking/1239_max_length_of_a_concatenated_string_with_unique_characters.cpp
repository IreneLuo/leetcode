class Solution {
    /* solution: dfs + bitmask
     * Thinking:
     *   1. unique characters --> so the order of subsequence doesn't matter
     *      "un"+"iq" == "iq"+"un" 
     *   2. n<=16 --> means time complexity will be 2^16
     * ==> so it's a combination problem
     * Combination:
     * We use dfs to try every possible combination of substrings in arr
     * Note:
     * Also we notice that 1 <= arr[i].length <= 26 < 32
     * so we can use a integer to record the status of a substring.
     * For each character, we can use a bit to represent it
     * ex:
     *     abcd = 0x00001111
     *     efgh = 0x11110000
     *
     * (1) abcd & efgh = 0x00000000
     *  --> use & to know if all characters are unique after combining subsequence
     *  --> if the result != 0 --> not all characters are unique
     * (2) abcd | efgh = 0x11111111
     *  --> use | to reprsent the new status of subsequence
     *
     * time complexity = O(2^n)
     * space complexity = O(n) //stack size
     *
     */
public:
    int maxLength(vector<string>& arr) {
        //transfer the strings into numbers
        vector<int> cand;
        for(string str: arr){
            int temp = 0;
            for(char c: str)
                temp |= 1<<(c-'a');
            if(__builtin_popcount(temp) != str.length()) continue;
            cand.push_back(temp);
        }
        //try strings in all possible combinations by using DFS
        //first argument: idx of string in arr
        //second argument: character mask so far
        int ans = 0;
        dfs(cand, 0, 0, ans);
        return ans;
    }
    void dfs(vector<int>& arr, int index, int mask_so_far, int& ans){
        ans = max(ans, __builtin_popcount(mask_so_far));
        //start from arr[index] and try every items after this index
        for(int i = index; i < arr.size(); i++){
            //if all characters are unique after combining
            if((mask_so_far & arr[i])== 0)
                //move to the next item in arr and update mask_so_far
                dfs(arr, i+1, mask_so_far|arr[i], ans);
        }
    }
};
