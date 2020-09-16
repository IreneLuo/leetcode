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
        /* Solution: (inorder method: node, left, right)
         * 1. find the middle number by using the left index and right index.
         *    then create a middle node
         * 2. populate the left node with left index and right index
         * 3. populate the right node with left index and right index
         * time complexity: O(n) // n nodes, each node for constant time
         * space complexity: O(h) // h: the height of the tree, the depth
         *                          of the code stack
         */
private:
    TreeNode* build_binary_search_tree(vector<int> nums, int left, int right) {
        cout << "build left, right = "<<left<<", "<<right<<endl;
        if (left == right)
            return NULL;
        int middle = left + ((right - left) / 2);
        TreeNode* node = new TreeNode(nums.at(middle));
        node->left = build_binary_search_tree(nums, left, middle);
        node->right = build_binary_search_tree(nums, middle + 1, right);
        return node;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        //must pass nums.size() as the parameter
        // if we pass nums.size()-1, the last value won't be added into the tree
        return build_binary_search_tree(nums, 0, nums.size());
    }
};
