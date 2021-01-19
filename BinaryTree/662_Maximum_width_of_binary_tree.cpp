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
    /* Solution : dfs
     * For the root node, we give it id 0
     * and the left child's id = id(parent) * 2
     *         right child's id = id(parent) * 2
     * then we record the leftmost node's id of each level
     * and calculate the width when we visit each node
     *     - width = id(current node) - id(leftmost node) + 1
     *
     * Example: 
     *         1                                  0  (1,2,4)    
     *       /   \                          /           \
     *      3     2   --> change to id     0  (1,1,2)    1 (2,0,4)
     *     / \     \                      / \           /  \
     *    5   3     9                  0      1       -      3
     *                             (1,0,0) (2,0,0)   (0) (4,0,0)
     *   node   id    return
     *    5      0   max(1,0,0)=1  --> width of node id 0 = 0 - 0 + 1 = 1
     *                                                    (id=0) (leftmost id=0)
     *    3      1   max(2,0,0)=2  --> with of node id 1 = 1-0+1=2
     *    -              0
     *    9      3   max(4,0,0)=4
     *    3      0   max(1,1,2)=2  --> 1=width of node3
     *                                 1=left child's max width
     *                                 2=right child's max width
     *    2      1   max(2,0,4)=4  --> 2=width of node2
     *                                 0=left child's max width
     *                                 4=right child's max width                                *    1      0   max(1,2,4)=4  --> 1=width of node1
     *                                 2=left child's max width
     *                                 4=right child's max width                                *   --> the ans = 4
     *
     *  Note that we cannot use 1 as root's id
     *          left = 2 * root's id
     *          right = 2 * root's id + 1
     *  because if a node's id = 2^63, the id of its right child = 2^64+1 (overflow!)
     *  this case is possible, since the depth of a tree could be more than 64.
     *  Instead, we use 0 as root's id
     *          left = 2 * root's id
     *          right = 2 * root's id + 1 
     *  so the id starts from each level will be 0
     *     ( for level h, ids will be 0, 1, 2, 3, 4, 5....h-1)
     *  For this case, it won't overflow if we change ids like the right one
     *       1                   0
     *      / \                 / \
     *     2   3  ------>      0   1 
     *    /     \             /     \
     *   4       7           0       3   
     *   /        \         /         \
     *  ...       ...      ...        ...
     *  /           \      /            \
     * 2^63      2^64+1   0              64
     *  
     *  time complexity = O(n)
     *  space complexity = O(h)
     *        - h = height of the tree/depth of dfs calls
     */
public:
    int widthOfBinaryTree(TreeNode* root) {
        vector<int> leftmost;
        return dfs(root, 0, 0, leftmost);
    }
    int dfs(TreeNode* root, int depth, long id, vector<int>& leftmost){
        if(!root) return 0;
        if(leftmost.size() == depth) leftmost.push_back(id);
        int offset = id - leftmost[depth];
        return max(offset + 1,max(
                  dfs(root->left, depth+1, (long)offset*2, leftmost),
                  dfs(root->right, depth+1, (long)offset*2+1, leftmost)));
    }
};
/* test case
[1,1,1,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,null,1,1,null,1,null,1,null,1,null,1,null]
*/
