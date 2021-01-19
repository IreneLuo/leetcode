class Solution {
    /* solution: DP
     * use swap[i]/keep[i] to denotes the min swap that makes A and B
     * strictly increasing.
     * Rules:
     *    - if A[i] > A[i-1] && B[i] > B[i-1]
     *       1. keep (A[i],B[i]) (A[i-1], B[i-1])      --> keep[i] = keep[i-1]
     *       2. swap both (A[i],B[i]) (A[i-1], B[i-1]) --> swap[i] = swap[i-1] + 1
     *    - if B[i] > A[i-1] && A[i] > B[i-1]
     *       1. swap (A[i],B[i]) only      --> swap[i] = (keep[i-1] + 1, swap[i])
     *       2. swap (A[i-1], B[i-1]) only --> keep[i] = (swap[i-1], keep[i])
     *
     *  Ex: A = [3,5]
     *      B = [2,3]
     *      there are 4 cases
     *      1. keep i and i-1      2. swap both i and i-1
     *           [3,5]                   [2,3]
     *           [2,3]                   [3,5]
     *      3. keep i, swap i-1    4. keep i-1, swap i
     *           [2,5]                   [2,5]
     *           [3,3]                   [3,3]
     *
     * time complexity = O(n)
     * space complexity = O(n)
     *
     * Note that for DFS solution, see HuaHua's video
     * (time complexity = 2^n might occur time limit exceeded)
     */
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> keep(n, INT_MAX);
        vector<int> swap(n, INT_MAX);
        keep[0] = 0;
        swap[0] = 1;
        for(int i = 1; i < n; i++){
            if(A[i] > A[i-1] && B[i] > B[i-1]){
                keep[i] = keep[i-1];
                swap[i] = swap[i-1] + 1;
            }
            if(B[i] > A[i-1] && A[i] > B[i-1]){
                keep[i] = min(keep[i], swap[i-1]);
                swap[i] = min(swap[i], keep[i-1] + 1);
            }
        }
        return min(keep.back(), swap.back());
    }
};
