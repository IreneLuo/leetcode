class Solution {
public:
    /* solution: binary search
     * We use the value of middle point and the left/right point to
     * know that which part(left or right) is the ascending part.
     * If target falls in the ascending part, then we go into that part
     * Otherwise we go to another part to check the answer.
     * Ex:               [4,5,6,7,0,1,2], target = 0
     *                    |-----||-----|
     *                           |--|--|
     *
     *          left, right, mid num ascending  target in ascending part?  go to
     *   step1:  0     6      3   7   left          no                     right
     *   step2:  4     6      5   1   left          yes                    left
     *   step3:  4     4      4   0--> anwer
     *
     *  time complexity = O(logn)
     *  space complexity = O(1)
     *      
     */
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while(left <= right){
            int mid = left + (right - left) / 2;
            cout<<" left, right, mid = "<<left<<", "<<right<<", "<<mid<<endl;
            if(nums[mid] == target) return mid;
            /* edge case: [3,1] target=1
             * if we use :
             *    - if (nums[left] < nums[mid]), it will recognize the right part
             *      as ascending array, but actually
             *      the right part [1] is > left part [3]
             *      so the right part is rotated part--> and this will lead to
             *      an unexpected answer
             *    - if (nums[left] <= nums[mid]), since mid = left = idx 0
             *      so the left part will be recodnoed as an ascending array.
             *      Then we'll check if target falls between nums[left] and nums[mid].
             *      In this case, it doesn't fall in the left part, so left boundary
             *      will be update to mid+1 and return a correct anwer.  
             */
            //left part: ascending / right part: rotated
            if(nums[left] <= nums[mid]){
                //if target falls in left part, update the right boundary
                if(nums[left] <= target && target < nums[mid])
                    right = mid - 1;
                //if target falls in right part, update the left boundary
                else
                    left = mid + 1;
            //left part: rotated / right part: ascending
            }else{
                //if target falls in right part, update the left boundary
                if(nums[mid] < target && target <= nums[right])
                    left = mid + 1;
                //if target falls in left part, update the right boundary
                else
                    right = mid - 1;
            }
        }
        return -1;
    }
};
