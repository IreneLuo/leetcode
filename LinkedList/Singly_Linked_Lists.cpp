#include <iostream>
#include <stack>

 /* Implement some rudimentary operations for linked list.
  * Operations are as follows:
  * (1~5 are for Leetcode 707. Design a Linked List,
  *  others are the practice on BackToBackSWE)
  * 1. addToHead
  * 2. addToTail
  * 3. addAtIndex
  * 4. deleteAtIndex
  * 5. get
  * 7. reverse_list
  * 8. print
  * 9. reverse_print
  */
using namespace std;
class MyLinkedList{
public:
	MyLinkedList(){
		head = nullptr;
		tail = head;
		size = 0;
	}
	~MyLinkedList(){
		while(head){
			Node* curr = head;
			head = head->next;
			delete(curr);
		}
		head = nullptr;
		tail = head;
		size = 0;
	}
	void addAtHead(int val){
		head = new Node(val, head);
		if(size == 0)
			tail = head;
		++size;
	}
	void addAtTail(int val){
		Node* node = new Node(val);
		if(size == 0){
			head = tail = node;
		}else{
			tail->next = node;
			tail = node;
		}
		++size;
	}
	/* Add a node of value val before the index-th node in the linked list.
	 * If index equals to the length of linked list, the node will be appended
	 * to the end of linked list. If index is greater than the length, the node
	 * will not be inserted. */
	void addAtIndex(int index, int val){
		//0->1->2
		int cnt = index - 1;
		Node* p = head;
		if(index > size || index < 0){
			return;
		}else if(index == 0){
			addAtHead(val);
			return;
		}else if(index == size){
			addAtTail(val);
			return;
		}else{
			while(cnt--)
				p = p->next;
			Node* node = new Node(val, p->next);
			p->next = node;
			++size;
		}
	}
	void deleteAtIndex(int index){
		if(index >= size || index < 0) return;
		//Node* dummy = new Node(0, head);
		Node dummy(0, head);
		Node* p = &dummy;
		int cnt = index;
		while(cnt){
			p = p->next;
			--cnt;
		}
		Node* curr = p->next;
		p->next = curr->next;
		if(index == 0) head = head->next;
		if(index == size-1) tail = p;
		delete(curr);
		//delete(dummy);
		--size;
	}
	/*
	 * Get the value of the index-th node in the linked list.
	 * If invalid, return -1
	 */
	int get(int index){
		if(index >= size || index < 0) return -1;
		Node* p = head;
		while(index--)
			p = p->next;
		return p->value;
	}
	void reverse_list(){
		Node* prev = nullptr;
		Node* curr = head;
		Node* last;
		tail = head;
		while(curr){
			last = curr->next;
			curr->next = prev;
			prev = curr;
			curr = last;
		}
		head = prev;
	}
	void print(){
		Node* p = head;
		while(p){
			cout<<p->value<<", ";
			p = p->next;
		}
		cout<<endl;
	}
	void reverse_print(){
		stack<int> s;
		Node* p = head;
		while(p){
			s.push(p->value);
			p = p->next;
		}
		while(!s.empty()){
			cout<<s.top()<<", ";
			s.pop();
		}
		cout<<endl;
	}
private:
	struct Node{
		int value;
		Node* next;
		Node* prev;
		Node(int v): value(v), next(nullptr), prev(nullptr){};
		Node(int v, Node* n): value(v), next(n){};
		Node(int v, Node* n, Node* p): value(v), next(n), prev(p){};
	};
	Node* head;
	Node* tail;
	int size;
};
int main(void){
       	MyLinkedList* obj = new MyLinkedList();
 	obj->addAtTail(3);
 	obj->addAtHead(2);
 	obj->addAtHead(1);
	obj->addAtIndex(0,5);
	obj->addAtIndex(4,5);
	obj->addAtIndex(3,5);
 	obj->addAtTail(4);
	obj->print();
	cout<<"get value : "<<obj->get(3)<<endl;

	cout<<"delete index 4"<<endl;
 	obj->deleteAtIndex(4);
	obj->print();

	cout<<"delete index 0"<<endl;
 	obj->deleteAtIndex(0);
	obj->print();

	cout<<"reverse print"<<endl;
	obj->reverse_print();

	cout<<"reverse the list"<<endl;
	obj->print();
	return 0;
}
