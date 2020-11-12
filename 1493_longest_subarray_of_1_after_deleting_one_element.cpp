class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        /*  solution: dp
         *  time complexity = O(n)
         *  space complexity = O(n)
	 *  for more solution see huahua's video
         *
         *  Method:
         *   1. we use a counter to accumulate the length of subarray
         *   2. counter = 1 if nums[0] = 1
         *      counter = 0 if nums[0] = 0
         *   3  iterate over the nums
         *      - if nums[i] == 1, counter++
         *      - if nums[i] == 0, save the counter to the "history" table
         *      - if we finish investigating all the elements and the last element is not 0,
         *        save the counter to the history table
         *   4. get the longest length by calculating the values in the table
         *      Note that for the first two values, we won't have to do this operations
         *        length = history[i] - history[i-2]
         *
         *  Case 1 (starts with 0)
         *  Ex:         input = [0,1,1,1,0,1,1,0,1]
         *              count =  0 1 2 3 3 4 5 5 6
         *            history =  0       3     5 6----> the length of subarray before this element is history[3] - history[1] = 3
         *                       |       |     |------> the length of subarray before this element is history[2] - history[0] = 5
         *                       |       |------------> the subarray before this element is history[1] = 3
         *                       |--------------------> the subarray before this element is history[0] = 0
         *           ==> so the longest one is 5
         *
         *  Case 2: with 2 zeros
         *  Ex:         input = [1,1,0,0,1,1,1,0,1]
         *              count =  1 2 2 2 3 4 5 5 6
         *            history =      2 2       5 6 
         *                           | |       |     |------> the longest subarray before this element is history[3] - history[1] = 4
         *                           | |       |------------> the longest subarray before this element is history[2] - history[0] = 3
         *                           |-|------------------> the longest subarray before this element is history[0] = 2, history[1]= 2
         *           ==> so the longest one is 4
         */
        int count = (nums[0] & 1) ? 1 : 0;
        int i = 1;
        vector<int> history;
        while(i < nums.size()){
            if(nums[i] == 1){
                count++;i++;
            }else if(nums[i] == 0){
                history.push_back(count);i++;
            }
        }

        //if the last element is not 0, we have to push the count into the vector
        if(nums[nums.size()-1] == 1)
                history.push_back(count);

        //edge case: no 0 in nums like [1,1,1]
        //return the count - 1 since we must delete one element
        if(history.size() == 1)
            return history.back() - 1;
        //if we only have 2 elements in the vector, return the max one
        int ans = max(history[0], history[1]);
        if(history.size() == 2)
            return ans;
        
        for(int i = 2; i < history.size(); i++){
            ans = max(ans, history[i]-history[i-2]);
        }
        return ans;
    }
};
