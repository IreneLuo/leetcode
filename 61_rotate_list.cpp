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
    ListNode* rotateRight(ListNode* head, int k) {
        /* Solution 1:
         * 1. get the size of the list
         * 2. calculate the steps = n-k-1 which means that the head pointer needs to move n-k-1 steps
         *    to find the new tail
         * 3. After finding the new tail, get the new head and let new tail points to null
         */
        if (head == NULL)
            return head;

        int size = 1;
        ListNode* tail = head;
        while(tail->next != NULL) {
            tail = tail->next;
            size++;
        }
        k = k % size;
        if (k == 0)
            return head;

        int steps = size - k - 1;

        ListNode* newtail = head;
        while(steps > 0) {
            newtail = newtail->next;
            steps--;
        }
        tail->next = head;
        ListNode* newhead = newtail->next;
        newtail->next = NULL;
        return newhead;
    }
};
