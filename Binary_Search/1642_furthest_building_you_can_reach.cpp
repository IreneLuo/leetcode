class Solution {
    /* solution: binary search
     * Main Idea:
     * 1. if ladders >= n-1, ans = n-1
     * 2. if sum (diffs) <= bricks, ans = n-1 (optional)
     * 3. In each iteration, we use :
     *      - ladders for those largest diffs.
     *      - bricks for those smallest diffs.
     * How do we use binary search?
     * 1. Initialize
     *    - build a diff table: diff[i] = heights[i+1]-height[i]
     *    - left = ladders (since we can at least reach to the "ladders-th" building)
     *    - right  = number of buildings
     *    - mid = left + (right - left) / 2 
     * 2. we find out the 'ladders-th' largest diffs from diff[0]~diff[m-1]
     *    by using nth_element(diff.begin, diff.end-ladders, diff.end)
     *    [a,b,c,d,e] if ladder = 1, then nth_element() will make sure that 
     *     |-----| |-->that position [end()-1] will be the largest diff
     *                 and a~d will smaller than [end()-1]
     *     ==> we assume that we'll put ladders at [end()-1]
     * 3. we calculate the sum(rest of diffs) by using accumulate()
     *    if [0]+[1]+...+[end-2] > bricks --> bricks are not enough
     *       so we have to reduce the amount of buildings by shifting right to mid
     *    else --> bricks are enough
     *       so we can increase the amount of buildings by shifting left to mid+1
     * 4. this method will find the "smallest index L " that we cannot reach
     *    so we'll return L-1
     *
     * time complexity = O(nlogn)
     *    -total O(logn) iterations and O(n) for each iteration
     * space complexity = O(n) //diff[]
     *
     * Ex:       [4,2,7,6,9,14,12] b = 5, l = 1
     *    diff = [0,5,0,3,5,0]  n = 7
     *
     *    left right mid   diff         nth_element  sum  >b  to
     *      1    7     4 [0,5,0,3]    -> [0,3,0,5]    3    f  right
     *      5    7     6 [0,5,0,3,5,0]->[0,3,0,0,5,5] 8    t  left
     *      5    6     5 [0,5,0,3,5]  ->[0,3,0,5,5]   8    t  left
     *      5    5     -> 5 is the building that we "cannot reach"
     *                 -> return 4
     * Solutions 2: min-Heap
     * Main idea:
     *   1. use a min-Heap to track all the diffs so far
     *   2. assume that we use ladders first until ladders are not enough
     *      (i.e heap size < ladders)
     *   3. if ladders are not enough, pick a smallest diff from min-Heap
     *      and use bricks for that smallest one
     *      (then bricks = bricks - smallest diff)
     *   4. keep updating bricks until bricks are not enough
     *      then we return i-1 (since i is the smallest building L that we cannot reach)
     * Pros: we don't have to calculate the diffs for each buildings first
     * time complexity = O(nlogL)
     * space complexity = O(L) //heap size won't > ladders
     */
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int n = heights.size();
        //n buildings needs at least n-1 ladders to reach
        if(ladders >= n - 1) return n-1;
        //calculate the diff between each building
        vector<int> diff(n);
        for(int i = 1; i < n; i++)
            diff[i-1] = max(0, heights[i] - heights[i-1]);
        //use ladders for largest diff, check the sum of the rest of diffs > bricks
        //if yes, go to the left part since the bricks are not enough
        int left = ladders;
        int right = n;
        while(left < right){
            int mid = left + (right - left) / 2;
            //only copy diff[0] to diff[mid-1]
            vector<int> copy_diff(diff.begin(), diff.begin()+mid);
            //if ladders = 2
            //[a,b,c,e,d,f,g]
            //           |--| we assume that we use ladders at these two positions
            //           because nth_element() will guarantee that f,g are the two
            //           largest diffs
            nth_element(copy_diff.begin(), copy_diff.end() - ladders, copy_diff.end());
            int sum = accumulate(copy_diff.begin(), copy_diff.end() - ladders, 0);
            if(sum > bricks)
                right = mid;
            else
                left = mid + 1;
        }
        return left-1;
        /* solution 2:
        int n = heights.size();
        if(ladders >= n - 1) return n-1;
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 1; i < n; i++){
            const int d = heights[i] - heights[i-1];
            if(d < 0) continue;
            pq.push(d);
            if(pq.size() <= ladders) continue;
            bricks -= pq.top();
            pq.pop();
            if(bricks < 0)
                return i-1;
        }
        return n-1;
        */
    }
};
