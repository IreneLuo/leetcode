class MyQueue {
    /* we use two stacks to push and retrieve the item like queue.
     * 1. For the push stack: we always push item into this stack.
     *    the top item of the push stack is the tail of a queue.
     * 2. For the pop stack: we always pop item from this stack
     *    when we want to pop/peek the front item of the queue.
     *    When the pop stack is empty, we pop the item from the
     *    push stack and push it into the pop stack. Hence, the
     *    top item in the pop stack will be the front of a queue.
     *
     *    ex: we push 1,2,3 into the push_stack
     *        --> queue.back = push_stack.top = 3
     *        when we pop 3,2,1 and push them into the pop_stack
     *        --> queue.front = pop_stack.top = 1
     *
     *    | 3 |      |   |       |   |     | 1 |
     *    | 2 |      |   |   --> |   |     | 2 |
     *    | 1 |      |   |       |   |     | 3 |
     *    |---|      |---|       |---|     |---|
     *   push_stack pop_stack push_stack  pop_stack
     */
private:
    stack<int> pop_stack;
    stack<int> push_stack;
public:
    void move_item_to_pop_stack() {
        while(!push_stack.empty()) {
            pop_stack.push(push_stack.top());
            push_stack.pop();
        }
    }
    /** Initialize your data structure here. */
    MyQueue() {
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        push_stack.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if(pop_stack.empty())
            move_item_to_pop_stack();
        int ret = pop_stack.top();
        pop_stack.pop();
        return ret;
    }
    
    /** Get the front element. */
    int peek() {
        if(pop_stack.empty())
            move_item_to_pop_stack();

        return pop_stack.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return (push_stack.empty() && pop_stack.empty());
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
