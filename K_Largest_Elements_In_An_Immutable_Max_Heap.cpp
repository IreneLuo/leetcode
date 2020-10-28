istruct HeapNode{
  int val;
  int idx;
  HeapNode(int v, int i): val(v), idx(i) {}
};

struct mycompare{
  bool operator()(HeapNode a, HeapNode b){
    return a.val < b.val;
  }
};
class Solution {
  public:
    /* get the child index (left=1 for left child, left=0 for right child)
     * return -1 if this node doesn't have any child node
     * idx of left child: selfidx * 2 + 1
     * idx of right child: selfidx * 2 + 2
     * idx of parent: (selfidx - 1) / 2
     */
    int get_left_child_idx(int left, HeapNode node, int max){
      int  ans = (left == 1) ? (node.idx * 2 + 1) : (node.idx * 2 + 2);
      return (ans < max) ? ans : -1;
    }
    
    vector<int> kLargestInImmutableHeap(vector<int>& immutableHeap, int k) {
      /* solution:
       * 1. create a helper heap, push the first item(topnode) into the helper heap.
       *    pop the first item directly(because the input is already a heap,
       *    the first item must be the largest one)
       * 2. push the children node of topnode into the helper heap
       * 3. pop out the item from the helper heap one at a time and
       *    insert into the answer list until the answer list's size is k
       *  ex: [17,7,16,2,3,15,14], k = 6
       *                helperheap      ans              left   right
       *        1.        [17]                                        //push 1st item into heap
       *        2.        []            [17]              7       16  //pop it and find its left/right
       *        3.        [16 7]                                      //push them into heap
       *        4.        [7]           [17,16]           15      14  //pop it and find its left/right
       *        5.        [15,14,7]                                   //push them into heap
       *        6.        [14,7]        [17,16,15]        x       x   //pop it and find its left/right
       *        7.        [7]           [17,16,15,14]     x       x   //none of item's been pushed, pop the heap
       *        8.        []            [17,16,15,14,7]   2       3   //pop the heap and find its left/right again
       *        9.        [2,3]         
       *        10.       [2]           [17,16,15,14,7,2] x       x
       *
       *  time complexity = O(klogk) + O(3k) = O((k+3)*logk) = O(klogk)
       *    - remove(pop) item from the heap for k times: O(klogk)
       *    - add left/right child: O(k) + O(k)
       *    - access(top) item from the heap for k times: O(1) * k
       *  space complexity = O(k) + O(ck) = O(k)
       *    - vector<int> ans: O(k)
       *    - heap pq:O(k*c), which c is a constant depends on numbers of children that we add
       */
      priority_queue<HeapNode, vector<HeapNode>, mycompare> pq; //space O(k)
      vector<int> ans;
      if (k == 0)
        return ans;
      
      HeapNode node(immutableHeap.at(0), 0);
      pq.push(node);
      while(ans.size() < k) {
        HeapNode topnode = pq.top();
        ans.push_back(topnode.val);
        cout<<"push "<<topnode.val<<endl;
        pq.pop();
        int idx_left_child = get_left_child_idx(1, topnode, immutableHeap.size());
        int idx_right_child = get_left_child_idx(0, topnode, immutableHeap.size());
        if(idx_left_child > 0) {
          HeapNode n(immutableHeap.at(idx_left_child), idx_left_child);
          cout<<"push left child "<<idx_left_child<<", "<<immutableHeap.at(idx_left_child)<<endl;
          pq.push(n);
        }
        if(idx_right_child > 0) {
          HeapNode n(immutableHeap.at(idx_right_child), idx_right_child);
          cout<<"push left child "<<idx_left_child<<", "<<immutableHeap.at(idx_left_child)<<endl;
          pq.push(n);
        }

      }
      return ans;
    }
};
