/* solution 2:Balanced Binary Search Tree(Multiset for C++)
 * We use 2 pointers (left / right) to track the median position.
 * There are 4 situations for moving pointers
 * After adding a number x, if size of tree is odd
 *   1. if right <= x : left = right
 *        12 ->  1 2 2
 *        lr ->    lr   
 *   2. if x <= right: left = --right //not right = left
 *        12 -> 0 1 2
 *        lr      lr
 * After adding a number x, if size of tree is even
 *   3. if right <= x : ++right
 *       12 3 45   -> 123456
 *          lr          lr 
 *   4. if x <= right: --left
 *       12 3 45   -> 012345
 *          lr          lr
 *   time complexity: O(nlogn)
 *      - insert to the tree: O(logn)
 *      - move pointers: O(logn)
 *      - total n times
 *   space complexity: O(n)
 *  
 *  Reference: HuaHua's video
 */
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        left = bst.end();
        right = bst.end();
    }
    void addNum(int num) {
        if(bst.empty()){
            left = right = bst.insert(num);
            return;
        }
        //if bst is not empty
        bst.insert(num);
        //if bst size is odd
        if(bst.size() % 2){
            if(num >= *right)
                left = right;
            else
                left = --right;// left could be invalidate
        //if bst size is even   
        }else{
            if(num >= *right)
                ++right;
            else
                --left;
        }
    }
    
    double findMedian() {
        return (static_cast<double>(*left)+*right)/2;
    }
private:
    multiset<int> bst;
    multiset<int>::const_iterator left;
    multiset<int>::const_iterator right;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
