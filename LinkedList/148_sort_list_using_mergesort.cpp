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
    /* solution 2: Merge Sort(top-down)
     *  time complexity = O(nlogn)
     *  space complexity = O(logn) //stack depth
     */
    ListNode* sortList(ListNode* head) {
        return mergesort(head);
    }
    ListNode* mergesort(ListNode* head){
        if(head == NULL || head->next == NULL)
            return head;

        //find the middle node
        ListNode* mid = getMid(head);
        //split the list
        ListNode* listHead = mergesort(head);
        ListNode* listMid = mergesort(mid);
        //merge them
        return merge(listHead, listMid);
    }
    /* Get the middle node of a list: 
     * we let pointer slow move 1 step at a time,
     * pointer fast move 2 steps at a time
     * until pointer fase is NULL we stop the loop
     * and the place where pointer slow points to
     * is the middle of this list.
     * (we use pointer prevSlow to remember the node before slow,
     *  so we can cut off this list into two sublists)
     * ex:
     *    A B C D E F G H
     * 1. p s f
     * 2.   p s   f
     * 3.     p s     f
     * 4.       p s       f
     * 
     */
    ListNode* getMid(ListNode* head){
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prevSlow = head;
        
        while(fast != NULL && fast->next != NULL){
            prevSlow = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prevSlow->next = NULL;
        return slow;
    }
    /* Merge two lists
     * We traverse all the nodes on two lists, and
     * find a smaller one then add to our final list (which is pointed by endOfMergeList)
     * 
     * ex: list A: 1->5, list B: 2 -> 6 -> 8
     *   Round    comp     ans
     *     1       1<2      dH->1
     *     2       5>2      dH->1->2
     *     3       5<6      dH->1->2->5
     *     4                dH->1->2->5->6->8 (we stop comparison since no more items in listA)
     *                                        (and we append the rest of listB to the endOfMergeList)
     */
    ListNode* merge(ListNode* list1, ListNode* list2){
        //always points to the head of our merged list
        ListNode* dummyHead = new ListNode();
        //points to the last node in our merged list
        ListNode* endOfMergeList = dummyHead;
        while(list1 != NULL && list2 != NULL){
            if(list1->val < list2->val){
                endOfMergeList->next = list1;
                list1 = list1->next;
            }else{
                endOfMergeList->next = list2;
                list2 = list2->next;
            }
            endOfMergeList = endOfMergeList->next;
        }
        if(list1 != NULL)
            endOfMergeList->next = list1;
        if(list2 != NULL)
            endOfMergeList->next = list2;
        return dummyHead->next;
    }
};
