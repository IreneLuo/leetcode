/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        /* case 1: if x, y < root, recursive left
         * case 2: if x, y > root, recursive right
         * case 3: if x or y = root, return root
         * case 4: if x < root, y > root, return root
         * Time complexity: O(log n)
         * Space complexity: O(log n) (stack size, recursive calls log(n) times)
         */
        //cout << "root, p, q = "<<root->val<<", "<<p->val<<", "<<q->val<<endl;
        TreeNode* ans = root;
        if (p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);
        if (p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right, p, q);

        return root;
    }
};
