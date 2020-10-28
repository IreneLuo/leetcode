class Solution {
public:
    /* solution: dynamic programming
     * Naive solution needs cubic/quadratic time(more details in "back to back SWE")
     * 1. we use two variables to deal with the max contiguous subarray sum
     *    - maxSoFar = the max summary seen so far
     *    - maxEndingHere = the max summary ending at here
     *                    = max(a, b)
     *         - a = itself(if subarray starts and ends at itself)
     *         - b = previous maxEndingHere + itself (if subarray starts from previous elements and ends at itself)
     *
     * 2. by default, we set
     *    maxSoFar = nums[0] ---> the max sum so far is the first element 
     *    maxEndingHere = [0] --> the max sum ending from element 0 is itself
     * 3. we investigate the items(from 1 onwards) in input to retrieve the best sum
     *
     * time complexity = O(n)
     * space complexity = O(1)
     *
     * ex:
     *          data = [-2,1,-3,4,-1,2,1,-5,4]
     * maxEndingHere =  -2 1 -2 4  3 5 6  1 5 
     *                     |  | |--max(-2+4,4)
     *                     |  |--max(1+(-3),-3)
     *                    max(-2+1,1)
     *      maxSoFar =  -2 1  1 4  4 5 6  6 6 --> the answer
     */
    int maxSubArray(vector<int>& nums) {
        int maxSoFar = nums[0];
        int maxEndingHere = nums[0];
        //we are inspecting the item[i]
        for(int i = 1; i < nums.size(); i++){
            //everytime we ask that "what is the max summary ending at element i?"
            maxEndingHere = max(nums[i], maxEndingHere + nums[i]);
            //compare with maxSoFar
            maxSoFar = max(maxSoFar, maxEndingHere);
        }
        return maxSoFar;
    }
};
