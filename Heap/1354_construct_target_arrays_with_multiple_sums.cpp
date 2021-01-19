class Solution {
    /* solution: max-Heap
     * Instead of finding every possible ways from [1,1,1] to target,
     * we use some math skills to check that can target be changed to [1,1,1]
     * Observation: we don't have to consider the order between each number
     *
     *   Ex1:                       Ex2:
     *   [9,3,5]                    [1,7,100]
     *      v     3+5+x=9 -> x=1        v      x=100-(1+7)=92
     *   [1,3,5]                    [1,7,92]
     *      v     1+3+x=5 -> x=1        v      x=92-(1+7)=84 
     *   [1,1,3]                    [1,7,84]  
     *      v     1+1+x=3 -> x=1        v      x=84-(1+7)=76
     *   [1,1,1]                    [1,7,76]
     *                                  v
     *   for [a,b,c]                When max is way more bigger than a and b
     *   --> x = max(c) - sum(ab)   we'll need to run 10^9 times --> > time limit
     *
     *   Ex2: (extended)
     *   [1,7,100]  
     *       v        100 - (1+7)*k = remain = 100 % 8 = 4
     *   [1,7, 4]     we use max % (sum of ab) to speed up the process
     *       v        7 % (1+4) = 2
     *   [1,4,2]    
     *       v        4 % (1+2) = 1
     *   [1,2,1]      so now we know that it's impossible to change to [1,1,1]
     *                since 1+1+x cannot equal to 2 if x is a positive number
     *
     *   special case 1: [1,m] --> it's can definitely be changed to [1,1]
     *                             so return true directly
     *   special case 2: [m] --> it's impossible to change it to [1]
     *                             so return false directly
     *   special case 3: [4,4,6] --> we cannot find a x that 4+4+x=6
     *                              so if sum(ab) >= max, return false
     *   special case 4: [1,7,16] -> [1,7,0] --> cannot have 0, return false
     *
     *  time complexity = O(n + klogn)
     *     - accumulate: O(n)
     *     - retrieve an item from heap: O(logn)
     *     - the sum will be at least halved at each step
     *       there are at most k = log(sum) = log(t*n) steps = 46 steps
     *        (t = 10^9, n=5*10^4)
     *  worst case [1,4,7,13] sum = 25
     *             [1,4,7,1]  sum = 13
     *             [1,4,1,1]  sum = 7
     *             [1,1,1,1]  sum = 4
     *  best case [1,10^9]    sum = 10^9+1
     *            [1,1]       sum = 2
     *  space complexity = O(n)
     *  Reference: HuaHua's video
     */
public:
    bool isPossible(vector<int>& target) {
        priority_queue<int> pq(begin(target), end(target));
        long sum = accumulate(begin(target), end(target), 0LL);
        while(true){
            int max = pq.top(); pq.pop();
            //normal case: [1,1,1] --> the max = 1
            if(max == 1) return true;
            sum = sum - max;
            //special case 1: [1,m] --> sum - max = 1
            if(sum == 1) return true;
            //special case 2: [m] --> sum = 0
            //special case 3: [4,4,6] --> sum-max=14-6=8
            if(sum == 0 || sum >= max) return false;
            int remain = max % sum;
            //[1,7,16] -> [1,7,0]
            if(remain == 0) return false;
            pq.push(remain);
            sum += remain;
        }
    }
};
