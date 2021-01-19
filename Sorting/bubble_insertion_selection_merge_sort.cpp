#include <iostream>
#include <vector>

using namespace std;
void print(vector<int> input){
	int i;
	for(i = 0; i < input.size() - 1; i++)
		cout<<input[i]<<", ";
	cout<<input[i]<<endl;
}
//every time, push the maximum value to the right until hit the limit
//then again push the maximum value to the right unitil hit the limit-1
void bubble_sort(vector<int> input){
	int idx_limit = input.size();
	while(idx_limit > 1){
		for(int j = 0; j < idx_limit - 1; j++){
			if(input[j] > input[j+1]){
				int temp = input[j];
				input[j] = input[j+1];
				input[j+1] = temp;
			}
		}
		print(input);
		idx_limit--;
	}
}
// every time, insert current value to the previous value if current value is bigger than that
// do this operation until there's no previous value
// then keep looking the next value
void insertion_sort(vector<int> input){
	for(int i = 0; i < input.size(); i++){
		int target = input[i];
		int prev = i - 1;
		while(prev >= 0 && input[prev] > target){
			input[prev+1] = input[prev];
			prev--;
		}
		input[prev+1] = target;
	}
	print(input);
}
// every time, select a smallest value and insert to the left
void selection_sort(vector<int> input){
	int min_idx;
	int i;
	int j;
	for(i = 0; i < input.size(); i++){
		min_idx = i;
		for(j = i + 1; j < input.size(); j++){
			//find the minimum value from j+1 to the end
			if(input[min_idx] > input[j]){
				min_idx = j;
			}
		}
		int temp = input[i];
		input[i] = input[min_idx];
		input[min_idx] = temp;
		cout<<"i = "<<i<<": ";
		print(input);
	}
}
void merge(vector<int>& input, int left, int mid, int right){
	vector<int> leftpart(input.begin()+left, input.begin()+mid+1);
	vector<int> rightpart(input.begin()+mid+1, input.begin()+right+1);
	int leftidx = 0;
	int rightidx = 0;
	int curridx = left;
	while(leftidx < leftpart.size() && rightidx < rightpart.size()){
		if(leftpart[leftidx] < rightpart[rightidx])
			input[curridx++] = leftpart[leftidx++];
		else
			input[curridx++] = rightpart[rightidx++];
	}
	//input.insert(input.begin()+curridx, leftpart.begin()+leftidx, leftpart.end());
	while(leftidx < leftpart.size())
		input[curridx++] = leftpart[leftidx++];
	while(rightidx < rightpart.size())
		input[curridx++] = rightpart[rightidx++];
}
void mergesort(vector<int>& input, int left, int right){
	if(left < right){
		int mid = left + (right - left) / 2;
		mergesort(input, left, mid);
		mergesort(input, mid+1, right);
		merge(input, left, mid, right);
	}
}
int main(void){
	int test[] = {8, 9, 10, 1, 4, 20, 3, 6, 5};
	vector<int> input (test, test + sizeof(test)/sizeof(int));
//	selection_sort(input);
//	insertion_sort(input);
//	bubble_sort(input);
	mergesort(input, 0, input.size()-1);
	print(input);
	return 0;
}
