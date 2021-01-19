/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        /* solution 1 : use set
         * 1. create a set to store the node one by one
         * 2. if new node has already stored in the set,
         *    it means that we find the cycle.
	 *  time complexity = O(n)
	 *  space complexity = O(n)
         */
/*
        set<ListNode*> myset;
        ListNode* ptr = head;
        while(ptr != NULL) {
            if(myset.find(ptr) != myset.end())
                return true;
            myset.insert(ptr);
            ptr = ptr->next;
        }
        return false;
*/
        /* solution 2 : use fast/slow pointer
	 * Why will fast/slow meet? see HuaHua's video
         */
        ListNode* fast = head;
        ListNode* slow = fast;
        while(fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                return true;
        }
        return false;
    }
};
