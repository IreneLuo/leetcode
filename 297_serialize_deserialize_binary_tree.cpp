/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        /* for a parent node
         *   a. keep asking its left and right node the string pattern
         *   b. once it gets the ans, combine with the value itself
         *   c. then return the string pattern to its parent
         * this algorithm will get a string like: 1,2,NULL,NULL,3,4,NULL,NULL,5,NULL,NULL,
         *    each node comes with its children     |---------| |------------||--------|
         *                                            L tree   R tree of node1 R tree of node3  
         */
        string null = "NULL";
        string deli = ",";
        if (root == NULL)
            return null+ deli;
        string left_str = serialize(root->left);
        string right_str = serialize(root->right);
        return to_string(root->val) + deli + left_str + right_str;
    }

    // Decodes your encoded data to tree.
    // 1. split the ",", alpha and NULL, put alph and NULL into to a queue
    // 2. retrieve an item from the queue and create a node for it
    // 3. then keep retrieving the items from the queue until we encouter a NULL --> it means left node is done
    // 4. then keep retrieving the items from the queue until we encouter a NULL --> it means right node is done
    // 5. return current node
    TreeNode* deserialize(string data) {
        queue<string> nodequeue;
        string s = "";
        for (int i = 0; i < data.size(); i++) {
            if (data.substr(i, 1) != ",") {
                s += data.substr(i, 1);
            } else {
                nodequeue.push(s);
                s = "";
            }
        }
        return _deserialize(nodequeue);
    }
    //1,2,NULL,NULL,3,4,NULL,NULL,5,NULL,NULL,
    TreeNode* _deserialize(queue<string>& nodequeue) {
        string s = nodequeue.front();
        nodequeue.pop();
        if(s == "NULL")
            return NULL;
        TreeNode* node = new TreeNode(stoi(s));
        node->left = _deserialize(nodequeue);
        node->right = _deserialize(nodequeue);
        return node;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
