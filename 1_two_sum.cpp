class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
/* Solution 1: (Brute Force)
 * Loop through all the element in nums to find the anser
 * Time complexity = O(n^2)
 * Space complexity = O(1)
 */
/*
        for (int i = 0; i < nums.size()-1; i++) {
            for(int j = 0; j < nums.size(); j++) {
                if (i == j) continue;
                if ((nums[i] + nums[j]) == target) {
                    return {i, j};
                }
            }
        }
        return {};
*/
/* Solution 2: (Hash Table)
 * While we iterate the element, we'll
 * 1. get the complement (target - nums[i])
 * 2. serve the complement as a key and look back to check if
 *    the key already exists in the table
 * 3. if it exists, then that's the answer, just return {value of that match item, i}
 * 4. if it doesn't exist, then insert a new tuple in the table --> (nums[i], i)
 * Time complexity = O(n)
 * Space complexity = O(n)
 * ex: nums={2, 11, 15, 7} target = 9
 *     i = 0 -> target - nums[i] = 9 - 2 = 7   --> umap = (2, 0)
 *     i = 1 -> target - nums[i] = 9 - 11 = -2 --> umap = (2, 0), (11, 1) 
 *     i = 2 -> target - nums[i] = 9 - 7 = 2   --> find a key = 2 in umap so that's the answer
 *                                                 return (0,2)
 */
        unordered_map<int, int> umap;
        for (int i = 0; i < nums.size(); i++) {
            if(umap.count(target - nums.at(i)))
                return {umap.at(target - nums.at(i)), i};
            umap.insert(make_pair(nums.at(i), i));
        }
        return {};
    }
};
