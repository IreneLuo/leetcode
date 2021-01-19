class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        /* method 1: brutforce, may time limit exceeded
        int ans = 0;
        int sum;
        for (int i = 0; i < nums.size(); i++){
            if (nums[i] == k)
                ans++;
            sum = nums[i];
            for (int j = i+1; j < nums.size(); j++){
                sum += nums[j];
                if (sum == k)
                    ans++;
            }             
        }
        */
        /* solution: hashmap
         * [1,2,3,4,5,6,7] k = 10
         *  |---| sum[i] 
         *  |-----------| sum[j]
         *  if sum[j] - sum[i] = k
         *  then there's must be a continuous subarray
         *  between [i] to [j] that sums up to k
         * 
         *  we accumulate the num[i]= sum
         *  and find out if there's a continuous subarray
         *  sums up to (sum-k) before.
         *  If yes, then we add the count(in the hashtbl)
         *
         *  time complexity = O(n)
         *  space complexity = O(n)
         */
        int ans = 0;
        int sum = 0;
        unordered_map<int, int> mm;
        mm.insert(pair<int, int>(0, 1));
        for (int i = 0; i < nums.size(); i++){
            sum += nums[i];
            //if find (sum-k) in the hashtbl, then there's must have at least one
            //continuous subarrays sums up to (sum-k)
            auto it = mm.find(sum - k);
            if (it != mm.end())
                ans += mm[sum-k];
            //store current sum
            it = mm.find(sum);
            if (it == mm.end())
                mm.insert(pair<int, int>(sum, 1));
            else
                mm[sum] += 1;
           
        }
        
        return ans;   
    }
};
