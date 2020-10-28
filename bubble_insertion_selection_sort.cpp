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
	while(idx_limit > 0){
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
	int i;
	int curr_idx;
	for(i = 1; i < input.size(); i++){
		curr_idx = i;
		while(curr_idx > 0 && input[curr_idx - 1] > input[curr_idx]){
			int temp = input[curr_idx];
			input[curr_idx] = input[curr_idx - 1];
			input[curr_idx - 1] = temp;
			curr_idx--;
		}
		print(input);
	}
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
int main(void){
	int test[] = {8, 9, 10, 1, 4, 20, 3, 6, 5};
	vector<int> input (test, test + sizeof(test)/sizeof(int));
//	selection_sort(input);
//	insertion_sort(input);
	bubble_sort(input);
	return 0;
}
