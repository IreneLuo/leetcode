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
/* solution : dfs
 * Observation:
 *    An palindrome has at most 1 digit that appears odd times
 *    Ex: 2112 => both 1 and 2 appear two times
 *        21312 => both 1 and 2 appear two times. 3 appears only once.
 *        213412=> both 3 and 4 appear once, so it's not a palindrome
 * Method:
 *  use dfs() to traverse all the paths
 *  use an int to record each digit(0-9) has appeared odd or even times
 *     int digit_cnt:
 *              [1] = digit 1 appears odd or even times
 *              [2] = digit 2 appears odd or even times
 *              ...
 *              [9] = digit 9 appears odd or even times
 *     for each bit, 1 = odd times, 0 = even times
 *     and we can use XOR operation to reverse the bit each time
 *
 *  1. when we visit a node (non-leaf), reverse the bit of the digit
 *  2. when we visit a leaf nod, we count the 1 in digit_cnt
 *     if 1 appears more than once, it's not a palindrome
 *     otherwise, it's a palindrome and ans++
 * time complexity = O(n)
 * space complexity = O(1)
 */
class Solution {

public:
    int pseudoPalindromicPaths (TreeNode* root) {
        return dfs(root);
    }
private:
    int digit_cnt = 0;
    int dfs(TreeNode* node) {
        int ans = 0;

        if(!node) return 0;
        digit_cnt ^= (1 << node->val);
        if(!node->left && !node->right && __builtin_popcount(digit_cnt) <= 1)
            ans += 1;
        ans += dfs(node->left);
        ans += dfs(node->right);
        digit_cnt ^= (1 << node->val);
        return ans;
    }
};
