/* Implement a stack by using array
 * Basic operations:
 *  1. top
 *  2. push
 *  3. pop
 *  4. is empty?
 *  5. is full?
 *  6  get size
 *  7. doubled capacity
 *  Reference:
 *  https://groups.csail.mit.edu/graphics/classes/6.837/F04/cpp_notes/stack2.html
 *  http://alrightchiu.github.io/SecondRound/stack-yi-arrayyu-linked-listshi-zuo.html
 */
#include <iostream>
class Stack{
public:
	Stack(int cap);
	~Stack();
	void Push(int value);
	void Pop();
	int Top();
	bool IsEmpty();
	bool IsFull();
	int GetSize();
	void Doubledsize();
private:
	int capacity;
	int top;
	int* stack;
};
Stack::Stack(int cap){
	capacity = cap;
	stack = new int[capacity];
	top = -1;
}
Stack::~Stack(){
	top = -1;
	capacity = 0;
	delete(stack);
}
void Stack::Push(int value){
	if(IsFull()){
		fprintf(stderr, "The stack is full, cannot push %d!\n", value);
		return;
	}
	stack[++top] = value;
	fprintf(stdout, "push %d!\n", stack[top]);
}
void Stack::Pop(){
	if(IsEmpty()){
		fprintf(stderr, "The stack is empty!\n");
		return;
	}
	--top;
}
int Stack::Top(){
	if(IsEmpty()){
		fprintf(stderr, "The stack is empty!\n");
		return -1;
	}
	return stack[top];
}
bool Stack::IsEmpty(){
	return top == -1;
}
bool Stack::IsFull(){
	return top == (capacity - 1);
}
int Stack::GetSize(){
	return top+1;
}
void Stack::Doubledsize(){
	capacity *= 2;
	int* erase = stack;
	stack = new int[capacity];
	for(int i = 0; i <= top; i++)
		stack[i] = erase[i];
	delete(erase);
}

using namespace std;
int main(void){
	Stack mystack(5);
	for(int i = 1; i <= 6; i++){
		mystack.Push(i);
	}
	cout<<"stack size = "<<mystack.GetSize()<<endl;
	mystack.Pop();
	cout<<"after pop(), stack size = "<<mystack.GetSize()<<endl;
	mystack.Push(10);
	cout<<"Stack top = "<<mystack.Top()<<endl;
	mystack.Doubledsize();
	for(int i = 6; i <= 12; i++){
		mystack.Push(i);
	}
	return 0;
}
