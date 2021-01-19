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
     * 1. if val > root->val --> go to root->right
     * 2. if val < root->val --> go to root->left
     * 3. if root is null, create a new node with val and return it
     * 4. the returning node will bind with root
     */
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == NULL)
            return new TreeNode(val);
        //cout << "cur, val = "<<root->val<<", "<<val<<endl;
        if(root->val < val) {
            root->right = insertIntoBST(root->right, val);
        }else {
            root->left = insertIntoBST(root->left, val);
        }
        return root;
    }
};
