#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Analysis
 * Time complexity:
 * BuildHeap phase:
 *   1. we bubble down n/2 items, and in each iteration we spend logn times --> O(n/2 * logn) = O(nlogn)
 *      (logn is the worst case level)
 *   2. However, if we look into each comparison, this is not a tight boundary.
 *      Unintuitively, the BuildHeap phase runs in O(n) time.
 *      p.s) [1] this is why we start from n/2th item in BuildHeap phase since we don't have buuble down the leaves.
 *      Explain: What is the worst amount of comparison?
 *                      total  #n  worst amount of comp
 *
 *          []              ---1 * 6 (comapres 2 times per level, and there are 3 levels)      
 *        /    \            |
 *      []      []       7  |  2 * 4 (each node compares 2 times per level, and there are 2 levels)
 *     /  \    /  \         |
 *    []  []  []  []        ---4 * 2 (each node compares 2 times before a swap
 *    /\  /\  /\  /\        -
 *   [][][][][][][][]    8  |  8 * 0 ([1]half of nodes are leaves)
 *                          -
 *   so the total worst amount of work:
 *   (0 * n/2) + (2 * n/4) + (4 * n/8) + (6 * n/16) + ... = 2n --> we can bound tightly to theta(n)
 *   
 * Extract phase:
 *  1. total n-1 iterations (from the last item to the second item)
 *  2. summation:
 *             n
 *           Zigma(2 * log(i)) = 2nlog(n)-2nlog(e)+log2(pi)+logn --> we can bound it to O(nlogn)
 *            i=2
 *            [1] 2 comparisons per level traverse
 *            [2] after a replacement, we reduce the heap size, so we use log(i) to decide levels in heap.
 *            Find out the solution on WolframAlpha or symbolab

 */ 
class Solution {
  public:
    void swap(int& a, int& b){
      int tmp = a;
      a = b;
      b = tmp;
    }
    //size: the count of members in this array
    void buildHeap(vector<int>& arr, int targetIdx, int size){
      int largest = targetIdx;
      int leftChildIdx = (targetIdx * 2) + 1;
      int rightChildIdx = (targetIdx * 2) + 2;
 
      //compare target with left child & right child
      if(leftChildIdx < size)
        largest = (arr[largest] < arr[leftChildIdx]) ? leftChildIdx : largest;
      if(rightChildIdx < size)
        largest = (arr[largest] < arr[rightChildIdx]) ? rightChildIdx : largest;
      // swap the target with the maximum one
      // and keep comparing the item that we just bubbled down
      // until we meet the leaf node
      if(largest != targetIdx){
        swap(arr[largest], arr[targetIdx]);
        buildHeap(arr, largest, size);
      }
    }
    void extractItems(vector<int>& arr, int targetIdx){
      //swap the max item(arr[0] with the target)
      swap(arr[targetIdx], arr[0]);
      //in buildHeap(), we only check the node from idx 0 to targetIdx-1
      //since the value of idx targetIdx has already been set to a maximum value
      buildHeap(arr, 0, targetIdx);
    }
    vector<int> heapsort(vector<int>& arr) {
      int num = arr.size();
      for(int i = num / 2; i >= 0; i--)
        buildHeap(arr, i, num);
      for(int i = num - 1; i >= 0; i--)
        extractItems(arr, i);
      return arr;
    }
};

int main(void){
	Solution sol;
	int inputraw[] = {10, 6, 7, 5, 15, 17, 12};
	vector<int> input(inputraw, inputraw+(sizeof(inputraw)/sizeof(int)));
	sol.heapsort(input);
	for(int i = 0; i < input.size(); i++){
		cout<<input[i]<<",";
	}
	cout<<endl;
}
