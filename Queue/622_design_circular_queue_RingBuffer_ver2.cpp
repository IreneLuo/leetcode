/* solution:
 * front: the index of the first item in this queue
 * rear: the index of a new item that could be placed in this queue
 * Scenario:
 *  1. Init: capacity = k    2. if full: r = (r+1) % capacity
 *   _ _ _                      1 2 3    so r will be back to 0 once
 *   ^                          ^        we enqueue 3
 *  f,r=0 (at index 0)         f,r=0     Note> the rear item is 3,
 *                                       so we return cq[capcity-1] instead of
 *                                       returning cq[rear-1] (rear-1<0 is invalid)
 *  3. if we dequeue the items
 *     until it's empty
 *     _ _ _ f = (f+1) % capacity
 *     ^     so f will be back to 0 once we dequeue 3
 *    f,r   
 */
class MyCircularQueue {
    int capacity;
    int front;
    int rear;
    int count;
    int* cq;
public:
    MyCircularQueue(int k) {
        capacity = k;
        front = rear = 0;
        count = 0;
        cq = new int[capacity];
    }
    
    bool enQueue(int value) {
        if(isFull())
            return false;
        cq[rear] = value;
        rear = (rear + 1) % capacity;
        ++count;
        return true;
    }
    
    bool deQueue() {
       if(isEmpty())
           return false;
        front = (front + 1) % capacity;
        --count;
        return true;
              
    }
    int Front() {
        if(isEmpty())
            return -1;
        return cq[front];
    }
    
    int Rear() {
        if(isEmpty())
            return -1;
        int rearIdx = (rear - 1) < 0 ? capacity - 1: rear - 1;
        return cq[rearIdx];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == capacity;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
