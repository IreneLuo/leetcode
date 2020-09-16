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
    /* solution 1: using a stack
     * 1. push each node into the stack and go to the left node until we encounter a NULL
     * 2. if the node is NULL, pop out the stack and push it to the answer
     * 3. then access the right node and push the value into the stack until we counter a NULL
     * 3. continue step 2
     * 4. we keep following the order of left->node->right to access each node until the stack is empty or the node is NULL
     * Time complexity: O(n)
     * Space complexity: O(n)
     */

    vector<int> inorderTraversal(TreeNode* root) {
    /*
        stack<TreeNode*> temp_stack;
        vector<int> ans;
        TreeNode* ptr = root;

        while(!temp_stack.empty() || ptr != NULL) {
            // access left node
            while(ptr != NULL) {
                temp_stack.push(ptr);
                ptr = ptr->left;
            }
            // access node
            ptr = temp_stack.top();
            ans.push_back(ptr->val);
            temp_stack.pop();
            //access right node
            ptr = ptr->right;
        }
        return ans;
    */
        
        /* solution 2: recursive function calls
         * time complexity: O(n)
         * space complexity: O(n) (stack frames)
         */  
        /*
        vector<int> ans;
        _inorderTraversal(root, ans);
        return ans;
        */

        /* solution 3: morris method
         * 1. go to the left subtree of current node(root)
         * 2. find out the rightmost node of the left subtree,
         *    and set the root as the right node of this rightmost node
         * 3. then move the pointer to the root->left, keep doing step 1-3 until there's no left subtree
         * 4. print them out
         * time complexity: O(n)
         * space complexity: O(1) //count the solution set as extra space
         */ 
        vector<int> ans;
        TreeNode* ptr = root;
        TreeNode* pre;
        while(ptr != NULL) {
            if(ptr->left != NULL) {
                pre = ptr->left;
                // find the rightmost node
                while(pre->right != NULL) {
                    pre = pre->right;
                }
                // put ptr after the rightmost node
                pre->right = ptr;
                TreeNode* temp = ptr;
                ptr = ptr->left;
                temp->left = NULL;
            
            // if ptr->left == NULL
            }else {
                ans.push_back(ptr->val);
                ptr = ptr->right;
            }
        }
        return ans;
    }
    /*
    // for solution 2
    void _inorderTraversal(TreeNode* root, vector<int>& ans) {
        if (root == NULL)
            return;

        _inorderTraversal(root->left, ans);
        ans.push_back(root->val);
        _inorderTraversal(root->right, ans);
    }
    */
};
