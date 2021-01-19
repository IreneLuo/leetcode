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
    /* solution 1: BruteForce
     *   1. collect all the leaves
     *   2. enumerate all the leaves and check the distance between each 2 leaves <= distance
     *      - how to get the distance between two leaves? --> LCA(least common ancester)
     *             1
     *            / \     --> for node 4 and 5, LCA = 2
     *           2   3        we save all the ancesters of node 4
     *          / \           then we iterate over the ancesters of node 5
     *         4   5          if ancester(node5) == ancester(node4)
     *                        then this ancester is the LCA of node 4 and 5
     *
     * time complexity = O(leaves^2) = O(n^2)
     *     - collect all the leaves (dfs) = O(leaves)
     *     - enumerate all the leaves and get the distance = O(leaves^2)
     *     for a tree which has n nodes, the leaves of it can be at most n/2
     * space complexity = O(n)
     */
public:
    int countPairs(TreeNode* root, int distance) {
        int ans = 0;
        //collect all the leaves and find the parent of each node
        dfs(root, nullptr);
        //compare the distance of every 2 nodes
        for(int i = 0; i < leaves.size(); i++){
            distanceTbl.clear();
            TreeNode* a = leaves[i];
            /* Save the distance from all ancesters to node a into the hashtbl
             * Example:  1 distance[node1] = 2
             *          /
             *         2 distance[node2] = 1 (distance from node 2-4 = 1)
             *        /
             *      4   distance[node4] = 0
             */
            for(int dist = 0; dist < distance && a != nullptr; dist++){
                distanceTbl[a] = dist;
                a = parent[a];
            }
            /* find the least common ancester between leaves[i] and leaves[j]
             *           1  
             *          /
             *         2   -> distance.count(node2)=1 -> the least common ancestor
             *        / \     so the distance between 4 and 5 = 2~4 + 2~5 = 2 < distance->Hit!
             *       4   5 -> distance.count(node5)=0 so go to its parent
             */
            for(int j = i+1; j < leaves.size(); j++)
                ans += isGood(leaves[j], distance);
        }
        return ans;
    }
private:
    vector<TreeNode*> leaves;
    unordered_map<TreeNode*, TreeNode*> parent;
    unordered_map<TreeNode*, int> distanceTbl;
    void dfs(TreeNode* curr, TreeNode* prev){
        if(!curr)
            return;
        parent[curr] = prev;
        dfs(curr->left, curr);
        dfs(curr->right, curr);
        if(!curr->left && !curr->right)
            leaves.push_back(curr);
    }
    int isGood(TreeNode* node, int& limit){
        for(int dist = 0; dist < limit && node != nullptr; dist++){
            //if(distanceTbl.count(node) && distanceTbl[node] + dist <= limit)
            //    return 1;
            if(distanceTbl.count(node)){
                if(distanceTbl[node] + dist <= limit)
                    return 1;
                else
                    return 0;
            }
            node = parent[node];   
        } 
        return 0;
    }
};
