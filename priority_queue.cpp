#include <iostream>
#include <queue>
#include <vector>

using namespace std;
struct TreeNode{
	int val;
	int index;
	TreeNode(int x, int i): val(x), index(i) {}
};
struct mycompare{
	bool operator()(TreeNode a, TreeNode b){
		return a.val < b.val;
	}
};
int main (void){
	int input[] = {1,2,3,4,5,6,3};
	int size = sizeof(input)/sizeof(int);
	priority_queue<TreeNode, vector<TreeNode>, mycompare> pq;	
	for (int i = 0; i < size; i++){
		TreeNode node(input[i], i);
		pq.push(node);
		cout<<"heap top = "<<pq.top().val<<endl;
	}
	return 0;
}
