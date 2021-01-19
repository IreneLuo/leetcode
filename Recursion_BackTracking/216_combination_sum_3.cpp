class Solution {
    /* Solution 1: Recursion(DFS+memorization)
     * Choice: each time choose 1~9, total k times
     * Constraints: no duplicate combination
     * Goal: sum == n
     *
     * Ex: k = 3, n = 7
     *   i   cand    remain
     *   1   1         6
     *   2   12        4
     *    3   123       1  -> cand.size==k, return
     *    4   124       0  -> push {1,2,4}, pop 4
     *    5   125       -1 -> remain < 0, break
     *   3   13        3
     *   4   134       -1  -> remain < 0, break
     *   ..  ...      ...
     *
     *   time complexity = C(9,k) = 9!/k!/(9-k)!
     *   space complexity = O(k + k* num of ans)
     *     - stack depth = k
     *     - ans = len * num of ans
     *   
     * Solution 2: bitmask (slower than sol1)
     * Consider each possible combination as a bitmask
     * so we have 2^9 possible combination
     *  (bit[i] = number i+1)
     *    000000001 = 1
     *    000000010 = 2
     *    000000011 = 1,2
     *       ....
     *    111111111 = 1,2,3,4,5,6,7,8,9
     *  time complexity = 2^9 * 9
     *  space complexity = O(k + k* num of ans)
     */
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        /* solution 1 */
        combination(1, k, n, {}, ans);
        /* solution 2
        for(int pattern = 1; pattern < (1<<9); pattern++){
            vector<int> cand;
            int remain = n;
            for(int i = 1; i <= 9; i++){
                if(pattern & 1<<(i-1)){
                    remain -= i;
                    if(remain < 0)
                        break;
                    cand.push_back(i);
                }
            }
            if(remain == 0 && cand.size() == k)
                ans.push_back(cand);
        }*/
        return ans;
    }
    void combination(int idx, int total, int remain, vector<int> cand, vector<vector<int>>& ans){
        if(cand.size() == total && remain == 0){
            ans.push_back(cand);
            return;
        }
        if(remain < 0)
            return;
        if(cand.size() == total)
            return;

        for(int i = idx; i <= 9; i++){
            cand.push_back(i);
            //optimization: if remain-i < 0, skip the rest of i
            if(remain - i < 0)
                break;
            combination(i+1, total, remain-i, cand, ans);
            cand.pop_back();
        }
    }
};
