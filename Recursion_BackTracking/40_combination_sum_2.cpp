class Solution {
    /* solution: DFS
     * Choice: any element in candidates
     * Constraints: no dup combinations ex: {1,7}{7,1} are the same
     * Goal: sum == target
     * 
     * How to remove duplicate:
     *   1. use set --> use here
     *   2. disallow same number in the same path
     * Note
     *  1. we sort the candidates before combine()
     *  2. we use set to avoid duplicate
     *  3. we use accumulate to avoid time limit exceeded on edge cases
     *
     *  time complexity = O(2^n)
     *    - 2^n for combinations
     *    - nlogn for sorting (smaller than 2^n)
     *  space complexity = target * n
     */
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        set<vector<int>> ans;
        sort(candidates.begin(), candidates.end());
        /* Edge case
         * [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
         * 27
         */
        if(accumulate(candidates.begin(), candidates.end(), 0) < target)
            return {};
 
        combine(candidates, target, 0, {}, ans);
        return vector<vector<int>>(ans.begin(), ans.end());
    }
    void combine(vector<int>& candidates, int remain, int start,
                vector<int> cand, set<vector<int>>& ans){
        if(remain == 0){
            ans.insert(cand);
            return;
        }
        //i starts from "start" to avoid a same element being used twice
        for(int i = start; i < candidates.size(); i++){
            int num = candidates[i];
            //candiates had been sorted so we skip the rest of elements if
            //remain - current element < 0
            if(remain-num < 0)
                continue;
            cand.push_back(num);
            combine(candidates, remain-num, i+1, cand, ans);
            cand.pop_back();
        }
    }
};
