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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        /* solution 1:
         * 1. create a DummyHead Node and points to head
         *    DH->1->2->3->4->5->x
         *
         * 2. find the initial locations of right pointer
         *    DH->1->2->3->4->5->x (n = 2)
         *        r --> r (r will move n times)
         *
         * 3. set the left pointer (we set a window from left to right to avoid out of bound for accessing
         *                          left->next->next)
         *    DH->1->2->3->4->5->x (n = 2)
         *   [ l        r ]
         *
         * 4. slide the window(left to right) until right pointer = null
         *    DH->1->2->3->4->5->x (n = 2)
         *            [ l        r ] when r == NULL, the node next to left is our target to remove!
         *
         * 5. remove the node
         * note) What's the relationship between window size and n?
         *       window size = n + 1(DH) + 1(NULL)
         *       this window size allows us to get the node before target when right = null
         * note) Why do we need DummyNode?
         *       To deal with the edge case like 1->x. This case only has 1 element so we need to create a   
         *       dummy node before head to remove it.
         *
         * Time complexity:O(n)
         * Space complexity: O(1)
         */
        ListNode DummyNode(-1);
        ListNode* left;
        ListNode* right;

        DummyNode.next = head;
        right = head;
        while(n > 0) {
            right = right->next;
            n--;
        }
        left = &DummyNode;
        while(right != NULL){
            right = right->next;
            left = left->next;
        }
        left->next = left->next->next;
        return DummyNode.next;
    }
};
