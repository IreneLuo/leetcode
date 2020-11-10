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
    /* solution:
     * We use a queue to handle the nodes in each level
     * ex:     3
     *        / \
     *      9   20
     *     / \  / \
     *   10  11 12 13
     * 
     *         <queue>       <answer>
     *      front    back    
     * 1.     3                         //we push root into the queue. Only 1 item in this queue, so we know that #node in layer0 = 1
     * 2.    9 20              {3}*     //pop out 3 and push 3's child into the queue. #node in laywer1 = 2, so we start a for loop (2 iterations)
     * 3.    20 10 11          {9}      //the first iteration, we pop out 9, and push its children
     * 4.    10 11 12 13       {9,20}*  //the second iteration, we pop out 20, and push its children.
     *                                    For loop finish and we start a next loop(next layer will have 4 nodes, so run 4 iterations)
     * 5.                      {10 11 12 13}* //after 4 iterations, all the items in queue are done
     * the answer will be the set with * = {3} {9,20}, {10 11 12 13}
     * 
     * time complexity = O(n) //for loop will iterate over all nodes
     * space complexity = O(n)
     * 
     */
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        //check the input is valid or not
        if(root == NULL)
            return {};

        queue<TreeNode*> q;
        TreeNode* curr = root;
        //push the item from root to the queue
        q.push(curr);
        vector<int> nodes_set_in_layer;
        while(!q.empty()){
            nodes_set_in_layer.clear();
            //the size of queue decides the amount of nodes in this layer
            int nodes_in_layer = q.size();
            for(int i = 0; i < nodes_in_layer; i++){
                //retrieve a node from queue and push it to the temp answer set
                TreeNode* n = q.front();
                nodes_set_in_layer.push_back(n->val);
                //find this node's left/right child
                if(n->left != NULL)
                    q.push(n->left);
                if(n->right != NULL)
                    q.push(n->right);
                //pop out this node
                q.pop();  
            }
            //finishing the nodes in this layer
            ans.push_back(nodes_set_in_layer);
        }
        return ans;
    }
};
