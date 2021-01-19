class Solution {
    /* solution: DFS
     * The problem is :
     *    find the max number of connected components in the graph
     * Method:
     *  1. Create a vector visited to record each node has been visited or not
     *  2. Iterate over each node
     *     1. Mark current node as visited
     *     2. Visit its friends
     *     3. Mark friends as visited until we find a visited node
     * time complexity = O(m^2)
     * space complexity = O(m)
     * 
     * Note:
     *  We can optimize space to O(1) by modified M[i][j] to 0 when visit instead of
     *  creating a vector to record the status of visit.
     *  However this approach might not good enough since
     *     1. M might be a const input--> we cannot change a const input
     *     2. Modifying M (a 2-D vector) will increase the time
     * Reference: HuaHua's video
     * Similar: Leetcode 200. number of islands
     */
public:
    int findCircleNum(vector<vector<int>>& M) {
        if(M.empty())
            return 0;
        int n = M.size();
        int ans = 0;
        vector<int> visited(n, 0);
        //iterate everyone
        for(int i = 0; i < n; i ++){
            if(visited[i])
                continue;
            dfs(M, i, visited);
            ++ans;
        }
        return ans;
    }
    void dfs(vector<vector<int>>& tbl, int curr, vector<int>& visited){
        /* ignore this checking because we will check if a friend has been visited or not
           before we call dfs() (save more time)
        if(visited[curr])
           return;
        */
        visited[curr] = 1;
        for(int i = 0; i < tbl.size(); i++){
            //visit all friends
            if(tbl[curr][i] == 1 && !visited[i])
                dfs(tbl, i, visited);
        }
    }
};
