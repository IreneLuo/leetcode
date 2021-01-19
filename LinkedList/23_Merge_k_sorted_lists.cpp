/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct mycompare{
    //min heap
    // check whether curr->val is smaller than parent's, if yes, return true to swap
    bool operator()(ListNode* parent, ListNode* curr){
        return (curr->val) < (parent->val);
    }
};
class Solution {
public:
    /* solution 1: using heap
     * 1. create a heap(pq) and a vector(ans)
     * 2. push the head of each list into the heap
     * 3. pop the top item and push it into ans
     * 4. then push the next item of the pop item into the heap
     * 5. keep doing step 3,4 until we push all the items from the lists
     *
     * ex:
     *       [1,4,5] [1,3,4] [2,6]     heap           ans
     *  1.    ^       ^       ^       [1,1,2] -> pop   1
     *  2.      ^     ^       ^       [1,2,4] -> pop   1
     *  3.      ^       ^       ^     [2,4,3] -> pop   2
     *  4.              ^       ^     [4,3,6] -> pop   3
     *  5.      ^         ^     ^     [4,6,4] -> pop   4
     *  6.        ^       ^     ^     [6,4,5] -> pop   4
     *  7.        ^             ^     [6,5]   -> pop   5
     *  8.                      ^     [6]     -> pop   6
     * time complexity = O(nklogk)
     *  - push and pop each node: O(logk) + O(logk) = O(logk) (drop away constant)
     *  - lists.length = k
     *  - number of items in a list = n
     *    --> total nk items
     * space complexity = O(k) + O(n)
     *  - heap size = k = lists.length
     *  - ans size = O(n) if considered
     *
     * Solution 2: Divide and conquer (Mergesort)
     * (similar: Leetcode 21 merge two sorted list)
     * time complexity = O(nklogk)
     * space complexity = O(logk) -> O(1)
     *
     * Example: lists.length(k) = 5 --> we use l0 ~ l4 to represent 5 lists
     *          each list has n items
     *               l0-4
     *               /  \
     *           l0-2   l3-4      --> we divide the number of lists into half at each level
     *            / \    / \          so level = log5 = logk
     *        l0-1  l2  l3 l4     --> total nk items
     *         / \                ==> time complexity = nklogk
     *        l0 l1               ==> space complexity = logk (stack depth)
     *   Note: if we don't use recursion, we could decrease the space to O(1)
     *
     */
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0)
            return NULL;

#if 0
        /* solution 1 */
        priority_queue<ListNode*, vector<ListNode*>, mycompare> pq;
        ListNode* DummyHead;
        ListNode* tail;

        for(int i = 0; i < lists.size(); i++){
            if(lists.at(i) != NULL)
                pq.push(lists.at(i));
        }

        DummyHead = new ListNode(0);
        tail = DummyHead;
        while(pq.size() > 0){
            ListNode* ptr = pq.top();
            pq.pop();
            tail->next = ptr;
            tail = tail->next;
            if(ptr->next != NULL)
                pq.push(ptr->next);
        }
        return DummyHead->next;
#endif
        /* solution 2 */
        return divide(lists, 0, lists.size()-1);
    }

    /* solution 2 */
    ListNode* divide(vector<ListNode*>& lists, int left, int right){
        if(left == right) return lists[left];
        if(left + 1 == right) return merge(lists[left], lists[right]);
        int mid = left + (right - left) / 2;
        ListNode* leftlist = divide(lists, left, mid);
        ListNode* rightlist = divide(lists, mid+1, right);
        return merge(leftlist, rightlist);
    }
    /* solution 2 */
    ListNode* merge(ListNode* left, ListNode* right){
        ListNode DummyHead(0);
        ListNode* tail = &DummyHead;
        while(left!=NULL && right!=NULL){
            if(left->val > right->val) swap(left, right);
            tail->next = left;
            left = left->next;
            tail = tail->next;
        }
        tail->next = (left==NULL) ? right : left;
        return DummyHead.next;
    }
};
