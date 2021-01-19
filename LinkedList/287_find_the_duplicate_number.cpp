class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        /* solution3:  Floyd's Tortoise and Hare (Cycle Detection)
         * time complexity = O(n)
         * space complexity = O(1)
         */
        //phase 1:
        int tortoise = nums[0];
        int hare = nums[0];
        do{
            tortoise = nums[tortoise]; //tortoise goes 1 step
            hare = nums[nums[hare]];   //hare goes 2 steps
        }while(tortoise != hare);
        //phase 2:
        tortoise = nums[0];
        while(tortoise != hare){
            tortoise = nums[tortoise];
            hare = nums[hare];
        }
        return hare;

        /* solution1: use set
         * time complexity = O(n)
         * space complexity = O(n)
        set<int> tbl;
        for(auto n: nums){
            if(tbl.count(n)) return n;
            tbl.insert(n);
        }
        return -1;
        */
        /* solution2: sorting 
         * time complexity = O(nlogn) sorting
         * space complexity = O(1) if we can modify the input arrray
         *                  = O(n) if we cannot modify the input array,
         *                         we need an extra linear space for a copy of input
         
        sort(nums.begin(), nums.end());
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] == nums[i-1]) return nums[i];
        }
        return -1;
        */
    }
};
