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
public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL)
            return true;
        return check_symmetric(root->left, root->right);
    }
private:
    bool check_symmetric(TreeNode* lnode, TreeNode* rnode) {
        if(lnode == NULL && rnode == NULL) {
            //cout << " NULL, NULL return true "<<endl;
            return true;
        }
        /* 1. check the value of lnode and rnode
         * 2. check lnode's right child and rnode's left child
         * 3. check lnode's left child and rnode's right child
         * Note) both value and structure of nodes should be symmetric, so wo use
         *       && to combine all the conditions together
         * We'll have O(n) calls due to n nodes, and for each call costs O(1)
         */
        if(lnode != NULL && rnode != NULL) {
            //cout << "lnode, rnode = " << lnode->val << ", "<<rnode->val<<endl;
          return (lnode->val == rnode->val &&
                  check_symmetric(lnode->right, rnode->left) &&
                  check_symmetric(lnode->left, rnode->right));
            
        }
        return false;
    }
};
