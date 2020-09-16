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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        /* solution 1: throw the node to forward
         *  1. set nbrs to the previous node of start(m)
         *  2. set temp to the next node of start and throw it to the head
         *  ex: 1 -> 2 -> 3 -> 4 -> 5 -> x (3,5)
         *           |    |    |
         *         nbrs start temp
         *                
         *      1 -> 2--v  3 -> 5 -> x  (throw 4 to the next of 2)
         *           |  4--^    |    |
         *         nbrs       start temp
         */
        ListNode* nbrs; //node before start
        ListNode* start;
        ListNode dummynode(-1);
        ListNode* temp;
        int pos = 1;

        if(head == NULL)
            return NULL;

        dummynode.next = head;
        nbrs = &dummynode; //not nbrs = head, otherwise we'll get a wrong pos
        while(pos < m) {
            nbrs = nbrs->next;
            pos++;
        }

        start = nbrs->next;
        while(m < n) {
            temp = start->next;
            start->next = temp->next; // cut off the temp
            temp->next = nbrs->next; // forward the temp
            nbrs->next = temp;
            m++;
        }
        return dummynode.next;
    }
};
