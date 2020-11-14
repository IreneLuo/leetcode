class Solution {
public:
    /* solution 1: dynamic programming
     * Let's define:
     *   prefix(k) as the product of the first k element in the array.
     *   suffix(k) as the product of the last k element in the array.
     *   --> prefix(k) = prefix(k-1) * array[k]
     *   --> suffix(k) = array[k] * suffix(k+1)
     * Base cases:
     *   prefix(0) = array[0]
     *   suffix(n) = array[n] //n is the last element
     * Method:
     * 1. find out all the prefix() and suffix()
     * 2. use them to get the answer
     *    for answer[k] = prefix(k-1) * suffix(k+1)
     *
     * time complexity = O(n)
     * space complexity = O(n)
     * 
     * p.s) we can store the prefix into the answer
     *      and suffix can be known on the fly when we calculate the anser
     *      this approach can save our space to O(1)
     *      see solution on leetcode
     */
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> prefix(nums.size(), 0);
        prefix[0] = nums[0];
        for(int i = 1; i < nums.size(); i++){
            prefix[i] = prefix[i - 1] * nums[i];
        }
        vector<int> suffix(nums.size(), 0);
        suffix[nums.size()-1] = nums[nums.size()-1];
        for(int i = nums.size() - 2; i >= 0; i--){
            suffix[i] = nums[i] * suffix[i + 1];
        }
        vector<int> ans(nums.size(), 1);
        for(int i = 0; i < nums.size(); i++){
            // if 0 < i < n-1 then ans = prefix * suffix
            // if i == 0 then ans = suffix
            // if i == n-1 then ans = prefix
            if(i != 0)
                ans[i] = prefix[i-1];
            if(i != nums.size() - 1)
                ans[i] *= suffix[i+1];
        }
        return ans;

        /* solution 2: math
         * (Input data may be negative or zero, so we have to deal with those corner cases.)
         * We can use math formula:
         *    log(a*b) = log(a) + log(b)
         *    log(a/b) = log(a) - log(b)
         *    --> log(sum/arr[k]) = (log(arr[1])+..+log(arr[n])) - log(arr[k])
         *
         * time complexity: O(n)
         * space complexity: O(1)
         */
        /*
         double logsum = 0;
         int zerocnt = 0;
         int negcnt = 0;
         vector<int> ans(nums.size(), 1);
         for(int i = 0; i < nums.size(); i++){
             // if nums[i] is negative, negcnt++
             if(nums[i] < 0)
                 negcnt++;
            // if nums[i] is 0, zerocnt++ and skip this number
             if(nums[i] == 0){
                 zerocnt++;
                 continue;
            //normal case: get log(arr[1])+..+log(arr[n])
             }else{
                logsum += log(abs(nums[i]));
             }
         }
         for(int i = 0; i < nums.size(); i++){
             // if the number itself is the only one who is zero, return exp(logsum) directly
             if(nums[i] == 0 && zerocnt == 1)
                ans[i] = round(exp(logsum));
             // there are more than one zero, the sum will always be zero, so return zero
             else if((nums[i] != 0 && zerocnt == 1) || (nums[i] == 0 && zerocnt > 1) ||
                 (nums[i] != 0 && zerocnt > 1))
                ans[i] = 0;
             //normal case (without any zero)
             else
                ans[i] = round(exp(logsum - log(abs(nums[i]))));

             // if the number itself is negative, then except itself, check if negcnt is odd
             // if yes, it means the sum will be negative
             if(nums[i] < 0){
                if((negcnt - 1) % 2)
                    ans[i] = -ans[i];
             }else{
                 if(negcnt %2)
                     ans[i] = -ans[i];
             }
         }

        return ans;
        */
    }
};
