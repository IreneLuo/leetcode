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
    /* solution 1:
     *   1. traverse the tree and get the total of all the values
     *   2. traverse the tree again:
     *      For each non-leaf node,
     *          1. get the sum of left/right subtree
     *          2. calculate the product of the sums if we cut off left subtree
     *                     -> left sum * (total-left sum)
     *          3. calculate the product of the sums if we cut off right subtree
     *                     -> right sum * (total-right sum)
     *          4. compare 2, 3 and save the max one
     *          5. return the left sum + right sum + self value to its parent node
     *             and the parent node will repeat step 1 to 5 again
     *      When we back to the root, we can get the answer
     *
     *  time complexity = O(n)
     *  space complexity = O(n)
     *
     *  note that: number of nodes <= 50000
     *             value of a node <= 10000
     *  so for worst case
     *            for each side(left and right) has 25000 nodes with values 10000
     *            = 250000000
     *     and left sum * right sum = 250000000 * 250000000 will overflow if we use int
     *     so we use long as data type for total and ans
     */
public:
    int maxProduct(TreeNode* root) {
        int mod = 1e9 + 7;
        long total = get_total(root);
        long ans = 0;
        dfs(root, total, ans);
        return ans % mod;
    }
    long get_total(TreeNode* root){
        if(!root) return 0;
        return root->val + get_total(root->left) + get_total(root->right);
    }
    int dfs(TreeNode* root, long& total, long& ans){
        if(!root) return 0;
        if(!root->left && !root->right) return root->val;
        int left_sum = dfs(root->left, total, ans);
        int right_sum = dfs(root->right, total, ans);
        ans = max(ans, max(
                        left_sum * (total - left_sum), 
                        right_sum * (total - right_sum)));
        return (left_sum + right_sum + root->val);
    }
};
