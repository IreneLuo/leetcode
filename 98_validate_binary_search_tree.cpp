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
    struct ArgumentedNode {
        TreeNode *node;
        long min;
        long max;
        ArgumentedNode(TreeNode *p, long n, long m) : node(p), min(n), max(m) {}
    };
    
public:

    /* solution 1: BFS
     * 1. traverse over the node by one level at a time.
     * 2. For each node, check its child nodes by:
     *    a. set the lower bound, upper bound
     *    b. compare if the child nodes' value is between lower bound and
     *       upper bound.
     *    c. if yes, keep checking other nodes
     *    d. if no, return false
     */
    bool isValidBST(TreeNode* root) {
/*
        queue<ArgumentedNode*> myqueue;
        myqueue.push(new ArgumentedNode(root, LONG_MIN, LONG_MAX));

        while(!myqueue.empty()) {
            ArgumentedNode* curr = myqueue.front();
            myqueue.pop();
            if (curr->node != NULL) {
                int value = curr->node->val;
                if (value <= curr->min || value >= curr->max)
                    return false;
                // remember to use parent node's min and max bound
                myqueue.push(new ArgumentedNode(curr->node->left,curr->min,value));
                myqueue.push(new ArgumentedNode(curr->node->right,value,curr->max));
            }
        }
        return true;
*/
     /* solution 2: recursive method */
        return _isValidBST(root, LONG_MIN, LONG_MAX);
    }
private:
    bool _isValidBST(TreeNode* node, long min, long max) {
        if (node == NULL)
            return true;

        if (node->val <= min || node->val >= max)
            return false;

        return _isValidBST(node->left, min, node->val) &&
            _isValidBST(node->right, node->val, max);
    }
    
};
