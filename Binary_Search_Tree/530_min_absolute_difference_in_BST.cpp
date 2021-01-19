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
    /* solution 1: inorder traversal
     * In a binary search tree, all the items will be sorted
     * while we use inorder traversal to visit all the nodes in it.
     * So:
     *  1. we use inorder traversal to get all the nodes
     *  2. compare each item in the nodes' list
     *  3. retrieve the min one
     * time complexity = O(n) //inorder traverse + finding min
     * space complexity = O(n)
     *
     * Example: 
     *             8
     *           /   \          inorder traversal:
     *          3     10                1,3,4,6,7,8,10,13,14
     *         /  \    \        everytime we calculate
     *        1    6   14               [i] - [i-1] --> child - parent
     *            / \  /        
     *           4  7 13
     * solution 2: optimization
     * While we traverse the tree, keep the parent node
     * and let child node - parent node to get a diff value
     *
     * space complexity = O(1)
     */
public:
    int getMinimumDifference(TreeNode* root) {
        /* solution 1:
        vector<int> order;
        inorder(root, order);
        int min_diff = order.back();
        for(int i = 1; i < order.size(); i++)
            min_diff = min(min_diff, order[i] - order[i-1]);
        return min_diff;
        */
        /* solution 2: */
        int min_diff = INT_MAX;
        inorder_opt(root, min_diff);
        return min_diff;
    }
private:
    void inorder(TreeNode* root, vector<int>& order){
        if(!root) return;
        inorder(root->left, order);
        order.push_back(root->val);
        inorder(root->right, order);
    }
    void inorder_opt(TreeNode* root, int& min_diff){
        if(!root) return;
        inorder_opt(root->left, min_diff);
        if(prev != NULL)
            min_diff = min(min_diff, root->val - prev->val);
        prev = root;
        inorder_opt(root->right, min_diff);
    }
    TreeNode* prev = NULL;
};
