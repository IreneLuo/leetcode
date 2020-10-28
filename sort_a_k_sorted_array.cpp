class Solution {
  public:
    /* solution: use min-Heap
     *  1. insert the first k items into the min-Heap
     *  2. from kth to the last items
     *     1. insert 1 item at a time
     *     2. pop out the item (this will be the min item in the heap)
     *  3. after traversing the items in arr, we keep poping out
     *     the rest of the items in the min-Heap
     *
     *  (starts from 2 since 2 is the farthest item that can be push when we try to select the 1st min item)
     *  ex:          [3,4,1,2,5,6] k=3
     *                      ^ ^ ^
     *            a   b c d e f g
     *          ------------------    a. init min-heap
     *  min-heap  3   3 3 3 4 5 6     b. push 2 and pop
     *            4   4 4 4 5 6       c. push 5 and pop
     *            1   1 2 5 6         d. push 6 and pop
     *                2 5 6           e-g. pop until heap is empty
     *---------------------------     *) the heap size is always k+1 (add 1 to include itself(ex: 2))
     *  pop           1 2 3 4 5 6
     *
     *  time complexity: O(nlog(k)) //n times push and pop, and each time (for push) we need log(k) to restruct the tree
     *  space complexity: O(k) //for heap
     */
    vector<int> sortNearlySortedArray(vector<int>& arr, int k) {
      //a min-Heap use Comparison Object greater<int>
      priority_queue<int, vector<int>, greater<int>> pq;
      int arrsize = arr.size();
      vector<int> ans;
      // if k < arrsize, we push k items into the heap
      // if k > arrsize, we push arrsize items into the heap
      for(int i = 0; i < arrsize && i < k; i++)
        pq.push(arr[i]);
      
      int i = k;
      while(i < arrsize){
        pq.push(arr[i]);
        i++;
        ans.push_back(pq.top());
        pq.pop();
      }
      while(!pq.empty()){
        ans.push_back(pq.top());
        pq.pop();
      }
      return ans;
    }
};
