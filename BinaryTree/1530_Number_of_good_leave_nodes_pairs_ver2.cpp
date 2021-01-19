/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    /* solution 2: DFS
     * Main idea:
     *      For each node, ask its children that how many pairs of nodes
     *      are good leaves and return the answer to its parent
     * Example:   Each node will return {hashtbl, ans}
     *              - hashtbl: all the possible distance with count
     *              - answer: the good leave pairs
     *
     *                       1  {2:4}:2
     *                /            \
     *  {1:2},1    2                  3   {1:2},1
     *          /     \            /     \
     *         4       5          6       7
     *      {0:1},0  {0:1},0   {0:1},0  {0:1},0
     *
     *  Node 1:
     *      -> left child says: it has 2 nodes in distance 1
     *      -> right child says: it has 2 nodes in distance 1
     *      -> If we pair the nodes on left side with the nodes on right side
     *      the distance would be 1 + 1 + 2(left/rightchild to node1) = 4 > distance 3
     *      so we cannot pair them together
     *      -> so we summarize the info from the left/right child
     *         the nodes in distance 2 = leftmap[1] + rightmap[1]=2+2=4
     *         the pairs = left child pairs + right child pairs = 1+1=2
     *  Formula:
     *                      a {d1+1:c1+c3, d2+1:c2+c4}, ans1+ans2+A
     *                 /        \                    
     *                b          c
     *   {d1:c1, d2:c2},ans1    {d1:c3, d2:c4},ans2
     *   for(d: d1, d2)
     *      for(d': d1, d2)
     *          if(d+d'+2 <= distance) A = map[d]*map[d']
     *
     * time complexity = O(n* D^2)
     * space complexity = O(n)
     * Reference: HuaHua's video
     */
public:
    int countPairs(TreeNode* root, int distance) {
        return dfs(root, distance).second;
    }
private:
    pair<unordered_map<int, int>, int> dfs(TreeNode* curr, int& distance){
        /* distance/count */
        unordered_map<int, int> m;
        /* if the tree is empty, return 0 */
        if(!curr) return{m, 0};
        /* if curr is a leaf node, return {0:1},0 */
        if(!curr->left && !curr->right){
            m[0] = 1;
            return{m, 0};
        }
        /* left.first = hashtbl, left.second = ans */
        auto left = dfs(curr->left, distance);
        auto right = dfs(curr->right, distance);
        unordered_map<int, int> map_left = left.first;
        unordered_map<int, int> map_right = right.first;
        int cnt_left = left.second;
        int cnt_right = right.second;
        int ans = 0;
        /*check distance of left child + distance of right child
         *    + 2 <= distance or not,
         *    if yes, pair them together (use *)
         */
        for(int i = 0; i < map_left.size(); i++){
            for(int j = 0; j < map_right.size(); j++)
                if(map_left[i] && map_right[j] && (i + j + 2) <= distance)
                    ans += map_left[i] * map_right[j];
        }
        /* summarize the hashtbl and ans
         * all the children's distance + 1 = distance from children to curr node
         */
        for(int i = 0; i <= distance; i++)
            m[i+1] = map_left[i] + map_right[i];

        return {m, cnt_left + cnt_right + ans};
    }
};
