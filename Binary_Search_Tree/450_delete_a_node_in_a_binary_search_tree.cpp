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
// can combine with leetcode.701 insert a node into a BST
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == NULL)
            return NULL;

        // if key > root val, go to the right subtree
        if(root->val < key)
            root->right = deleteNode(root->right, key);
        // if key < root val, go to the left subtree
        else if(root->val > key)
            root->left = deleteNode(root->left, key);
        // if root->val == key --> root is the node that we want to delete
        else {
            // if this node only right node, connect the right child with root's parent node
            if(root->left == NULL)
                return root->right;
            // if this node only left node, connect the left child with root's parent node
            else if(root->right == NULL)
                return root->left;
            // if root has left and right child nodes, we have to find the next smallest in its right subtree
            else {
                TreeNode* temp = get_the_smallest_node_in_right_subtree(root->right);
                // after finding the smallest node, replace the value to root val,
                // and keep deleting process until we kill that smallest node in its original position
                root->val = temp->val;
                root->right = deleteNode(root->right, temp->val);
            }          
        }
        return root;
    }
private:
    TreeNode* get_the_smallest_node_in_right_subtree(TreeNode* root) {
        if(root == NULL)
            return NULL;
        TreeNode* temp = root;
        while(temp->left != NULL)
            temp = temp->left;
        return temp;
    }
};
