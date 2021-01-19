#include <iostream>
#include <vector>
using namespace std;

struct TreeNode{
	int key;
	int data;
	TreeNode(): key(0), data(0) {};
	TreeNode(int k, int d): key(d), data(d) {};
};
class BinaryHeap{
private:
	/* store the TreeNode entities */
	vector<TreeNode> heap;
	void Swap(int t1, int t2);
	int FindPosition(int value);
	bool isEmpty();
	int GetParentIdx(int idx);
	int GetLeftIdx(int idx);
	int GetRightIdx(int idx);
	void siftup(int index);

public:
	BinaryHeap();
	BinaryHeap(int n);
	void MinHeapify(int node, int length);
	void BuildMinHeap(vector<int>& array);
	int GetPeek();
	int ExtractMin();
	void DecreaseKey(int oldkey, int newkey);
	void Insert(int key, int value);
	void print();
};
BinaryHeap::BinaryHeap(){
	heap.resize(1);
}
BinaryHeap::BinaryHeap(int n){
	heap.resize(n);
}
/* helper function */
void BinaryHeap::Swap(int t1, int t2){
	TreeNode temp = heap[t1];
	heap[t1] = heap[t2];
	heap[t2] = temp;
}
int BinaryHeap::FindPosition(int value){
	for(int i = 0; i < heap.size(); i++)
		if(heap[i].key == value) return i;
	return -1;
}
bool BinaryHeap::isEmpty(){
	return heap.size() < 1;
}
int BinaryHeap::GetParentIdx(int idx){
	return (idx - 1) / 2;
}
int BinaryHeap::GetLeftIdx(int idx){
	return idx * 2 + 1;
}
int BinaryHeap::GetRightIdx(int idx){
	return idx * 2 + 2;
}
/* Main function */
/* MinHeapify()
 * node: idx of current node
 * length: total size of TreeNode in heap
 * (heap size= 4 --> length=4, so node must be < 4)
 *
 * 1. if left child exists, find a smaller one between parent and left child
 * 2. if right child exists, find a smaller one between parent and right child
 * 3. if current node isn't the smallest one, swap the content with the smaller one
 * 4. for the node that swap the data with current node, do a minHeapify() again
 *    ( to ensure that the subtree under current node match the rules of priority queue)
 */
void BinaryHeap::MinHeapify(int node, int length){
	int smallest = node;
	int left = GetLeftIdx(node);
	int right = GetRightIdx(node);
	if(left < length && heap[left].key < heap[node].key)
		smallest = left;
	if(right < length && heap[right].key < heap[smallest].key)
		smallest = right;
	if(smallest != node){
		Swap(smallest, node);
		MinHeapify(smallest, length);
	}
}
/* BuildMinHeap()
 * 1. create TreeNode entities and store in a vector
 * 2. Heapify all the nodes that has children
 *    --> so we start from node which index = size/2
 */
void BinaryHeap::BuildMinHeap(vector<int>& array){
	for(int i = 0; i < array.size(); i++){
		TreeNode node(array[i], array[i]);
		heap[i] = node;
	}
	//build min-Heap
	for(int i = heap.size()/2; i >= 0; i--)
		MinHeapify(i, heap.size());
}
/* Return the minimum data in the heap */
int BinaryHeap::GetPeek(){
	return heap[0].data;
}
/* Extract the TreeNode which has the minimum data and remove it.
 * After removing it, heapify the heap again
 */
int BinaryHeap::ExtractMin(){
	if(isEmpty()){
		fprintf(stderr, "Cannot extract minimum item since the heap is empty!\n");
		return -1;
	}
	int min = heap[0].data;
	int lastidx = heap.size()-1;
	heap[0] = heap[lastidx];
	heap.erase(heap.begin() + lastidx);
	MinHeapify(0, heap.size());
	return min;
}
/* siftup()
 * bubble-up the item
 */
void BinaryHeap::siftup(int idx){
	while(idx >= 0 && heap[GetParentIdx(idx)].key > heap[idx].key){
		Swap(idx, GetParentIdx(idx));
		idx = GetParentIdx(idx);
	}
}
/* DecreaseKey()
 * 1. find the position of the TreeNode which heap[position].data == data
 * 2. change the key to newkey if newkey < original key
 *    (unnecessary to change the key if newkey > original key)
 * 3. after updating the key, compare current node with its parent
 *    if current node's key < parent's key, then swap the node
 *    (bubble-up checking the key's of current node and it's parent)
 * we create a siftup() for step 3
 * Note that:
 * 	FindPosition() will take O(n), so DecreaseKey() will be bounded to O(n)
 * 	In order to save more time, we could also use a hashtbl to
 * 	save all the address of each node, then we can decrease the time
 * 	in FindPosition() to O(1). And the time of DecreaseKey() can be O(logn)
 */
void BinaryHeap::DecreaseKey(int data, int newkey){
	int idx = FindPosition(data);
	if(newkey > heap[idx].key){
		fprintf(stderr, "newKey > key so decrease fail\n");
		return;
	}
	heap[idx].key = newkey;
	siftup(idx);
}
void BinaryHeap::Insert(int key, int value){
	heap.push_back(TreeNode(key, value));
	//DecreaseKey(value, value);
	siftup(heap.size()-1);
}
void BinaryHeap::print(){
	for(int i = 0; i < heap.size(); i++)
		cout<<heap[i].data<<" ";
	cout<<endl;
}
int main(void){
	int heapsize = 5;
	vector<int> input;
	input.push_back(5);
	input.push_back(3);
	input.push_back(4);
	input.push_back(2);
	input.push_back(1);

	BinaryHeap bp(heapsize);
	bp.BuildMinHeap(input);
	bp.print();

	for(int i = 1; i <= 3; i++){
		int min = bp.ExtractMin();
		if(min > 0)
			cout<<" extract min = "<<min<<endl;
	}
	bp.print();

	bp.Insert(12,12);
	bp.Insert(3,3);
	bp.print();
	return 0;
}
