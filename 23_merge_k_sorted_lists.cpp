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
    /* solution: using heap
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
     * time complexity = O(nlogk)
     *  - push and pop each node: O(logk) + O(logk) = O(logk) (drop away constant)
     *  - iterate n times
     * space complexity = O(k)
     *  - we need k size for the heap
     */
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0)
            return NULL;

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
    }
};
