class Solution {
public:
    /* solution: dynamic programming
     * We use an array to record the result of each subproblem.
     *  - arr[i] = the length the increasing subsequence that ends up at index[i]
     * ex: 
     *      we initialize each element to 1 since arr[i] is the smallest
     *      increasing subsequence.
     *
     *      [10,9,2,5,3,101,18]
     * arr    1 1 1 1 1  1  1   // default 1
     *        1 1 1 2           -> only 2>5, so 2,5 is increasing, arr[3]=1+arr[2]
     *        1 1 1 2 2  3      -> we have to get the max so the max is 1+2=3
     *        1 1 1 2 2  3  4   -> 4 is the final answer
     *      so our longest increasing subsequence is
     *      2,5,101,18 or 2,3,101,18
     *
     * note) non-decreasing != strictly increasing
     *       (because of a sequence of same value)
     *   but,strictly increasing == non-decreasing
     */
    int lengthOfLIS(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
 
        //initialize elements to 1
        vector<int> history(nums.size(), 1);
        //start to calculate the longest increasing subsequence at index i
        int maxSoFar = 1;
        for(int i = 1; i < nums.size(); i++){
            for(int j = 0; j < i; j++){
                if(nums[i] > nums[j]){
                    history[i] = max(history[i], 1 + history[j]);
                }
            }
            maxSoFar = max(maxSoFar, history[i]);
        }
        return maxSoFar;
    }
};
