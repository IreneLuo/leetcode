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
    /* solution 1: dp
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
    */
        /* solution 2: divide and conquer */
        return max_sum_subarray(nums, 0, nums.size()-1);
    }
    /* Divide and Conquer
     * 1. find the max sum of left subarray
     * 2. find the max sum of right subarray
     * 3. find the max sum in left+right subarray(crossing middle)
     * 4. compare 1,2,3 find a max one
     * time complexity = O(nlogn)
     * space complexity = O(1)
     * reference: https://www.codesdope.com/blog/article/maximum-subarray-sum-using-divide-and-conquer/
     */
    int max_sum_subarray(vector<int>& nums, int left, int right){
        if(left == right)
            return nums[left];
        int mid = left + (right-left)/2;
        int max_sum_left = max_sum_subarray(nums, left, mid);
        int max_sum_right = max_sum_subarray(nums, mid+1, right);
        int max_sum_crossing = max_sum_crossing_subarray(nums, left, mid, right);
        return max(max(max_sum_left, max_sum_right), max_sum_crossing);
    }
    int max_sum_crossing_subarray(vector<int>& nums, int left, int mid, int right){
        int sum = 0;
        int max_left = INT_MIN;
        int max_right = INT_MIN;
        //from left to mid, accumulate the numbers and find max sum
        for(int i = mid; i >= left; i--){
            sum += nums[i];
            if(sum > max_left)
                max_left = sum;
        }
        sum = 0;
        //from mid+1 to right, accumulate the numbers and find max sum
        for(int i = mid+1; i <= right; i++){
            sum += nums[i];
            if(sum > max_right)
                max_right = sum;
        }
        return max_left + max_right;
    }
};
