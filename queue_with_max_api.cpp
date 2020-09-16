#include <iostream>
#include <queue>
#include <deque>
using namespace std;

/* we use a double ended queue to store the max.
 * for each value x in this deque,
 * x is the maximum value among all the values before x
 */
class solution {
	public:
		solution() {}
		void enqueue(int input) {
			myqueue.push(input);
			cout << "enqueue = " << myqueue.back()<<endl;
			while(!maxcache.empty() && input > maxcache.back()) {
				cout << "--maxcache pop back= "<<maxcache.back()<<endl;
				maxcache.pop_back();
			}
			maxcache.push_back(input);
			cout << "--maxcache push = "<<maxcache.back()<<endl;
		}
		void dequeue() {
			int curr = myqueue.front();
			cout << "dequeue = " << curr<<endl;
			if(curr == maxcache.front()) {
				cout << "--maxcache pop front= "<<maxcache.front()<<endl;
				maxcache.pop_front();
			}
			myqueue.pop();
		}
		void max() {
			cout << "max = "<<maxcache.front()<<endl;
		}
	private:
		queue<int> myqueue;
		deque<int> maxcache;
};
int main(void){
	solution mq;
/*
	mq.enqueue(1);
	mq.enqueue(2);
	mq.enqueue(-11);
	mq.max();         // outputs 2
	mq.enqueue(-12);
	mq.enqueue(100);
	mq.max();         // outputs 100
	mq.dequeue();     // outputs 1
	mq.dequeue();     // outputs 2
	mq.dequeue();     // outputs -11
	mq.max();         // outputs 100
*/
	mq.enqueue(10);
	mq.enqueue(8);
	mq.enqueue(2);
	mq.max();        // outputs 10
	mq.enqueue(6);
	mq.dequeue();
	mq.enqueue(7);
	mq.max();        // outputs 8
	mq.dequeue();
	mq.enqueue(1);
	mq.enqueue(9);
	mq.max();        // outputs 9
	mq.dequeue();
	mq.dequeue();
	mq.max();        // outputs 9
	return 0;
}
