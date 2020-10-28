class Solution {
public:
    /* solution:
     * choice: k positions, each position can choose a number from 1 to n
     * constraints: each positions' number is different
     * goal: finish choosing k numbers
     */
    void _combine(int start, int count, int n, int k, vector<int>cand, vector<vector<int>>& ans) {
        if(count == k){
            ans.push_back(cand);
            return;
        }
        // time complexity = O(n * (n choose k))
        // space complexity = O(n)
        //  - in this function, a for loop takes O(n) and an answer push back takes O(k), so total O(n)
        //  - how many times of function do we call? i.e (n choose k) = n!/(k!(n-k)!)
        //    -> n choose k means: if I choose size k items from a pool of size n, how many of this length-k sets
        //       are unique can I choose from an overarching n?
        //    -> lowerbound of n choose k (Omega(n choose k))

        // if there's no more selections of i that we can choose, then stop
        // we don't need to waste time on it
        // ex: n=4, k=3
        /*                 [1,2,3,4]
         *           /        /      \    \
         *         1__       2__      3__  4__
         *        / |  \     / \       |    |
         *     12_ 13_ 14_ 23_ 24_   34_   x
         *     / \   |   |   |   |     | 
         *  123 124 134  x  234  x     x
         *  
         *  in order to save time on cases like x
         *  we do a spaceleft check in our for loop
         */
        int spaceleft = k - count;
        for(int i=start; i<=n && spaceleft <= (n-i+1); i++){ 
                cand.push_back(i);
                count++;
                _combine(i+1, count, n, k, cand, ans);
                count--;
                cand.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        _combine(1, 0, n, k, {}, ans);
        return ans;
    }
};
