/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/* solution:
 * 1. find the reference of target in the tree
 * 2. construct a hashtbl to save every node's parent
 * 2. start from target, go finding its neighbor(children and parent) --> the first level
 * 3. push their neighbor into queue and find their's neighbor --> the second level
 *    until level = k
 * 4. when we meet level k, the nodes in the queue are the answer
 *
 * time complexity = O(m+n) = O(n)
 *   - n : nodes in this tree
 *   - m : edges in this tree --> however, in a binary search tree, edges = nodes - 1 --> m = n-1 --> O(m+n) = O(n)
 * space complexity = O(n)
 *
 *         =======================
 *  ex:       =============      |
 *                        3      |
 *              ======/=  |   \  |
 *      Level 0      5 |  |    1 |
 *              ====/=\=  | ==/=\|
 *    Level 1      6  2   | | 0  8
 *           ==========/=\= |
 *                    7   4 |
 *  Level 2 =================
 *  distance = level here, so we can calculate the level, when level = k, we pop the queue
 */
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        vector<int> ans;
        int level = 0;
        unordered_map<TreeNode*, TreeNode*> tbl_mapping_to_parent;
        //construct a hashtbl for mapping node with its parent
        populate_node_to_hashtbl(tbl_mapping_to_parent, root, NULL);
        //push target into the queue
        queue<TreeNode*> q;
        set<TreeNode*> visited;
        q.push(target);
        visited.insert(target);
        //investigate the neighbor of nodes in the queue
        while(!q.empty()){
            int nodes_in_this_level = q.size();
            //only access q.front() for "num of nodes for this level" times
            //because we will have more than num of nodes for this level
            for(int i = 0; i < nodes_in_this_level; i++){
                if(level == K){
                    ans = dump_nodes_from_queue(q);
                    break;
                }
                TreeNode* node = q.front();
                q.pop();
                //investigate left child
                TreeNode* child = node->left;
                if(child!= NULL && visited.find(child) == visited.end()){
                    q.push(child);
                    visited.insert(child);
                }
                child = node->right;
                if(child != NULL && visited.find(child) == visited.end()){
                    q.push(child);
                    visited.insert(child);
                }
                TreeNode* parent = tbl_mapping_to_parent[node];
                if(parent != NULL && visited.find(parent) == visited.end()){
                    q.push(parent);
                    visited.insert(parent);  
                }
            }
            level++;
        }
        return ans;
    }
    void populate_node_to_hashtbl(unordered_map<TreeNode*, TreeNode*>& tbl,
                                  TreeNode* node, TreeNode* parent){
        if(node == NULL)
            return;

        tbl[node] = parent;
        populate_node_to_hashtbl(tbl, node->left, node);
        populate_node_to_hashtbl(tbl, node->right, node);
    }
    vector<int> dump_nodes_from_queue(queue<TreeNode*>& q){
        vector<int> ans;
        while(!q.empty()){
            ans.push_back(q.front()->val);
            q.pop();
        }
        return ans;
    }
};
