#include <iostream>
#include <vector>
using namespace std;

/* Analysis
 * 1. Choosing bad pivots --> pivots is the largest or the least value
 *    ex: 9,8,7,6,1
 *        -> x|1|9.8,6,7
 *        (1 is pivot, and we'll split the input into two parts,
 *         where left part has 0 items and right part has n-1 items)
 *        total comparisons = (n-1)+(n-2)+(n-3)+...+1 = [1+(n-1)]*(n-1)/2 = n(n-1)/2 = O(n^2) in worst case
 *                              |
 *                        top level we do n-1 comparisons
 *
 * 2. Choosing good pivots --> a pivot is the media of the partitioning space
 *    ex: 9,10,6,8,7
 *             ^-----pivot
 *    In this case, we split the input into 2 parts and each part has n/2 items
 *    So how much work is done in each layer?
 *                             #n   #comp
 *                     n        1 * (n-1)
 *                  /     \
 *                 n/2    n/2   2 * (n/2-1)
 *                /  \   /   \
 *              n/4 n/4 n/4 n/4 4 * (n/4-1)
 *                              each level does (2^i)*(n/2^i-1) work
 *                              and there are logn levels
 *    summation:
 *
 *      logn-1
 *    z i g m a (2^i)*(n/(2^i)-1) = nlog(n)-n+1 = O(nlogn)
 *       i=0 
 *
 *    let's see what if i=logn - 1: 2^ (logn-1)*(n/(2^(logn-1)-1) = n * n/n-1 = 0 --> this is the final level
 *    the way to solve this summation could go back and see mergesort video
 *
 */
void print(vector<int>& input){
	for(int i = 0; i < input.size(); i++)
		cout<<input[i]<<",";
	cout<<endl;
}
void swap(vector<int>& input, int x, int y){
	//for[4,5], pivot=5, and 4<=5, so we'll swap 4 with 4
	//the former 4 is input[i] and the later one is input[j]
	//in order to skip this kind of case, we add a value checking here
	if(input[x] == input[y])
		return;
	int tmp = input[x];
	input[x] = input[y];
	input[y] = tmp;
}
int partition(vector<int>& input, int left, int right){
	int pivot = input[right];
	int i = left - 1;
	for (int j = left; j < right; j++){
		if(input[j] <= pivot){
			i++;
			swap(input, i, j);
		}
	}
	swap(input, i+1, right);
	return i+1;
}
void _quicksort(vector<int>& input, int left, int right){
	//remember to check left and right
	if(left >= right)
		return;

	int pivot = partition(input, left, right);
	_quicksort(input, left, pivot-1);
	_quicksort(input, pivot+1, right);
}
void quicksort(vector<int>& input){
	_quicksort(input, 0, input.size()-1);
}
int main(void){
	int inputRaw[] = {5,4,1,8,7,10,6};
	vector<int> input(inputRaw, inputRaw+(sizeof(inputRaw)/sizeof(int)));
	quicksort(input);
	print(input);
	return 0;
}
