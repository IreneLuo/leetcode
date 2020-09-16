class MyCircularQueue {
public:
    int* queue;
    int size = 0;
    int tail_pos = -1;
    int head_pos = -1;
    int count = 0;
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        queue = new int[k];
        size = k;
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull())
            return false;

        // if there's only 1 item in the queue, then enqueue->dequeue will occur
        // error if we don't change head_pos from -1 to 0.
        if(tail_pos == -1)
            head_pos = 0;

        tail_pos = (tail_pos + 1) % size;
        *(queue + tail_pos) = value;
        count++;
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty())
            return false;
        head_pos = (head_pos + 1) % size;
        count--;
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        if (isEmpty())
            return -1;

        return *(queue + head_pos);
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        if (isEmpty())
            return -1;

        return *(queue + tail_pos);
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return (count == 0);
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return (count == size);
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
