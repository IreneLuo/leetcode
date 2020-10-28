#include <iostream>
#include <stack>

using namespace std;

struct NODE{
	int order;
	NODE* jump;
	NODE* next;
	NODE(): order(-1), jump(NULL), next(NULL){};
};

class solution{
public:
	NODE* CreateList(){
		NODE* dummyHead = new NODE();
		NODE* dummyTail = new NODE();
		NODE* thelast = dummyHead;
		NODE* curr=dummyHead;
		dummyHead->next = dummyTail;
		//create a list which has 7 nodes
		for(int i = 0; i < 5; i++){
			NODE* node = new NODE();
			node->next = thelast->next;
			thelast->next = node;
			thelast = node;
		}
		//asign jump field and order field for each node, and the list looks like this:
		//          |-----------------v|-----------------v|--------------v
		//A(-1) -> B(-2) -> C(-3) -> D(-4) -> E(-5) -> F(-6) -> G(-7) -> x
		//  |----------------^|----------------^|----------------^|-----^
		int num = -1;
		while(curr->next != NULL){
			curr->jump = curr->next->next;
			curr->order = num;
			curr = curr->next;
			num--;
		}
		// the last one
		curr->jump = NULL;
		curr->order = num;
		return dummyHead;
	}
	/* time complexity = O(n)
	 * space complexity = O(n)
	 */
	NODE* SetJumpOrder_Iterative(NODE* head){
		int order = 0;
		stack<NODE*> myStack;
		myStack.push(head);
		while(!myStack.empty()){
			NODE* curr = myStack.top();
			myStack.pop();
			if(curr != NULL && curr->order < 0){
				curr->order = order;
				order++;
				// priority jump > next, so we must push next node first to
				// dealing with jump node when we pop a node out
				myStack.push(curr->next);
				myStack.push(curr->jump);
			}
		}
		return head;
	}
	/* time complexity = O(n)
	 * space complexity = O(n)
	 */
	NODE* SetJumpOrder_Recursive(NODE* head){
		_SetJumpOrder_Recursive(head, 0);
		return head;
	}

	//we traverse the list by using jump pointers and fill in the order
	int _SetJumpOrder_Recursive(NODE* head, int order){
		//we've increased 1 for order so we have to recover it since
		//we don't have to fill in the order for this node
		if(head == NULL || head->order > 0)
			return order-1;
		head->order = order;
		cout<<"curr order = "<<head->order<<endl;
		order = _SetJumpOrder_Recursive(head->jump, order+1);
		order = _SetJumpOrder_Recursive(head->next, order+1);
		return order;
	}

};
int main(void){
	solution sol;	
	NODE* head = sol.CreateList();
	//head = sol.SetJumpOrder_Recursive(head);
	head = sol.SetJumpOrder_Iterative(head);
	NODE* ptr = head;
	while(ptr!=NULL){
		cout<<ptr->order<<",";
		ptr = ptr->next;
	}
	cout<<endl;
	return 0;
}
