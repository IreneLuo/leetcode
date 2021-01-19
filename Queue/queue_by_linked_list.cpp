#include <iostream>
using namespace std;
struct Node{
	int val;
	Node* next;
	Node(int v): val(v), next(nullptr) {}
	Node(int v, Node* n): val(v), next(n) {}
};
class Queue{
public:
	Queue(): front(nullptr), back(nullptr), size(0) {};
	~Queue();
	void push(int val);
	void pop();
	int getFront();
	int getBack();
	bool isEmpty();
	int getSize();
	void print();
private:
	Node* front;
	Node* back;
	int size;
};
Queue::~Queue(){
	while(front!=nullptr)
		pop();
	front = nullptr;
	back = nullptr;
	size = 0;
}
void Queue::push(int val){
	//if push the first node
	if(isEmpty()){
		front = new Node(val);
		back = front;
		++size;
		return;
	}
	//otherwise, put the node after the last node(which back points to)
	Node* node = new Node(val);
	back->next = node;
	back = node;
	++size;
}
void Queue::pop(){
	if(isEmpty()){
		fprintf(stderr, "Queue is empty!\n");
		return;
	}
	Node* target = front;
	front = front->next;
	delete(target);
	--size;
}
int Queue::getFront(){
	if(isEmpty()){
		fprintf(stderr, "Queue is empty!\n");
		return -1;
	}
	return front->val;
}
int Queue::getBack(){
	if(isEmpty()){
		fprintf(stderr, "Queue is empty!\n");
		return -1;
	}
	return back->val;
}

/* Example:
 *  1        --> pop -->  x nullptr
 *  ^                     ^    ^
 *  front,back           back front
 *  Once we pop the only item in the stack
 *  front will point to a nullptr, which is 0
 */
bool Queue::isEmpty(){
	//return size == 0;
	return (front && back) == 0;
}
int Queue::getSize(){
	return size;
}
//just for checking if all the operations are correct
void Queue::print(){
	Node* curr = front;
	while(curr!=nullptr){
		cout<<curr->val<<", ";
		curr = curr->next;
	}
	cout<<endl;
}
int main(void){
	Queue myQueue;
	for(int i = 1; i < 5; i++)
		myQueue.push(i);
	cout<<"push items: ";
	myQueue.print();
	for(int i = 1; i < 5; i++)
		myQueue.pop();
	cout<<"pop items: ";
	myQueue.print();
	for(int i = 1; i < 3; i++)
		myQueue.push(i);
	cout<<"push items: ";
	myQueue.print();
	cout<<" get front = "<<myQueue.getFront()<<endl;
	cout<<" get back = "<<myQueue.getBack()<<endl;
	cout<<" get size = "<<myQueue.getSize()<<endl;
	return 0;
}
