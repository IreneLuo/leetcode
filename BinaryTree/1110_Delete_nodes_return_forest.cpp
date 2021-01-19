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
    /* solution: post-order traversal
     * 1. we use post-order traversal to visit all the nodes in the tree
     * 2. after visiting left and right subtree, we check if current node
     *    has to be deleted or not
     *    if yes, push left/right subtree's head node into the answer
     *           and return nullptr to its parent node
     *    if no, return current node to its parent node
     * Example:
     *      1                                1
     *       \                                \       1. ans.push_back(6)
     *        3  --> <after deleting 3>     nullptr      ans.push_back(7)
     *       / \                                      2. return nullptr to node1
     *      6   7                             6  7    3. ans.push_back(1)
     *  
     * time complexity = O(n)
     * space complexity = O(h)
     *    - h: the height of the tree (depth of function calls)
     *    - if this tree is an unbalanced tree, then the worst case
     *      could be O(n) (n==h)
     */
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        deleteset = set<int>(to_delete.begin(), to_delete.end());
        root = delete_node(root);
        if(root)
            ans.push_back(root);
        return ans;
    }
private:
    vector<TreeNode*> ans;
    set<int> deleteset;
    TreeNode* delete_node(TreeNode* root){
        if(!root) return nullptr;
        root->left = delete_node(root->left);
        root->right = delete_node(root->right);
        if(deleteset.count(root->val)){
            if(root->left) ans.push_back(root->left);
            if(root->right) ans.push_back(root->right);
            return nullptr;
        }else{
            return root;
        }   
    }
};
