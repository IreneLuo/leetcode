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
    /* solution 1: traverse root1 and root2 respectively + mergesort
     *   - since the input data is a binary search tree
     *     so we can get a sorted list of values by using inorder traversal method
     *
     * solution 2: traverse root1 and root2 only once
     * 1. Push all the left nodes in root1 and root2 in stack1 and stack2
     * 2. Compare the top values in stack1 and stack2, retrieve the smaller one
     *    and pop it out the stack
     * 3. find the smallest value from current node's right subtree and push them into the stack
     * 4. back to step2
     * Example:  
     *       t1          t2        node  stack1  stack2  ans
     *        2           1         -    {2,1}    {1,0}
     *       / \         / \       t2,0  {2,1}    {1}    {0}  ->pop 0 from s2,find a
     *      1   5       0   3                                   smallest val from 0's right subtree
     *         / \                 t1,1  {2}      {1}    {0,1}
     *        3   8                t2,1  {2}      {3}    {0,1,1}
     *                             t1,2  {5,3}    {3}    {0,1,1,2} -> pop 2 from s1, push all the
     *                             t1,3  {5}      {3}    {0,1,1,2,3}  left values in 2's right subtree in s1
     *                             t1,3  {5}      {}     {0,1,1,2,3,3}
     *                             t1,5  {8}      {}     {0,1,1,2,3,3,5}
     *                             t1,8  {}       {}     {0,1,1,2,3,3,5,8}
     *
     *
     * time complexity = O(n)
     * space complexity = O(n)
     */
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        /* solution 1
        vector<int> data1;
        vector<int> data2;
        traverse(root1, data1);
        traverse(root2, data2);
        vector<int> ans;
        int i, j;
        for(i = 0, j = 0; i < data1.size() && j < data2.size();){
            if(data1[i] <= data2[j]) ans.push_back(data1[i++]);
            else ans.push_back(data2[j++]);
        }
        while(i < data1.size())
            ans.push_back(data1[i++]);
        while(j < data2.size())
            ans.push_back(data2[j++]);
        return ans;
        */
        /* solution 2 */
        stack<TreeNode*> s1;
        stack<TreeNode*> s2;
        find_smallest_value_in_left_subtree(root1, s1);
        find_smallest_value_in_left_subtree(root2, s2);
        vector<int> ans;
        while(!s1.empty() || !s2.empty()){
            /* Note that we must use a stack reference here, since we'll modify s1 or s2 through this reference.
             * If we use a hard copy like stack<TreeNode*> s = s1, then even we pop out a value in s,
             * the real value in s1 still exists(but we hope to remove this value in s1)
             *
             * If s1 is empty, s points to s2
             * If s2 is empty, s points to s1
             * If both s1,s2 are not empty, s points to the one that has a smallest value on the top
             */
            stack<TreeNode*>& s = s1.empty() ? s2 :
                                  s2.empty() ? s1 :
                                  (s1.top()->val <= s2.top()->val) ? s1 : s2;
            TreeNode* curr = s.top(); s.pop();
            ans.push_back(curr->val);
            find_smallest_value_in_left_subtree(curr->right, s);
        }
        return ans;
    }
    /* solution 2 */
    void find_smallest_value_in_left_subtree(TreeNode* root, stack<TreeNode*>& s){
        if(!root) return;
        s.push(root);
        find_smallest_value_in_left_subtree(root->left, s);
    }
    /* solution 1*/
    void traverse(TreeNode* root, vector<int>& data){
        if(!root) return;
        traverse(root->left, data);
        data.push_back(root->val);
        traverse(root->right, data);
    }
};
