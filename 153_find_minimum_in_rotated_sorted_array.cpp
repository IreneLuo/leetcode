class Solution {
public:
    /* solution: binary search
     * 1. set the left and right idx
     * 2. find the middle
     * 3. if middle > right, set left = middle + 1 (it means the smallest value is located at right section)
     *    otherwise, set right = middle (it means the smallest value could be middle or is located at left section)
     * 4. keep finding middle until left equals to right
     *
     * time complexity: O(logn)
     * space complexity: O(1)
     */
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        int middle;
        while(left < right){
            middle = left + (right - left) / 2; //to avoid overflow
            if(nums[middle] > nums[right])
                left = middle + 1;
            else
                right = middle;
        }
        //cout << "left, right, middle = "<<left<<", "<<right<<", "<<middle<<endl;
        // do not return nums[middle]
        // ex: [3,4,5,1,2] --> left = right = middle = 3      (odd case)
        // ex: [4,3,2,1] --> left = right = 3, but middle = 2 (even case)
        return (nums.size() == 0) ? -1 : nums[left];
    }
};
