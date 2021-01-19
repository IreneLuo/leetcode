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
    ListNode* reverseList(ListNode* head) {
        /* method 1: iteration
         * We use prev, curr, and nextTemp 3 pointers to notify the postions of
         * key list nodes. Everytime, we change curr->next = prev and move 3
         * pointers forward until we meet the end.
         * 
         * time complexity = O(n)
         * space complexity = O(1)
         */
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while(curr){
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        };
        return prev;
        /* method 2: recursion
         *  1. make recursive calls until we find the last item
         *  2. while we find the last item, return the last item
         *     (since it's the head of the reverse list)
         *  3. after recursive calls, make the next item point to curr item
         *     and curr item point to a nullptr then return the head of this reverse list
         * time complexity = O(n)
         * space complexity = O(n) //implicit stack space
         */
        /*
        if(!head || !head->next) return head;
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
        */
    }
};
