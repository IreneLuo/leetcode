class Solution {
    /* solution: binary search
     * time complexity = O(logn)
     *  T(n) = 2 * T(n/2) + O(1) = O(logn)
     * space complexity = O(1)
     *
     * Note that there's only 1 mainly code different between first_pos() and last_pos()
     * If our goal is
     *   - find the position of a number<target and nums[mid]==target,
     *     we must go left since all the numbers before mid must smaller or equal
     *     to the nums[mid]
     *   - find the position of a number>target and nums[mid] == target,
     *     we must go right since all the numbers after mid must bigger or equal
     *     to the nums[mid]
     *
     * reference: HuaHua's Tech Road
     */
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return {first_pos(nums, target), last_pos(nums, target)};
    }
    /* int first_pos(vector<int>& nums, int target)
     *  - If target exists -> return the first position of target
     *  - If target doesn't exist:
     *      - nums[0] < target < nums[n] || target < nums[0]
     *                  -> return the position of a number who is > target
     *      - nums[n] < target
     *                  -> return the lenght of nums
     * Ex:                               [6,8,8,10] t = 8
     *         left    right    mid
     *     1.  0(6)    4        2(8)     8<=nums[mid]--> go left
     *     2.  0(6)    2(8)     1(8)     8<=nums[mid]--> go left
     *     3.  0(6)    1(8)     0(6)     8>nums[mid] --> go right
     *     4.  1(8)    1(8)              return idx 1
     *
     * Ex:                               [6,7,9,10] t = 8
     *         left    right    mid
     *     1.  0(6)    4        2(9)     8<=nums[mid]--> go left
     *     2.  0(6)    2(9)     1(7)     8>nums[mid] --> go right
     *     3.  2(9)    2(9)              return idx 2#
     *
     * Ex:                               [6,7,9,10] t = 5
     *                                    return idx 0
     *
     * Ex:                               [6,7,9,10] t = 12
     *         left    right    mid
     *     1.  0(6)    4        2(9)     12 > nums[mid] --> go right
     *     2.  3(10)   4        3(10)    12 > nums[mid] --> go right
     *     3.  4       4                 return idx 4
     *                                   
     *
     */
    int first_pos(vector<int>& nums, int target){
        int left = 0;
        int right = nums.size();//
        while(left < right){;
            int mid = left + (right - left) / 2;
            if(target <= nums[mid]){
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        if(left == nums.size() || nums[left] != target) return -1;
        return left;
    }
    /* int last_pos(vector<int>& nums, int target)
     *  - If target exists -> return the last position of target
     *  - If target doesn't exist:
     *      - nums[0] < target < nums[n] || target < nums[0]
     *                  -> return the last position of the number who is < target
     *      - nums[n] < target
     *                  -> return the lenght of nums
     *
     * Ex:                               [6,8,8,10] t = 8
     *         left    right    mid
     *     1.  0(6)    4        2(8)     8>=nums[mid]--> go right
     *     2.  3(10)   4        3(10)    8<=nums[mid]--> go left
     *     3.  3(10)   3(10)             idx3 is the first item > 8
     *                                   return 3-1=2
     *
     * Ex:                               [6,7,9,10] t = 8
     *         left    right    mid
     *     1.  0(6)    4        2(9)     8<=nums[mid]--> go left
     *     2.  0(6)    2(9)     1(7)     8>nums[mid] --> go right
     *     3.  2(9)    2(9)              idx2 is the first item > 8
     *                                   return -1 since nums[2-1] != 8
     *
     * Ex:                               [6,7,9,10] t = 5
     *                                   idx0 is the first item > 5
     *                                   return -1 since idx0-1 < 0
     *
     * Ex:                               [6,7,9,10] t = 12
     *         left    right    mid
     *     1.  0(6)    4        2(9)     12 > nums[mid] --> go right
     *     2.  3(10)   4        3(10)    12 > nums[mid] --> go right
     *     3.  4       4                 idx4 is the first position that we can place
     *                                   12, but we return -1 since idx4-1 != 12
     */
    int last_pos(vector<int>& nums, int target){
        int left = 0;
        int right = nums.size();
        while(left < right){
            int mid = left + (right - left) / 2;
            if(target < nums[mid]){
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        //left is the first element that is bigger than target
        //so we -1
        --left;
        if(left < 0 || nums[left] != target) return -1;
        return left;
    }
};
