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
    /* solution: Brute Force
     * traverse the whole tree and do a pathsum() for each node serving
     *    as root to a subtree
     * 1. find the total path sums with the root of the overarching tree
     * 2. go to the left subtree to find the total path sums
     * 3. go to the right subtree to find the total path sums
     * How to find total path sums for 1,2,3?
     * 
     */
public:
    int _pathSum(TreeNode* root, int newsum) {
        if (root == NULL)
            return 0;
        int count = ((root->val) == newsum) ? 1 : 0;
        count += _pathSum(root->left, newsum - root->val) +
                 _pathSum(root->right, newsum - root->val);
        return count;
    }
    int pathSum(TreeNode* root, int sum) {
        if (root == NULL)
            return 0;
        return _pathSum(root, sum) + pathSum(root->left, sum) +
               pathSum(root->right, sum);
    }
};
