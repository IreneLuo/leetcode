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
     *   1. inorder traversal and get a sorted values in this tree
     *   2. use left, right and middle index to build a balanced binary search tree
     * time complexity = O(n)
     *     - step 1: O(n)
     *     - step 2: O(logn)
     * space complexity = O(n)
     * Similar: leetcode 108
     * Reference: HuaHua's video
     */
public:
    TreeNode* balanceBST(TreeNode* root) {
        /* inorder traverse and retrieve the values --> will be a sorted array
         * due to the original tree is a binary search tree
         */
        inorder(root);
        return build(0, values.size()-1);
    }
private:
    vector<int> values;
    void inorder(TreeNode* root){
        if(!root) return;
        inorder(root->left);
        values.push_back(root->val);
        inorder(root->right);
    }
    TreeNode* build(int left, int right){
        int mid = left + (right - left) / 2;
        if(left > right) return nullptr;
        TreeNode* root = new TreeNode(values[mid]);
        root->left = build(left, mid-1);
        root->right = build(mid+1, right);
        return root;
    }
};
