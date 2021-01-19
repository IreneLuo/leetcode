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
/*
 Example: N=7
     |-----------------------------------------------------|
    N=7                                                  N=7
  left=1 ---------------|                                left=3
  right=5      |-------------------|                    right=3
     1         N=5                 N=5                    
    / \       left=1 ---|         left=3 -----|
   2         right=3  N=3        right=1     N=3
              3     left=1         3       left=1
             / \    right=1       / \      right=1
            4         5              5       4
                     / \                    / \
                    6   7                  6   7
                  3->right=ans{5}        3->left=ans{4}
                  
  time complexity = O(n)
  space complexity = O(n)
*/
class Solution {
public:
    vector<TreeNode*> allPossibleFBT(int N) {
        /* solution 1
        //the number of nodes of a full binary tree can't be odd
        if(N % 2 == 0) return {};
        //if N is 1, return only 1 node
        if(N == 1) return vector<TreeNode*>(1, new TreeNode(0));
        //enumerate all possible number of nodes on left side
        vector<TreeNode*> ans;
        for(int left = 1; left < N; left+=2){
            //combine all possible left subtree with right subtree
            for(TreeNode* leftTree: allPossibleFBT(left)){
                for(TreeNode* rightTree: allPossibleFBT(N-1-left)){
                    TreeNode* root = new TreeNode(0);
                    root->left = leftTree;
                    root->right = rightTree;
                    ans.push_back(root);
                }
            }
        }
        return ans;
        */
        return find(N);
    }
private:
    /* solution2: 
     *   1. add a hashtbl to save the answer that we've gotten before
     *   2. use reference instead of copy in two for loops (much more faster)
     */
    unordered_map<int, vector<TreeNode*>> hashtbl;
    vector<TreeNode*> find(int N) {
        if(hashtbl[N].size() > 0) return hashtbl[N];
        vector<TreeNode*>& ans = hashtbl[N];
        //the number of nodes of a full binary tree can't be odd
        if(N % 2 == 0) return {};
        //if N is 1, return only 1 node
        if(N == 1) return vector<TreeNode*>(1, new TreeNode(0));
        //enumerate all possible number of nodes on left side
        for(int left = 1; left < N; left+=2){
            //combine all possible left subtree with right subtree
            for(auto& leftTree: allPossibleFBT(left)){
                for(auto& rightTree: allPossibleFBT(N-1-left)){
                    TreeNode* root = new TreeNode(0);
                    root->left = leftTree;
                    root->right = rightTree;
                    ans.push_back(root);
                }
            }
        }
        return ans;
    }
};
