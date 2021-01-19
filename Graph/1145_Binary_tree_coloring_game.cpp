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
    /* solution:       x
     *                  \         [1]
     *          -------[red]---------
     *                 / | \
     *          [2]   y  |  z      [3]
     *                   |
     *  player2 can choose node x or y or z
     *   [1] if player2 choose node x, then he can
     *          dominate all the nodes except subtrees of red(y and z)
     *   [2] if player2 choose node y, then he can
     *          dominate all the nodes below node y, i.e left subtree of red
     *   [3] if player2 choose node z, then he can
     *          dominate all the nodes below node z, i.e right subtree of red
     *  player2 can choose the max one which has the maximum number of nodes.
     *  if number of nodes > n/2, then player2 can win the game
     *
     *  time complexity = O(n)
     *  space complexity = O(1)
     */ 
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        //get the number of left/right children of x
        num_of_children(root, x);
        //calculate the number of top nodes of x
        //top = total - (x's left + x's right + x itself)
        int top = n - (left_children + right_children + 1);
        //if max(left children, right children, top) > n/2 --> player2 win!
        return max(top, max(left_children, right_children)) > (n / 2);
    }
private:
    int left_children;
    int right_children;
    /* Count the number of nodes in this tree.
     * However, we only want to know the number of
     *   - left children of x
     *   - right children of x
     * so we update left_children and right_children
     * only when current node's val == pleyer1's node(val)
     */
    int num_of_children(TreeNode* root, int val){
        //if root is null, return 0
        if(!root) return 0;
        int left = num_of_children(root->left, val);
        int right= num_of_children(root->right, val);
        if(root->val == val){
            left_children = left;
            right_children = right;
        }
        return 1+left+right;
    }
};
