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
     * Preorder: provide the node information
     * Inorder: provide the left and right node information
     * 1. Traverse over the node in the preorder list
     * 2. create a node while we access an item in the preorder list
     * 3. then we search the idx of that node in the Inorder list.
     *    we use that idx to find out the left subtree section and the right subtree section
     * 4. recursive call the function to build left/rigt nodes
     *
     * time complexity = O(n) --> visit n nodes, for each node only need constant time--> total we'll have linear time to decompose the whole tree
     * space complexity = O(n) --> a hashmap for space (n) + stack frames for O(tree's height) --> bound to O(n)
     */
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inorder_value_to_idx_map;
        curr_idx_preorder = 0;
        // create a map that <key, value> = <item in inorder, idx of the item>
        for(int i = 0; i < inorder.size(); i++)
            inorder_value_to_idx_map.insert(make_pair(inorder.at(i), i));

        return _buildTree(0, inorder.size() - 1, preorder, inorder, inorder_value_to_idx_map);      
    }
private:
    int curr_idx_preorder;
    TreeNode* _buildTree(int start, int end, vector<int>& preorder, vector<int>& inorder, unordered_map<int, int>& map) {
        int idx_inorder;

	// for the edge case like []
        if(start > end)
            return NULL;

        // create a node for the value that curr_idx_preorder indicates to
        TreeNode *node = new TreeNode(preorder[curr_idx_preorder]);
        curr_idx_preorder++;
        //cout << "< start, end > = " << start<<", "<<end<<" node: "<< node->val<<" idx in preorder= "<<curr_idx_preorder<<endl;

	// it means there's no left or right possiblities for this node, hence return the node
        if (start == end)
            return node;

        // find the key-value pair in the map as the key is this node's value
        if(map.find(node->val) != map.end())
            idx_inorder = map.at(node->val);

        node->left = _buildTree(start, idx_inorder - 1, preorder, inorder, map);
        node->right = _buildTree(idx_inorder + 1, end, preorder, inorder, map);
        return node;
    }
};
