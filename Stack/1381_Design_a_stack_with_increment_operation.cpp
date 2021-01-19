class CustomStack {
    /* solution:
     * Use an extra vector to save the incremental value
     *   - inc[i] = the bottom i elements need to increase the value inc[i]
     * Example: 
     *     stack = [1,2]
     *     inc = [10, 20]
     *    this means:
     *         the bottom 2 elements need to + 20
     *         the bottom 1 element needs to + 10
     *    so when we pop the top, we have to return 2 + 20
     *    then increase the value in inc[0]
     *         --> inc[0] += inc[1] --> 10 + 20 = 30
     *    now the top is 1
     *    and when we pop the top, we have to return 1 + 30 = 31
     *
     * time complexity = O(1)
     * space complexity = O(1)
     */
public:
    CustomStack(int maxSize) {
        capacity = maxSize;
    }
    
    void push(int x) {
        //if stack is full, return
        if(stack.size() == capacity)
            return;
        stack.push_back(x);
        inc.push_back(0);
        
    }
    
    int pop() {
        //if stack is empty, return
       if(stack.empty())
           return -1;
        /* Example: we push 1,2, and 3 into the stack, and set increment(3,10)
         *  so stack and inc will look this:
         *          stack=[1,2,3]
         *          inc  =[0,0,10]
         *  the top element is 3 + inc[2] = 13
         *  then we set inc[1] = 10 --> this means the bottom 2 elements
         *            needs to increment 10 when we pop them out
         *  last, we pop the top element in stack and inc
         *  then return the answer
         *          stack=[1,2]
         *          inc  =[0,10]
         *  
         */
        int topIndex = stack.size() - 1;
        int ans = stack.back() + inc[topIndex];
        //remember to do the boundary check
        if(topIndex > 0)
            inc[topIndex-1] += inc[topIndex];
        stack.pop_back();
        inc.pop_back();
        return ans;
    }
    
    void increment(int k, int val) {
        int numOfElements = min(k, (int)stack.size());
        if(numOfElements > 0)
            inc[numOfElements - 1] += val;
    }
private:
    int capacity;
    vector<int> stack;
    vector<int> inc;
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
