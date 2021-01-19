/* solution: stack
 * 1. push all the elements of list1 and list2 into two stacks
 * 2. pop out and add the elements until both stacks are empty
 * Remember to deal with the carry bit after adding all the elements
 * time complexity = O(max(l1, l2))
 * space complexity = O(max(l1, l2))
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1;
        stack<int> s2;
        ListNode* ptr = l1;
        while(ptr){
            s1.push(ptr->val);
            ptr = ptr->next;
        }
        ptr = l2;
        while(ptr){
            s2.push(ptr->val);
            ptr = ptr->next;
        }
        int sum = 0;
        ListNode* ans = nullptr;
        while(!s1.empty() || !s2.empty()){
            if(!s1.empty()){
                sum += s1.top();
                s1.pop();
            }
            if(!s2.empty()){
                sum += s2.top();
                s2.pop();
            }
            ListNode* node = new ListNode(sum % 10, ans);
            ans = node;
            sum /= 10;
        }
        if(sum > 0){
            ListNode* node = new ListNode(sum % 10, ans);
            ans = node;
        }
        return ans;
    }
};
