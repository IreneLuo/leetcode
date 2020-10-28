/* solution:Using heap
 * 1. put the values into two heap, one is upperHalf, another is lowerHalf
 * 2. if the value is smaller than the min(upperHalf)=upperHalf.top(), push it into the lowerHalf
 *    otherwise push it into the upperHalf
 * 3. balance both heap every time after inserting a value
 *    the method is : push the top item of one heap into another heap
 *    the principle is keeping the numbers of upperHalf higher or equal than lowerHalf
 * 4. return the top of the upperHalf is the numbers of upperHalf is higher than lowerHalf
 *    return the top of both heap is the numbers of both heap are equal
 *  ex: insert 10,9,8,7,6
 *      lowerHalf        upperHalf
 *   1.                     10           //first item push to upperHalf
 *   2.   9                 10           // 9 < 10 push to lowerHalf
 *   3   8,9                10           // 8 < 10 push to lowerHalf
 *   4.   8                 9,10         // balance both heaps
 *   5.  7,8                9,10         // 7 < 9 push to lowerHalf --> at this moment, the median = (8 + 9) / 2
 *   6. 6,7,8               9,10         // 6 < 9 push to lowerHalf
 *   7.  6,7                8,9,10       // balance both heaps      --> at this moment, the median = 8
 *
 *   time complexity: 3n * log(n/2) = O(nlogn)
 *     - insert: log(n/2) for n times (each heap will have maximum n/2 items, so insert an item needs log(n/2))
 *     - balanced(push/pop): 2*log(n/2) for n times (push action needs to pop-up the value to the root--> log(n/2), pop action needs to pop-down-->log(n/2))
 *     - get the answer: O(1)
 *   space complexity: O(n)
 */
class MedianFinder {
public:
    /** initialize your data structure here. */
    struct mycompare_less{
        bool operator()(int parent, int curr){
            // am I smaller than my parent? if yes, return true and swap
            return parent > curr;
        }
    };
    // min heap
    priority_queue<int, vector<int>, mycompare_less> upperHalf;
    // max heap
    priority_queue<int> lowerHalf;

    MedianFinder() {
        
    }
    /* Try to keep both heap in a balanced state.
     * A balanced state contains two situations
     * 1. num(upperHalf) == num(lowerHalf) + 1
     * 2. num(upperHalf) == num(lowerHalf)
     */
    void balanced(){
        //ex: if number of upperHalf = 2, number of lowerHalf = 0
        // push 1 value to the lowerHalf, make the numbers of each heap becomes 1
        if(upperHalf.size() == lowerHalf.size() + 2){
            lowerHalf.push(upperHalf.top());
            upperHalf.pop();
        // ex: if number of upperHalf = 1, number of lowerHalf = 2
        // push 1 value to the upperHalf, make the numbers of each heap becomes 2 and 1
        }else if(upperHalf.size() == lowerHalf.size() - 1){
            upperHalf.push(lowerHalf.top());
            lowerHalf.pop();
        }
    }
    void addNum(int num) {
        // if upperHalf is empty, push value into it
        if(upperHalf.empty()){
            upperHalf.push(num);
        // if num < the top of upperHalf, push value into the lowerHalf
        // otherwise, push it into the upperHalf
        }else{
            if(num < upperHalf.top())
                lowerHalf.push(num);
            else
                upperHalf.push(num);
        }
        //balance the lowerHalf and upperHalf Heap
        balanced();
    }
    
    double findMedian() {
        if(upperHalf.size() == lowerHalf.size() + 1)
            return upperHalf.top();
        else
            return (double)(upperHalf.top() + lowerHalf.top()) / (double)2;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
