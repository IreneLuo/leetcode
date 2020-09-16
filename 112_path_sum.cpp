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
    /* solution:
     * 1. calculate a new target sum (sum - value of current node)
     * 2. check left/right child node with this new target sum
     *    if child node is a leaf, check value equals to target sum or not
     *    if child node is not a leaf, goto 1
     * Time complexity: O(n)
     * Space complexity: O(h) // height of the tree will be the numbers of stack frames that we need
     */
public:
    bool hasPathSum(TreeNode* root, int sum) {
        // if a node only has one child
        if (root == NULL)
            return false;
        // if this node is a leaf
        if ((root->left == NULL) && (root->right == NULL))
            return (root->val == sum);
        // if this node has child, calculate a new target sum
        int new_sum = sum - root->val;
        return hasPathSum(root->left, new_sum) || hasPathSum(root->right, new_sum);
    }
};
