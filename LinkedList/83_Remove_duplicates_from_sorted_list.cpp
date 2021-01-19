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
    /* solution: 
     *  1. iterate over the list
     *  2. compare prev node with curr node
     *  3. if prev == curr
     *     we let prev->next point to curr->next
     *     and move curr to the next node
     * time complexity = O(n)
     * space complexity = O(1)
     */
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next)
            return head;
        //since the list has been sorted, so we don't have to use a set to
        //check if a node is dup or not
        //set<int> history;
        ListNode* curr = head->next;
        ListNode* prev = head;
        //history.insert(curr->val);
        while(curr){
            //if(history.find(curr->val) != history.end()){
            if(curr->val == prev->val){
                //do not delete duplicate item here to save more time
                //ListNode* dup = curr;
                prev->next = curr->next;
                curr = curr->next;
                //delete(dup);
            }else{
                //history.insert(curr->val);
                prev = curr;
                curr = curr->next;
            }
        }
        return head;
    }
};
