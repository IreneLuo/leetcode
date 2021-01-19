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
    /* solution 1: dfs
     *   1. Traverse the list and add edge for node u and v if u,v are both
     *      in G
     *   2. Use an unordered_map to store the edges of each node
     *   3. Start visiting each node in G and use dfs to traverse all its neighbors
     *  Example: head: 0->1->2->3  G = [0, 1, 3]
     *  phase 1: construct edgetable
     *    u  v  count u  count v    edgetable
     *    0  1     y       y        [0]=1, [1]=0
     *    1  2     y       n
     *    2  3     n       y
     *    3
     *   
     *  phase 2: traverse all the nodes in G
     *  dfs(0, edgetable[0], visited)
     *     ===>[0,1,3]  visited  edge  ans <-------
     *          ^          0,1     1    1         | 2
     *     dfs(1, edgetable[1], visited)      ----|
     *         ===>[1]  visited  edge  ans    <----
     *                 0,1    0                   | 1
     *         dfs(0, edgetable[0], visited)      |
     *             ===> 0 already visited, return -
     *
     * dfs(1, edgetable[1], visited)
     *     ===> 1 already visited, continue
     *
     * dfs(3, edgetable[3], visited)
     *    ===>[0,1,3]  visited  edge  an
     *             ^     0,1,3        2
     *
     * time complexity = O(n)
     * space complexity = O(n)
     *
     * solution 2: property of list
     * A sublist is a connected components if all nodes in the sublist
     * are in G
     * For example, we mark the node in G as 1 and the node not in G as 0
     * Ex: 0->1->2->3 --> 1->1->0->1
     *                    |==|    |=|
     *              2 connected components
     *
     *  Implementation: 0->1->2->3
     *                     ^     ^
     *                   case1  case2
     *  case 1: if head->val is in G && head->next->val is not in G
     *          --> hit the end of a connected component --> ++ans
     *  case 2: if head->val is in G && head->next does not exist
     *          --> hit the end of a connected componet --> ++ans
     * time complexity = O(n)
     * space complexity = O(n)
     */
public:
    int numComponents(ListNode* head, vector<int>& G) {
        /* solution 1
        unordered_set<int> nodelist(G.begin(), G.end());
        unordered_map<int, vector<int>> edgetable;
        ListNode* curr = head;
        int u = curr->val;
        while(curr->next){
            curr = curr->next;
            int v = curr->val;
            if(nodelist.count(u) && nodelist.count(v)){
                edgetable[u].push_back(v);
                edgetable[v].push_back(u);
            }
            u = v;
        }
        set<int> visited;
        int ans = 0;
        for(int g: G){
            if(visited.count(g)) continue;
            dfs(g, edgetable, visited);
            ++ans;
        }
        */
        /* solution 2 */
        unordered_set<int> nodelist(G.begin(), G.end());
        int ans = 0;
        while(head){
            if(nodelist.count(head->val) && 
               (!head->next || !(nodelist.count(head->next->val))))
                ++ans;
            head = head->next;
        }
        return ans;
    }
    void dfs(int curr, unordered_map<int, vector<int>>& edgetbl, set<int>& visited){
        if(visited.count(curr)) return;
        visited.insert(curr);
        for(int n : edgetbl[curr]){
            dfs(n, edgetbl, visited);
        }
    }
};
