class Solution {
    /* solution 1: dfs
     *
     * Each character = vertex
     * Pairs = edges
     *
     * WE use dfs() to find all the connected components in this graph.
     * For each component, we sort the items and idx
     * then place them into the string
     *
     * time complexity = O(|V| + |V|log|v|)
     *   - worst case: sort v items in a connected component
     *                 --> vlogv
     *                 --> we only have 1 connected component -> O(|V|log|v|)
     *   - best case: sort 1 items in a connected component
     *                --> 1
     *                --> we have n connected component -> O(|V|)
     * space complexity = O(|V|)
     * 
     * Example:
     *    s = dcab  pairs = [[0,3],[1,2],[0,2]]
     *            |--|
     *         d  c  a  b
     *         |--------|
     *    Round 1: temp = db --> sort: bd --> component 1
     *             idx=  03  --> sort: 03
     *             --> s = bcad (we've changed idx0 and idx3)
     *    Round 2: temp = ca --> sort: ac --> component 2
     *             idx = 12  --> sort: 12
     *             --> s = bacd (we've changed idx1 and idx2)
     *    ans = bacd#
     *
     * solution 2: union-find algorithm
     * Reference: HuaHua's video
     */
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        /* build an adjlist (store index of its neighbors)
         * pairs = [a,b] -> set adjlist[a] = b
         *                      adjlist[b] = a
         * time: O(V)
         */
        int n = s.length();
        vector<vector<int>> adjlist(n);
        for(const auto& e: pairs){
            adjlist[e[0]].push_back(e[1]);
            adjlist[e[1]].push_back(e[0]);
        }
        vector<int> visited(n);
        string temp;
        vector<int> idx;
        //time: O(VlogV)
        for(int i = 0; i < n; i++){
            if(visited[i]) continue;
            temp.clear();
            idx.clear();
            dfs(i, visited, adjlist, temp, idx, s);
            sort(temp.begin(), temp.end());
            sort(idx.begin(), idx.end());
            for(int j = 0; j < idx.size(); j++)
                s[idx[j]] = temp[j];
        }
        return s;
    }
    void dfs(int i,  vector<int>& visited, vector<vector<int>>& adjlist,
            string& temp, vector<int>& idx, string& input){
        visited[i]++;
        temp += input[i];
        idx.push_back(i);
        /* find all the neighbors of i and add it to temp and idx
         */
        for(int nb: adjlist[i]){
            if(visited[nb]) continue;
            dfs(nb, visited, adjlist, temp, idx, input);
        }
    }
};
