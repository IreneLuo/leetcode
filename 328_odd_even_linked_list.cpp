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
    ListNode* oddEvenList(ListNode* head) {
        /* Solution 1:
         * 1. create two ListNode entity for linking odd and even node in head
         * 2. traverse head and link with tail_odd and tail_even
         * 3. set tail_odd to NULL, and connect tail_even with tail_odd
         * 4. point tail_even to the first node in head_even and return tail_even
	 * Time complexity = O(n)
	 * Space complexity = O(1)
         *
         *                                 |----- step 3 -------v             step 2
         * head_even ->  2 ->  4 ->  6 ----         head_odd -> 1 -> 3 -> 5 -> NULL
         *     ^                     ^                 ^                        ^
         * tail_even -- step 1 --> tail_even        tail_odd ---- step 1 ---> tail_odd
         */
        
        if (head == NULL)
            return NULL;

        ListNode head_odd, head_even;
        ListNode* tail_odd = &head_odd;
        ListNode* tail_even = &head_even;
        ListNode* ptr;
        int index = 0;

        for (ptr = head; ptr != NULL; ptr = ptr->next){
            if (index % 2) { //if odd
                tail_odd->next = ptr;
                tail_odd = ptr;
            } else {// if even
                tail_even->next = ptr;
                tail_even = ptr;
            }
            index++;
        }
        tail_odd->next = NULL;
        tail_even->next = head_odd.next;
        tail_even = head_even.next;
        return tail_even;
    }
};
