class Solution {
    /* solution 1: maxHeap
     * Let's redefine the formula:
     * yi+yj+|xi-xj| = yi+yj + xj-xi (since xj must greater than xi)
     *               = xj+yj + yi-xi
     *                   ^       ^
     *                 pointj  pointi
     *
     * for point j, xj+yj is a constant, the key is to find a largest yi-xi
     *                p0, p1,..,ps,..., pi, ..., pj
     *                           |----------------|
     * from the sliding window ps to pj, find a pi that yi-xi is the largest one
     *
     *
     * Method:
     *  1. Build a max-Heap with key, value = yi-xi, xi
     *  2. Iterate over all the points
     *     1. The point that we iterate is point j
     *     2. The top point in the max-Heap is point i
     *     3. check if xj-xi <= k
     *          - if yes, calculate ans = xj+yj + yi-xi
     *          - if no, pop the top item in max-Heap, and check the next one
     *            (xj' will be larger than xj, even we do xj'-xi will still > k, so pop xj)
     * time complexity = O(nlogn) worst case //extract n times from max-Heap
     *                 = O(n) best case
     * space complexity = O(n) worst case //n elements in max-Heap
     *                  = O(1) best case  //1 element in max-Heap
     * Worst Case: (1,2) (2,4) (3,6) (4,8) k = 1
     *    j   p        Heap                ans
     *    0  (1,2)     (1,1)                -
     *    1  (2,4)     (2,2)(1,1)           7   ans = 2+4+1, push(4-2, 2)
     *    2  (3,6)     (3,3)(2,2)(1,1)      11  ans = 3+6+2, push(6-3, 3)
     *    3  (4,8)     (4,4)(3,3)(2,2)(1,1) 15  ans = 4+8+3, push(8-4, 4)
     *  every point meet the criteria of xj-xi<=k, so we push n points into the max-Heap
     *
     * Solution 2: deque
     * We could decrease the items in the max-Heap, just keep the max one only
     * This kind of "find a largest item in a sliding window" problem,
     * we could use deque to get rid of useless items in it.
     *
     * Worst Case: (1,2) (2,4) (3,6) (4,8) (5,8) (6,9) k = 1
     *    j   p        Heap                ans
     *    0  (1,2)     (1,1)                -
     *    1  (2,4)     (2,2)                7   ans = 2+4+1, push(4-2, 2)
     *    2  (3,6)     (3,3)                11  ans = 3+6+2, push(6-3, 3)
     *    3  (4,8)     (4,4)                15  ans = 4+8+3, push(8-4, 4)
     *    4  (5,8)     (4,4)(3,5)           17  ans = 5+8+4, 8-5 < 4 so push(8-5,5)
     *    5  (6,9)     (3,5)(3,6)           18  pop(4,4) because xj-xi>k
     * time complexity = O(n)
     *   - each node will be push and pop once
     * space complexity = O(n)
     *
     * similar: leetcode 1438
     */
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        /* solution 1
        // key, value = yi-xi, xi
        priority_queue<pair<int, int>> pq;
        int ans = INT_MIN;
        for(int j = 0; j < points.size(); j++){
            int xj = points[j][0];
            int yj = points[j][1];
            //if xj-xi <= k or not
            while(!pq.empty() && xj - pq.top().second > k)
                pq.pop();
            //ans = yi-xi + xj + yj 
            if(!pq.empty())
                ans = max(ans, pq.top().first + xj + yj);
            pq.emplace(yj-xj, xj);
        }
        return ans;
        */
        deque<pair<int, int>> dq;
        int ans = INT_MIN;
        for(int j = 0; j < points.size(); j++){
            int xj = points[j][0];
            int yj = points[j][1];
            //if xj-xi <= k or not
            while(!dq.empty() && xj - dq.front().second > k)
                dq.pop_front();
            //ans = yi-xi + xj + yj 
            if(!dq.empty())
                ans = max(ans, dq.front().first + xj + yj);
            /*  dq: (6,1)(3,2)(2,2)
             *  if yj-xj = 5 then pop (3,2)(2,2) push (5,xj)
             *                 because v    v  are < 5
             */
            while(!dq.empty() && yj-xj > dq.back().first)
                dq.pop_back();
            dq.emplace_back(yj-xj, xj);
        }
        return ans;
    }
};
