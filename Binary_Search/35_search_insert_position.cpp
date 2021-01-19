class Solution {
    /* solution: binary search
     * In each iteration:
     *    - find a middle index
     *    - if target == middle value --> we find the answer!
     *    - if target < middle value --> go to the left partition and repeat
     *    - if target > middle value --> go to the right partition and repeat
     * time complexity = O(logn)
     *     T(n) = T(n/2) + O(1) = O(logn)
     * space complexity = O(logn) //depth of function stacks
     * For another method, see HuaHua's article
     */
public:
    int searchInsert(vector<int>& nums, int target) {
        return binary_search(nums, target, 0, nums.size()-1);
    }
    int binary_search(vector<int>& nums, int target, int left, int right){
        /* if left == right --> only have 1 candidate to compare nums[x]
         * so if target <= nums[x], return left, else return right+1
         * Ex: [1] target = 0 --> 0 < 1, so return idx 0
         *     [1] target = 1 --> 1==1, so retrun idx 0
         *     [1] target = 5 --> 1 < 5, so return idx 1
         */
        if(left == right) return (target <= nums[left]) ? left : right+1;

        int mid = left + (right - left) / 2;
        if(nums[mid] == target) return mid;

        //if target < nums[mid], we must assign right to mid
        //because if nums[mid-1] < target < nums[mid]
        //the insertion point will be at mid
        if(target < nums[mid])
            return binary_search(nums, target, left, mid);
        else
            return binary_search(nums, target, mid + 1, right);
    }
};
