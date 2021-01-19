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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        /* solution 1: iterative
         *  1. we have pointer l1 and l2 that point to those two lists seperately
         *  2. compare l1 value with l2 value and save a smaller one to the answer list
         *  3. move l1 to the next item if l1's value is smaller
         *     move l2 to the next item if l2's value is smaller
         *  4. go to step 2 again, until one of a list or both lists are finished
         *  time complexity = O(n)
         *  space complexity = O(1)
         */
        ListNode DummyHead(0);
        ListNode* tail = &DummyHead;
        while(l1 && l2){
            if(l1->val < l2->val){
                tail->next = l1;
                l1 = l1->next;
            }else{
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return DummyHead.next;
        /* solution 2: Recursive
         *  merge:
         *    if l1 is null, return l2
         *    if l2 is null, return l1
         *    if l1[0] < l2[0], return l1[0] + merge(l1[1:], l2[0:])
         *    else return l2[0] + merge(l1[0:], l2[1:])
         *  Note that in our code
         *  we only change the pointer of next for each node to reach our goal
         *
         *  Ex: l1 = [1,2,4], l2 = [1,3,4]
         *     merge([1,2,4], [1,3,4]) = [1] + merge([2,4], [1,3,4])
         *                             = [1] + [1] + merge([2,4], [3,4])
         *                             = [1] + [1] + [2] + merge([4], [3,4])
         *                             = [1] + [1] + [2] + [3] + merge([4], [4])
         *                             = [1] + [1] + [2] + [3] + [4] + merge([4])
         *                             = [1] + [1] + [2] + [3] + [4] + [4]
         *
         *  time complexity =  O(n)
         *    - 1 + T(n-1)
         *  space complexity = O(1)
         *
         *  If we do array operations instead of linkedlist here
         *  time complexity will be T(n) = n + T(n-1) = n^2
         *                                 |--> need to copy l1[1:]
         */
        return merge(l1, l2);
    }
    ListNode* merge(ListNode* l1, ListNode* l2){
        if(!l1 || !l2) return l1 ? l1 : l2;
        if(l1->val < l2->val){
            l1->next = merge(l1->next, l2);
            return l1;
        }else{
            l2->next = merge(l1, l2->next);
            return l2;
        }
    }
};
