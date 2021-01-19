class Solution {
    /* solution 1: dfs
     * Key point:
     *   If we have n-1 cables, we can connect n computers together
     * Method:
     *   We use dfs() to find the number of connected components (cc)
     *   and the answer = cc-1 (since cc components need cc-1 cables to connect together)
     *
     * Time complexity = O(V+E)
     * Space complexity = O(V+E)
     * Reference: HuaHua's video
     */
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if(connections.size() < n-1) return -1;
        /* build an adjlist:
         * It's an undirected graph, so for an entry [a,b] in connections,
         * we set adjlist[a] = b and adjlist[b] = a
         * Note that don't use adjlist(n, vector<int>(n)) -> lead to a memory limit timeout
         * time: O(E)
         * space: O(E)
         */
        vector<vector<int>> adjlist(n);
        for(auto& v: connections){
            adjlist[v[0]].push_back(v[1]);
            adjlist[v[1]].push_back(v[0]);
        }
        /* visited: record the node has been visited or not
         * cc_count: count the number of connected components
         */
        vector<int> visited(n);
        int components = 0;
        /*
        function<void(int)> dfs = [&](int idx){
            //check the neighbors of current node
            for(int nb: adjlist[idx]){
                if(!visited[nb]++)
                    dfs(nb); 
            }
        };
        */
        /* Visit all the nodes if this node hasn't been visited yet
         * time: O(V)
         * space: O(V)
         */
        for(int i = 0; i < n; ++i){
            if(!visited[i]){
                ++components;
                dfs(i, adjlist, visited);
            }
        }
        return components - 1;
    }

    void dfs(int idx, vector<vector<int>>& adjlist, vector<int>& visited){
        ++visited[idx];
        //check the neighbors of current node
        for(int nb: adjlist[idx]){
            if(!visited[nb])
                dfs(nb, adjlist, visited); 
        }
    }
};
