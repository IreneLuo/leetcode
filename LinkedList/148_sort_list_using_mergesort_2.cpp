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
    /* solution 1: mergesotr(bottom-up)
     *  time complexity = O(nlogn)
     *  space complexity = O(1)
     *
     *  If we have a->b->c->d->e->f->g->h
     *  then we sort them in logn round (n is the size of the list)
     *  round 1: a->b->c->d->e->f->g->h
     *           _  _  _  _  _  _  _  _  we compare a with b, c with d, e with f, g with h and link them together
     *  round 2: a->b->c->d->e->f->g->h
     *           ____  ____  ____  ____  we compare a->b with c->d, e->f with g->h
     *  round 3: a->b->c->d->e->f->g->h
     *           __________  __________  we compare a->b->c->d with e->f->g->h
     *  number of items that we handle in each round is like
     *       8
     *      /  \
     *     4      4
     *    / \    / \
     *   2   2   2  2
     *  /\  /\   /\ /\
     *  1 1 1 1 1 1 1 1
     *
     *
     *  Ex: [4,2,1,3]
     *      len = 4
     *        i = 1    dummy->4  2  1->3   --> split() will split the list into left list and right list
     *                   t    l  r  c          (break the next ptr between them)
     *  after merge    dummy->2->4  1  3
     *                           t  l  r  c
     *  after merge    dummy->2->4->1->3
     * ----------------
     *        i = 2    dummy->2->4  1->3
     *                   t    l     r     c
     *  after merge    dummy->1->2->3->4
     */
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* curr = head;
        int len = 1;
        while(curr->next){
            curr = curr->next;
            len++;
        }
        ListNode dummyHead(0, head);
        ListNode* tail;
        ListNode* left;
        ListNode* right;
        //i = i * 2 --> so we can finish it in logn time
        for(int i = 1; i < len; i <<= 1){
            curr = dummyHead.next;
            tail = &dummyHead;
            while(curr){
               left = curr;
               right = split(left, i);
               curr = split(right, i);
               auto merged = merge(left, right);
               tail->next = merged.first;
               tail = merged.second;
            }
        }
        return dummyHead.next;
    }
    ListNode* split(ListNode* head, int snippet){
        while(--snippet && head)
            head = head->next;
        ListNode* rest = head ? head->next: nullptr;
        if(head) head->next = nullptr;
        return rest;
    }
    /* Merge two lists, return head and tail
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
    pair<ListNode*, ListNode*> merge(ListNode* list1, ListNode* list2){
        ListNode dummyHead(0);
        ListNode* tail = &dummyHead;
        while(list1 && list2){
            if(list1->val < list2->val){
                tail->next = list1;
                list1 = list1->next;
            }else{
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        tail->next = list1 ? list1 : list2;
        //if tail points to a nullptr, we don't have to move tail
        while(tail->next) tail = tail->next;
        return {dummyHead.next, tail};
    }
};
