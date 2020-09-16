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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        /* Solution:
         * 1. create a DummyHead Node for the answer list
         * 2. let ptr1, ptr2 traverse over l1, l2 list
         *     a. ans = ptr1->val + ptr2->val + carry
         *     b. carry = ans / 10;
         *     c. create a new node and store the val = ans % 2
         * Time complexity: O(m+n)
         * Space complexity: O(max(m,n))
         */
        ListNode DummyHead(0);
        ListNode* ptr = &DummyHead;
        ListNode* ptr1 = l1;
        ListNode* ptr2 = l2;
        int ans = 0;
        int carry = 0;
        while(ptr1 != NULL || ptr2 != NULL) {
            ans = 0;
            if (ptr1 != NULL) {
                ans += ptr1->val;
                ptr1 = ptr1->next;
            }

            if(ptr2 != NULL) {
                ans += ptr2->val;
                ptr2 = ptr2->next;
            }

            ans += carry;
            carry = ans / 10;
            ptr->next = new ListNode(ans % 10);
            ptr = ptr->next;
        }
        if(carry)
            ptr->next = new ListNode(carry);

        return DummyHead.next;
    }
