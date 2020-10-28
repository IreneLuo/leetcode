class Solution {
    /* soltuion: recursive call
     * 1. we choose one number at a time, and use new target(= target - num) to try a number recursively
     *    until target <= 0
     * 2. note that we have to return unique combinations, so we cannot return the answer like this: aab and aba
     *    the key point to avoid this is using a proper idx in each recursive call
     *
     * time complexity = O(N^K) --> loosely bounded
     *   - branching factor = N (size of candidates)
     *   - depth = K
     * space complexity = O(k), k = target/smallest num = level of the tree
     * Let's see an example:
     *                                                                          8     
     *                                                [2]                      [3]            [5] ==> candidate
     *                                                 |------------------------|--------------|
     *                                                 6                        5              3  ==> target = target - candidate
     *                                 [2]            [3]           [5]    [3]     [5]        [5]  |
     *                                  |--------------|-------------|      |-------|          |   |--> we must save history[3] w/[3] and w/o [3]
     *                                  4              3 =====       1      2       0         -2   |    because in this tree, we can clearly see that
     *                        [2]      [3]     [5]  [3] [5]  |      [5]  [3] [5]    v              |    there's two kind of situation for target=3
     *                         |--------|-------|    |---|   |       |    |---|                    |    one is: only can use [5] for the next recursive call
     *                         2        1       -1   0  -2   |      -4   -1  -3                    |    another one: can use [3][5] for the next recursive call
     *                    [2] [3] [5] [3] [5]        v       |======================================    so we must use a two-dimentional table.
     *                     |---|---|   |---|                                                            For implementation, see "Score Combinations" in
     *                     0  -1  -3  -2  -4                                                            "Back to Back SWE"
     *                     v
     *                 [2,2,2,2]                   [2,3,3]                        [3,5]              
     *                 => when a recursive function finish, we pop out "2"
     *                    so now the list will be [2,2,2] and then we try the next number 3 (we go upward to the (logn - 1) level)
     */
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        //remeber to sort the input
        sort(candidates.begin(), candidates.end());
        //start our recursive call
        try_one_number(0, candidates, target, {}, ans);
        return ans;
    }
    void try_one_number(int idxOfCand, vector<int>& candidates, int target, vector<int> combination, vector<vector<int>>& ans){
        //target is 0 which means that we the items in vector combination is our answer
        if(target == 0){
            ans.push_back(combination);
            return;
        }
        //everytime we start from idxOfCand and we only allow our subroutine start from idxOfCand to avoid duplicate items
        for(int i = idxOfCand; i < candidates.size(); i++){
            int targetLeft = target - candidates[i];
            //once we find that targetLeft is negative, we can break the for loop since we've already sorted the input
            //that means the items after candidates[i] will also make targetLeft become negative
            if(targetLeft < 0)
                break;
            combination.push_back(candidates[i]);
            try_one_number(i, candidates, targetLeft, combination, ans);
            //we still need to find other items so remember to pop out the last item in the combination
            combination.pop_back();
        }
    }
};
