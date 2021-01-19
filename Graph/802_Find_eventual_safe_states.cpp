class Solution {
    /* solution: DFS
     * A node is safe if we can reach in k or <= k steps
     * A node is unsafe if we cannot reach in k or <= k steps
     * and k is a natural number
     * ==> this means a node is unsafe if it's in a circle
     * Example1 in the problem:
     *   0 is unsafe because 0->1->3->0
     *   1 is unsafe because 1->3->0->1
     *   3 is unsafe because 3->0->1->3
     *  so only 2,4,5,6 are safe
     *
     *  time complexity = O(|v|+|e|)+O(|v|log|v|)
     *  space complexity = O(|v|+|e|)
     *  Reference: HuaHua's video
     */
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> ans;
        statetbl = vector<State>(graph.size(), UNKNOWN);
        for(int i = 0; i < graph.size(); i++){
            if(dfs(graph, i) == SAFE)
                ans.push_back(i);
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
private:
    enum State {UNKNOWN, VISITING, UNSAFE, SAFE};
    vector<State> statetbl;
    State dfs(vector<vector<int>>& graph, int curr){
        //it's a cycle
        if(statetbl[curr] == VISITING) 
            return UNSAFE;
        //curr node is SAFE or UNSAFE, return the result directly
        if(statetbl[curr] != UNKNOWN)
            return statetbl[curr];
        //if curr node is UNKNOWN, set it to VISITING
        statetbl[curr] = VISITING;
        //visit all the neighbors of curr node
        for(int nb: graph[curr]){
            if(dfs(graph, nb) == UNSAFE){
                statetbl[curr] = UNSAFE;
                return statetbl[curr];
            }
        }
        //if all the neighbors are SAFE, then curr node must be SAFE
        statetbl[curr] = SAFE;
        return statetbl[curr];
    }
};
