class Solution {
public:
    /* solution: dynamic programming
     * we create 2 vectors
     *  prefix[i]: the sum of nums[0] to nums[i-1]
     *  suffix[i]: the sum of nums[i+1] to nums[n-1]
     *  ==> if prefix[i] == suffix[i], then i is the pivot index
     *
     *  ex: nums = [1,  7,  3,   6,  5,  6]
     *    prefix = [0,  1,  8,  11, 17, 22]
     *    suffix = [27, 20, 17, 11,  6,  0]
     *    
     *    1. prefix[0] & suffix[n-1] initialize to 0
     *    2. prefix[i] = prefix[i-1] + nums[i-1]
     *    3. suffix[i] = suffix[i+1] + nums[i+1]
     *
     * time complexity = O(n)
     * space complexity = O(n)
     */
    int pivotIndex(vector<int>& nums) {
        if(nums.empty())
            return -1;
        int n = nums.size();
        vector<int> prefix(n, 0);
        vector<int> suffix(n, 0);
        for(int i = 1; i < n; i++)
            prefix[i] = prefix[i-1] + nums[i-1];
        for(int i = n-2; i >= 0; i--)
            suffix[i] = suffix[i+1] + nums[i+1];
        for(int i = 0; i < n; i++){
            if(prefix[i] == suffix[i])
                return i;
        }
        return -1;
    }
};
