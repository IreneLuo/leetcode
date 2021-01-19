class Solution {
    /* solution: binary search
     * time complexity:O(logn)
     * space complexity:O(1)
     * 
     * Main idea:
     * The idx of each pair of numbers will be <even, odd>
     * Once the single element appears, it will break the rules
     * Step:
     * 1. choose a middle number
     * 2. get its partner
     *    if middle is even, partner = middle +1
     *    if middle is odd, partner = middle -1
     *    ==> overall, partner = middle ^ 1 (reverse bit[0])
     * 3. if middle number isn't as same as its partner
     *    there must exist a single breaker who breaks the rules
     *    --> go to the left part and check again
     * 4. if middle number is as same as its partner
     *    we haven't find that single breaker
     *    --> go to the right part and check again
     * 5. the operation will stop if left >= right
     *
     * ex: [1,1,2,3,3,4,4]
     *  l  r  m  p
     *  0  7  3  2  nums[3]!=nums[2] --> go left
     *  0  3  1  0  nums[1]==nums[0] --> go right
     *  2  3  2  3  nums[2]!=nums[3] --> go left
     *  2  2        return 2
     */
public:
    int singleNonDuplicate(vector<int>& nums) {
        if(nums.size() == 1)
            return nums.back();
        int l = 0;
        int r = nums.size();
        while(l < r){
            int mid = l + (r-l)/2;
            int partner = mid ^ 1;
            if(nums[mid] == nums[partner])
                l = mid + 1;
            else
                r = mid;
        }
        return nums[l];
    }
};
