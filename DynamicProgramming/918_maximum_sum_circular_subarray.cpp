class Solution {
public:
    /* Solution:
     * A.
     * Before starting to fix this problem, let's consider how to get a maximum subarray sum if this array is not curcular?
     *   -> calculate the sum that ends up at element i = sum that ends up at element i-1 + i
     *   -> if sum that ends up at element i-1 < 0, then we drop it off, and only add i,
     *      because a negative sum + i will make the sum smaller
     *   ex:            1, -2, 3, -2
     *     sumSoFar 0   1  -1  3   1  
     *                         |---|---->sum[1]<0, so sum[2]=A[2]
     *                             |---->sum[2]>0, so sum[3]=A[3] + sum[2]
     * B.
     * Now for this problem, we can use Kadane's algorithm to solve it
     * Consider three cases:
     *  1. [1,2,3] all positive values in A:
     *     maximum subarray sum = 1 + 2 + 3, so we only have to acculate the sum of all the elements
     *  2. [5,-1,5] at least 1 negative value in A
     *     maximum subarray sum = total - minimum subarray sum = (5+(-1)+5) - (-1) = 10
     *     but how can get the minimum subarray sum? We can negate the elements and use the method we mention in A.
     *  3. [-2,-3,-1] all negative values in A
     *     maximum subarray sum = -1
     *
     *  So for this 3 cases, we use three variables to collect the sum that we need
     *    - maxSumAtLast: the max value of maxSumSoFar
     *    - maxSumSoFar: the max sum to A[i] so far : max (maxSumSoFar + A[i], A[i])
     *    - minSumSoFar: the min sum to A[i] so far 
     *    - total: the sum to A[i]
     *
     *  And in our return statement, we can return a correct answer for these three cases
     *    - (total == minSumAtLast) ? maxSumAtLast: max(total - minSumAtLast, maxSumAtLast);
     *                                (case 3)            (case 2)              (case 1)
     *
     *
     *  Ex: [1, -2, 3, -2]     step  maxSumAtLast   maxSumSoFar   total
     *       ^   ^  ^   ^      init       1             0           0
     *       a   b  c   d        a        1             1           1
     *             |             b        1(1>-1)     1+-2=-1     1+-2=-1
     *             |             c        3             3         -1+3=2
     *             v             d        3           3+-2=-1     2+-2=0
     *      [-1, 2, -3, 2]     step  minSumAtLast   minSumSoFar
     *       ^   ^  ^   ^      init        -1           0
     *       e   f  g   h        e         -1           -1
     *                           f          2           2
     *                           g          2           -1
     *                           h          2            2
     *                                      |------------------> minSumAtLast = -2
     *   return max(total - minSumAtLast, maxSumAtLast) = max(0 - (-2), 3) = 3
     */
    int maxSubarraySumCircular(vector<int>& A) {
        if(A.size() <= 1)
            return A.back();

        // first phase: calculate the total amount and get the maximum Sum of a subarray in A
        int maxSumAtLast = A[0]; // the maximum value of maxSumSoFar
        int maxSumSoFar = 0; // the sum of a subarray
        int total = 0;   // the sum of whole array
        for(auto& num : A){
            // if the sum of previous item < 0, we drop off the sum.
            // Because a negative sum + num will make sum smaller
            if(maxSumSoFar < 0)
                maxSumSoFar = 0;
            maxSumSoFar += num;
            total += num;
            maxSumAtLast = max(maxSumAtLast, maxSumSoFar);
            num = -num; // we negate the elements to extract the negative items in the second phase
        }
        // second phase: calculate the minimum sum of a subarray in A
        int minSumAtLast = A[0];
        int minSumSoFar = 0;
        for(auto& num : A){
            if(minSumSoFar < 0)
                minSumSoFar = 0;
            minSumSoFar += num;
            minSumAtLast = max(minSumAtLast, minSumSoFar);
        }
        minSumAtLast = -minSumAtLast;
        
        return (total == minSumAtLast) ? maxSumAtLast: max(total - minSumAtLast, maxSumAtLast);
    }
};
