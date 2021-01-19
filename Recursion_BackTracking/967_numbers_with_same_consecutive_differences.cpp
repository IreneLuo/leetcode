class Solution {
    /* solution: DFS
     * Observation:
     *    1. first digit(c) is from 1~9
     *    2. second/third digit = c+k or c-k if
     *             - c + k <= 9
     *             - c - k >= 0 (if k != 0)
     *       (if k == 0, c+k = c-k the answer will be duplicated)
     *    3. if n==1, the answer is {0,1,2,3,...,9}
     *       since each answer has only 1 digit 
     *
     * time complexity = O(2^n)
     *     - branching factor = 2 (c+k or c-k)
     *     - depth = n
     * space complexity = O(n) //DFS
     *                    O(2^n) //BFS
     *    - for BFS: all the possible node may be stored in the queue
     */
public:
    vector<int> numsSameConsecDiff(int n, int k) {
        /* solution 1:*/
        vector<int> ans;
        if(n == 1)
            ans.push_back(0);
        for(int i = 1; i <= 9; i++){
            dfs(n-1, k, i, ans);
        }
        return ans;
        /* solution 2:
        return bfs(n,k);
        */
    }
    void dfs(int length, int diff, int num, vector<int>& ans){
        if(length == 0){
            ans.push_back(num);
            return;
        }
        int d = num % 10;
        if((d + diff) <= 9) 
           dfs(length-1, diff, num * 10 + (d+diff), ans);
        if((d-diff) >= 0 && diff != 0)
            dfs(length-1, diff, num * 10 + (d-diff), ans);
    }
    /* Example: n = 3, k = 7
     * dq = {1,2,3,4,5,6,7,8,9}
     *   n   size   dq
     *   2    9     {2,3,4,5,6,7,8,9, 18}
     *        8     {3,4,5,6,7,8,9, 18, 29}
     *        7     {4,5,6,7,8,9, 18, 29}
     *        6     {5,6,7,8,9, 18, 29}
     *        5     {6,7,8,9, 18, 29}
     *        4     {7,8,9, 18, 29}
     *        3     {8,9, 18, 29, 70}
     *        2     {9, 18, 29, 70, 81}
     *        1     {18, 29, 70, 81, 92}
     *   1    5     {29, 70, 81, 92, 181}
     *        4     {70, 81, 92, 181, 292}
     *        3     {81, 92, 181, 292, 707}
     *        2     {92, 181, 292, 707, 818}
     *        1     {181, 292, 707, 818, 929} ##answer
     *   0 end
     *
     */
    vector<int> bfs(int n, int k){
        deque<int> dq{1,2,3,4,5,6,7,8,9};
        if(n == 1)
            dq.push_front(0);
        //the number in the dq has take 1 digit there are n-1 digits left
        while(--n){
            int size = dq.size();
            while(size){
                size--;
                int num = dq.front();
                dq.pop_front();
                int d = num % 10;
                if((d + k) <= 9)
                    dq.push_back(num * 10 + (d + k));
                if((d - k) >= 0 && k != 0)
                    dq.push_back(num * 10 + (d - k));
            }
        }
        return vector<int>(dq.cbegin(), dq.cend());
    }
};
