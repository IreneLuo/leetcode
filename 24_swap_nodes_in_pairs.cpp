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
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        /* solution 1:
         * 1. set ptr first, second to targets that we want to change
         * 2. set ptr next = second->next
         * 3. second->next = first
         *    first->next = next_first;
         *                         |--------v
         *    a->b->c->d->e->x ==> a<-b  c->d->e->x
         *    |  |  |              |  |  |
         *    f  s  n              f  s  n
         * 4. if next == NULL || next->next == NULL
         *    (if we don't set this rule, error will occur at step 5 when we
         *     meet [the end/the node before the end] of the list)
         *    f->next = next, return
         * 5. else move f, s, n to the next segment, back to 2
         *    first = next;
         *    second = next->next; 
         *                           (state for step 2- 4)
         *                                |-----|
         *    |--------v            |-----|--v  v
         *    a<-b  c->d->e->x  ==> a<-b  c<-d  e->x
         *          |  |                  |  |  |
         *         f,n s                  f  s  n
         *
         * Time complexity: O(n) //linear time
         * Space complexity: O(1) //constant space
         */
        if(head == NULL || head->next == NULL) 
            return head;

        ListNode* first = head;
        ListNode* second = first->next;
        ListNode* next_first;
        // important!
        // we need to move head to the right place first
        // otherwise, head will point to the first element forever!
        head = head->next;

        while(true) {
            next_first = second->next;
            second->next = first;
            // a->b->x or a->b->c->x
            if(next_first == NULL || next_first->next == NULL) {
                first->next = next_first;
                return head;
            }
            first->next = next_first->next;
            first = next_first;
            second = next_first->next;
        }
    }
};
