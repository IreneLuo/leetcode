/* Implementation of a queue by using array
 *       front: the idx of the first item in this queue
 *       back: the idx of a new item that should be placed (in the future)
 *       capacity: the limit size of a queue
 *       Example:
 *       item: 1 2 3 4 5     capaicty = 5
 *             ^         ^
 *            front     back
 *
 * Problem:
 *        Scenario: 1.  we enqueue the items until the queue is full
 *         	 	--> front=0, back=capacity
 *                  2.  then dequeue the items until the queue is empty
 *                      --> front==back
 *                  3.  now, we want to enqueue some items but fail!
 *                      because in the push(), it'll check if back==capacity
 *                      if yes, then the queue is considered to be fulled
 * Solution:
 *       If we want to fix this problem, we use use two ways:
 *       1. resize the queue if it's full, and copy all the data from old queue to a new queue
 *       	Disadvantages: waste of memory space(after pop) + cost for resize a new chunk of memory
 *       2. move all the datas forward a step while we pop the front item
 *       	Disadvantages: spend O(n) time when pop() an item instead of O(1)
 *          idx	0 1 2 3 4 5           0 1 2 3 4
 *       	1 2 3 4 5     pop()   2 3 4 5
 *       	^         ^    -->    ^       ^
 *            front      back       front    back
 *
 *  solutions are in push() and pop()
 */
#include <iostream>
using namespace std;
class Queue{
private:
	int front;
	int back;
	int capacity;
	int *q;
public:
	Queue(int s);
	~Queue();
	void push(int value);
	void pop();
	int getBack();
	int getFront();
	int getSize();
	bool isEmpty();
	bool isFull();
	void resize();
	void print();
};
Queue::Queue(int cap){
	front = 0;
	back = 0;
	capacity = cap;
	q = new int[capacity];
}
Queue::~Queue(){
	delete(q);
	front = 0;
	back = 0;
	capacity = 0;
	q = nullptr;
}
void Queue::push(int value){
	/* If the queue is full, resize the queue by
	 * allocating a chunk of memory(size of capacity*2)
	 */
	if(isFull()){
		//ver2:
		fprintf(stderr, "Queue is empty\n");
		return;
		//ver1:
		//resize();
	}
	q[back++] = value;
}
void Queue::pop(){
	if(isEmpty()){
		fprintf(stderr, "Queue is empty\n");
		return;
	}
	/* ver1: Only move pointer "front" to the next item.
	 *       However, q[front] is still exist, but it's been erased
	 *       from user's point of view
	 */
	//front++;

	// ver2
	for(int i = front + 1; i < back; i++)
		q[i-1] = q[i];
	--back;
}
int Queue::getBack(){
	if(isEmpty()){
		fprintf(stderr, "Queue is empty\n");
		return -1;
	}
	return q[back-1];
}
int Queue::getFront(){
	if(isEmpty()){
		fprintf(stderr, "Queue is empty\n");
		return -1;
	}
	return q[front];
}
int Queue::getSize(){
	return back-front;
}
bool Queue::isEmpty(){
	return (front == back);
}
bool Queue::isFull(){
	return (back == capacity);
}
void Queue::resize(){
	int* erase = q;
	capacity = capacity << 1;
	q = new int[capacity];
	memcpy(q, erase, sizeof(int) * (capacity >> 1));
}
void Queue::print(){
	for(int i = front; i < back; i++)
		cout<<q[i]<<", ";
	cout<<endl;
}
int main(void){
	Queue myQueue(5);
	for(int i = 1; i < 8; i++)
		myQueue.push(i);
	cout<<"push items: ";
	myQueue.print();
	for(int i = 1; i < 8; i++)
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
