class Solution {
    /* solution 1: sliding window
     * 1. set a sliding window from nums[left] to nums[right].
     * 2. check max elements - min elements <= limit or not
     * 3. if not, move the left pointer (left++) until we meet
     *    the criteria
     * 4. if yes, store the length of the window and
     *    move the right pointer(right++) and check the criteria again
     *
     *  Ex:  8 2 4 7  limit = 4
     *       |-|      max-min = 6 > 4 so move left pointer
     *         |      max-min = 0 < 4 so move right pointer
     *         |-|    max-min = 2 < 4 so move rigth pointer
     *         |---|  max-min = 5 > 4 so move left pointer
     *           |-|  max-min = 3 < 4 so move right pointer (the end)
     *
     * time complexity = O(nlogn) //multiset binary tree
     * space complexity = O(n)
     *
     * solution 2: monotonic queue (deque)
     * We use a min queue and a max queue to keep the min/max value in
     * the sliding window (instead of using multiset)
     * time complexity = O(n) //monotonic queue
     * space complexity = O(n)
     */
public:
    int longestSubarray(vector<int>& nums, int limit) {
        /* solution 1:*/
        int left = 0;
        int ans = 0;
        multiset<int> window;
        for(int right = 0; right < nums.size(); right++){
            window.insert(nums[right]);
            // rbegin/begin return an iterator, so we use * to get the value
            while(*rbegin(window) - *begin(window) > limit){
                window.erase(window.equal_range(nums[left]).first);
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        
        /* solution 2:
        int left = 0;
        int ans = 0;
        deque<int> minq;
        deque<int> maxq;
        for(int right = 0; right < nums.size(); right++){
            //ensure that minq has the min value of this window
            //if {1,2} nums[right] = 5 then push 5
            //if {1,2} nums[right] = 0 then pop 1,2 push 0
            while(!minq.empty() && minq.back() > nums[right])
                minq.pop_back();
            //ensure that maxq has the max value of this window
            while(!maxq.empty() && maxq.back() < nums[right])
                maxq.pop_back();
            minq.push_back(nums[right]);
            maxq.push_back(nums[right]);
            while(maxq.front() - minq.front() > limit){
                if(maxq.front() == nums[left]) maxq.pop_front();
                if(minq.front() == nums[left]) minq.pop_front();
                left++;
            }
            ans = max(ans, right - left +1);
        }
      */
        return ans;
    }
};
