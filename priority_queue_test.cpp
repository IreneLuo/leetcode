#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct NODE{
	int num;
	NODE(int n): num(n) {};
};
class myComp{
public:
	bool operator() (const NODE* a, const NODE* b){
		return a->num > b->num;
	}
};
int main(void){
	priority_queue<NODE*, vector<NODE*>, myComp> pq;
	vector<NODE*> nodelist;
	for(int i = 0; i < 10; i++){
		NODE* node = new NODE(i);
		nodelist.push_back(node);
		pq.push(node);
	}

	int count = 0;
	while(!pq.empty()){
		cout<<pq.top()->num<<", ";
		if(count < 7)
			nodelist[count+2]->num = 100+count;
		pq.pop();
		count++;
	}
	return 0;
}
