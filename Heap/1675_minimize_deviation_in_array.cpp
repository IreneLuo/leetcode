class Solution {
    /* solution: heap or set
     * Observation:
     * for number n
     *   1. if n is odd, then it will be n*2
     *      n*2 is even, then it will be n*2/2=n --> we should stop here
     *      so if n is odd, it can only be changed to even once,
     *      and to odd once.
     *   2. if n is even, then it will be n/2, n/4,...
     *      n will become smaller
     *
     * 1. change all the odd numbers (n) to n*2
     *    (so all the numbers are even)
     * 2. pick a max number and calculate the deviation = max - min
     * 3. change the max number(n) to n/2 
     *    and go to step 2 until the max number is odd
     * Why stop at max number is odd?
     *    if we continue the process, we'll change the max number(n) to n*2,
     *       however, n*2 has been handled at previous iteration
     *    if we continue the process, we'll change other numbers to n/2
     *       but this will increase the deviation because max value
     *       doesn't change but min value might get smaller
     *
     * time complexity = O(n*logm*logn)
     *   - n items to handle with the heap
     *   - for number m, it takes logm time to decrease to 1
     *     (since we have to stop when m is odd)
     *   - logn for 1 heap operation
     * space complexity = O(n)
     */
public:
    int minimumDeviation(vector<int>& nums) {
        /* solution 1: heap */
#if 0
        //create a max-heap
        priority_queue<int> pq;
        //we need to track the min item since max-heap cannot provide the min item
        int min_value = INT_MAX;
        //push all the numbers into the heap
        //if number n is odd, change it to n*2
        for(int i = 0; i < nums.size(); i++){
            int n = (nums[i] & 1) ? nums[i] * 2 : nums[i];
            pq.push(n);
            min_value = min(min_value, n);
        }
        /* While the max value is not an odd number,
         *  1. max = max/2
         *  2. update min
         *  3. push max to the heap
         *  4. calculate the deviation (new top item - min)
         * Example: [9,4,3,6,2]     d       max/2
         *       pq: 2 4 6 6 18   18-2=16   18/2=9
         *           2 4 6 6 9    9-2=7     stop
         *
         * Disadvantage:
         *    1. need to track the min value
         *    2. can have several same values
         *    ==> may increase processing time
         */
        int deviation = pq.top() - min_value;
        while((pq.top() & 1) == 0){
            int max = pq.top(); pq.pop();
            max = max / 2;
            pq.push(max);
            min_value = min(min_value, max);
            //calculate with the new max item with min value
            //so we can get the deviation of pq.top-min if pq.top is odd
            deviation = min(deviation, pq.top() - min_value);
        }
        return deviation;
#endif
        /* solution 2: set
         * Advantage:
         *    1. O(1) to get the max/min value
         *    2. avoid same values in the set
         */
        set<int> cand;
        for(int i = 0; i < nums.size(); i++){
            int n = (nums[i] & 1) ? nums[i] * 2 : nums[i];
            cand.insert(n);
        }
        int deviation = *cand.rbegin() - *cand.begin();
        while(*cand.rbegin() % 2 == 0){
            int max = *cand.rbegin();
            cand.insert(max/2);
            cand.erase(max);
            deviation = min(deviation, *cand.rbegin() - *cand.begin());
        }
        return deviation;
    }
};
