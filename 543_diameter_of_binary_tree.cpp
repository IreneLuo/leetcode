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
     * Main idea: How to find the best diameter ? Max(left_child_height + right_child_height, bestdiameter in subtree so far)
     * We could use recursive function to find the leaf, and return the information we need. Then accumulate the result backwards to the root.
     * ex: 
     *          step 5  we get the return node_info(3,3) --> 3 is the ans (the best diameter in this tree)
     *     1    step 4. left_node_info = (2,2), right_node_info = (0, 1) --> the best diameter so far in subtree = 2
     *    / \           now, we need to take itself into consideration --> the best diameter so far(including itself) = max (2, 2+1) = 3
     *   |   |          then, we calculate the height of this subtree(root = 1) = max(2,1)+1 = 3 (1->2->4) --> return node_info(3, 3)
     *   2   3  step 3. for 2: left_node_info = (0,1), right_node_info = (0,1) --> the best diameter so far in subtree = 0
     *   |                     now, we need to take itself into consideration --> the best diameter so far(including itself) = max (0, 1+1) = 2 
     *   |                                                                   (because 4->2->5 is longer)
     *   |                     then, we calculate the height of this subtree(root = 2) = max(1,1)+1 = 2
     *   |                     return node_info(2, 2)
     *   |         for 3: return (0, 1)
     *  / \     
     * 4   5    step 2. return (0, 1) --> best diameter so far = 1, subtree height = 1 (including itself)
     *          step 1. NULL, return (0, 0)
     */
private:
    struct node_info {
        int best_diameter_so_far;
        int subtree_height;
        node_info() : best_diameter_so_far(0), subtree_height(0) {}
        node_info(int x, int y) : best_diameter_so_far(x), subtree_height(y) {}
    };

    struct node_info* get_diameter_of_binary_tree(TreeNode* root) {
        // ex, the next node of a leaf node will return (0, 0)
        if(root == NULL)
            return new struct node_info(0, 0);

        struct node_info* left_node_info = get_diameter_of_binary_tree(root->left);

        struct node_info* right_node_info = get_diameter_of_binary_tree(root->right);

        int best_diameter_so_far_in_subtree = max(
                                            left_node_info->best_diameter_so_far,
                                            right_node_info->best_diameter_so_far);

        int my_left_right_child_height_total = left_node_info->subtree_height + right_node_info->subtree_height;

        int best_diamter_so_far = max(
                                    best_diameter_so_far_in_subtree,
                                    my_left_right_child_height_total);

        int max_subtree_height = max(
                                    left_node_info->subtree_height,
                                    right_node_info->subtree_height) + 1;

        return new struct node_info(best_diamter_so_far, max_subtree_height);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        struct node_info* ans_node_info = get_diameter_of_binary_tree(root);
        return ans_node_info->best_diameter_so_far;
    }
};
