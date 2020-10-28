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
     * for each node:
     * 1. ask child node (1) is it balanced? (2) how height it is?
     * 2. if the node is null, return the height -1 and is_balanced=true
     * 3. once a parent node receive the information for its child nodes
     *    a. check if its child nodes are balanced or not. If not, return false immediately
     *    b. calculate the balanced status and the height including itself, and return the information to its parent
     * time complexity = O(n)  // this will touch each node in the tree
     * space complexity = O(n) // for struct subtree_info
     */
private:
    struct subtree_info{
        bool isbalanced;
        int height;
        subtree_info(bool x, int y) : isbalanced(x), height(y) {}
    };
public:
    bool isBalanced(TreeNode* root) {
        struct subtree_info* ans = _isBalanced(root);
        return ans->isbalanced;
    }
    struct subtree_info* _isBalanced(TreeNode* parent) {
        struct subtree_info* parentinfo = new struct subtree_info(true, -1);
        if(parent == NULL)
            return parentinfo;

        struct subtree_info* leftinfo = _isBalanced(parent->left);
        if(!leftinfo->isbalanced)
            return leftinfo;

        struct subtree_info* rightinfo = _isBalanced(parent->right);
        if(!rightinfo->isbalanced)
            return rightinfo;

        parentinfo->isbalanced = (1 >= abs(leftinfo->height - rightinfo->height)) ? true : false;
        parentinfo->height = max(leftinfo->height, rightinfo->height) + 1;
        return parentinfo;
    }
};
