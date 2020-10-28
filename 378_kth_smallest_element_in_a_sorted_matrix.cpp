class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        /* Solution:
         * 1. create a maxheap by using the values in the matrix
         * 2. keep poping items in the heap until the size of heap is k
         *    then the top of this heap will be the answer (the kth smallest element)
         *
         * time complexity: O(n*log(k))    // n*log(k) + (n-k)*log(k)
         * space complexity: O(k)          //for storing k nodes and get the top of the heap for the answer
         */
        priority_queue<int> pq;
        for(int i = 0; i < matrix.size(); i++){
            vector<int> row = matrix.at(i);
            for(int j = 0; j < row.size(); j++){
                // insert a node needs time log(k), and we have to insert n times
                pq.push(row.at(j));
                /* solution 2: instead of pop out items like solution 1,
                 *             we check the heap size every time when we add a new node.
                 *             We always keep the size of heap at k to make sure that
                 *             the top of the heap is the kth smallerest item in the heap
                 */
                // remove a node needs time log(k), and we have to remove at most (n-k) times
                if(pq.size() == k+1)
                    pq.pop();
            }
        }
        /* solution 1: we pop out the largest value until the size of the heap is k
        while(pq.size() != k)
            pq.pop();
        */

        return pq.top();
    }
};
