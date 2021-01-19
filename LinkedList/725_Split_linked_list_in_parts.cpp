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
     * Example: [1,2,3,4] k=5
     *  len = 4
     *  snippet = 4/5=0
     *  mod = 4%5=4
     *  so we have to split the list into 5 parts and the previous 4 parts has
     *  size = snippet + 1
     *           [1,2,3,4]
     *  init   ^  ^
     *         p  c
     *  part 0   [1,2,3,4] -->   [1] [2,3,4]
     *            ^ ^      break
     *            p c      the link
     *  part 1   [1,2,3,4] -->   [1][2] [3,4]
     *              ^ ^
     *              p c
     *  part 2   [1,2,3,4] -->   [1][2][3] [4]
     *                ^ ^
     *                p c
     *  part 3   [1,2,3,4] -->   [1][2][3][4]
     *                  ^ ^
     *                  p c --> break
     * time complexity = O(n)
     * space complexity = O(1)
     *
     */
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        /* get the length of the list */
        int len = 0;
        ListNode* curr = root;
        for(curr; curr!= NULL; curr=curr->next)
            ++len;
        /* calculate the length of each part */
        int snippet = len / k;
        int mod = len % k;
        /* split each part */
        ListNode* prev = nullptr;
        vector<ListNode*> ans(k, nullptr);
        curr = root;
        for(int part = 0; part < k; part++){
            //if list length < k, curr might point to nullptr
            if(!curr) break;
            ans[part] = curr;
            //each part have to share the mod until mod is 0
            int extra = (mod-- > 0) ? 1 : 0;
            for(int s = 1; s <= snippet + extra; s++){
                prev = curr;
                curr = curr->next;
            }
            if(prev) prev->next = nullptr;
        }
        return ans;
    }
};
