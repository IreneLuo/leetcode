/* solution:
 * nums = [1,4,7,6,5,3,1]
 *           ^ we'll change here
 *                 ^ the first item > 4
 *        [1,5,7,6,4,3,1] swap 4,5
 *           ^ |--------| reverse the rest of numbers
 *        [1,5,1,3,4,6,7]
 * time complexity = O(n)
 * space complexity = O(1)
 * test case:[1,2,3], [1], [1,2]
 */
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        //step1: find the first decreasing element
        int target = nums.size() - 2;
        while(target >= 0 && nums[target] >= nums[target + 1])
            --target;
        //step2: find the first element > nums[target]
        if(target >= 0){
            int j = nums.size()-1;
            while(j >= 0 && nums[j] <= nums[target])
                --j;
            swap(nums[target], nums[j]);
        }
        //step3: reverse the elements after target
        reverse(nums.begin()+target+1, nums.end());
    }
};
