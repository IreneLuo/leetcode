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
    /* solution: dfs
     * For each non-leaf node:
     *    1. check how many coins are needed in left subtree (leftcoins)
     *    2. check how many coins are needed in right subtree (rightcoins)
     *    3. leftcoins + rightcoins is the required num of moves in the subtree.
     *       save it into the answer
     *    4. return curr->val-1+leftcoins+rightcoins to current node's parent
     *              |-------------------------------|
     *               how many coins are needed in this subtree
     *               -1 since we have to reserve 1 coin for current node
     *               if the result > 0, then the coins in this subtree are more
     *               than enough, so it can share the coins with others
     *               if the result < 0, then the coins are not enough in this
     *               subtree, so it needs to get more coins from others
     *
     *  Example:              balance(a) = 1-1+balance(b)+balance(d)
     *             a(1)                  = 1-1+1-1=0
     *             /  \       balance(b) = 0-1+balance(c)=0-1+2=1 #
     *           b(0) d(0)    balance(c) = 3-1=2  # (c has 2 more coins)
     *            \           balance(d) = 0-1=-1 # (d needs 1 coin)
     *            c(3)                     
     *   the ans = add all the # = 2+|-1|+1=4
     *
     *  time complexity = O(n)
     *  space complexity = O(n)
     *      - O(h): height of the tree
     *        in worst case h could be n
     */
public:
    int distributeCoins(TreeNode* root) {
        int ans = 0;
        balance(root, ans);
        return ans;
    }
    int balance(TreeNode* root, int& ans){
        if(!root) return 0;
        int leftcoins = balance(root->left, ans);
        int rightcoins = balance(root->right, ans);
        ans += abs(leftcoins) + abs(rightcoins);
        return root->val - 1 + leftcoins + rightcoins;
    }
};
