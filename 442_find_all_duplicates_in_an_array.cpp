class Solution {
public:
    /* solution: using a hash table
     * Iterate over each item in nums
     *  1. if item doesn't exist in the hash table, insert it as <key,value> = <item, idx>
     *  2. if item exists, push into the answer 
     *
     *  time complexity: O(n) //insert n items to the hash tbl in worst case
     *  space complexity: O(n) //to save n items in the hash tbl in worst case
     */
    vector<int> findDuplicates(vector<int>& nums) {
        /*
        unordered_map<int, int> hash_tbl;
        vector<int> ans;
        if(nums.size() == 0)
            return {};
        for(int i = 0; i < nums.size(); i++){
            if(hash_tbl.find(nums.at(i)) != hash_tbl.end()){
                ans.push_back(nums.at(i));
            }else{
                hash_tbl.insert(pair(nums.at(i), i));
            }
        }
        return ans;
        */

        /* solution 2: reverse the item
         * Iterate over each item in nums
         *  1. find a target index, which target index = |current value| - 1
         *  2. if nums[target index] is a negative value, set it to positive and push it into answer --> it means that we've met this value before
         *     if nums[target index] is not a negative value, set nums[target index] to a negative value
         *
         *  time complexity: O(n)
         *  space complexity: O(1)
         */
        vector<int> ans;
        for(int i = 0; i < nums.size(); i++){
            int curr_value = nums.at(i);
            int target_idx = abs(curr_value) - 1;
            int target_val = nums.at(target_idx);
            if(target_val > 0){
                nums[target_idx] = -target_val;
            }else{
                nums[target_idx] = -target_val;
                // must push abs(curr_value), since curr_value might be a negative value
                ans.push_back(abs(curr_value));
            }
        }
        return ans;
    }
};
