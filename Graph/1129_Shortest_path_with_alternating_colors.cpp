class Solution {
    /* solution: BFS
     * What do we use:
     *  1 queue, 4 vector tables
     *  state=node, color
     *  start = 0,0 / 0,1
     *
     * time complexity = O(|V|+|E|)
     * space complexity = O(|V|+|E|)
     *
     * Example: n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
     *          ---0----     q          size   curr  color  push       step
     *          |  ^   |    (0,0)(0,1)   2
     *          v  |   v    (0,1)        1     (0,0)  r    (1,0)(2,0)  [0]=0
     *          1---   2    (1,1)(2,1)   2     (0,1)  b    -           [0]=0
     *                      (2,1)        1     (1,1)  b    (0,0)       [1]=1
     *                      (0,0)        1     (2,1)  b    -           [2]=1
     *                                         (0,0)  r    -           -
     */
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        /* Build adjlist_r and adjlist_b for red edges and blue edges
         * Why we use unordered_set here?
         *   There could be some self-edges or parallel edges.
         *   so use unordered_set can eliminate those dup edges
         */
        vector<unordered_set<int>> adjlist_r(n);
        vector<unordered_set<int>> adjlist_b(n);
        //e[0]=from, e[1]=to
        for(const auto& e: red_edges)
            adjlist_r[e[0]].insert(e[1]);
        for(const auto& e: blue_edges)
            adjlist_b[e[0]].insert(e[1]);
        /* Build seen_r, seen_b table to record the node has been seen or not */
        vector<int> seen_r(n);
        vector<int> seen_b(n);
        /* a queue to save the neighbors that we want to visit
         * (node, color)
         *          |--> so we know which color to choose next
         */
        queue<pair<int, int>> q;
        /* start from node 0, and we migt choose red or blue to start */
        q.push({0, 0});//use {} to pair it
        q.push({0, 1});
        /* There are two possible ways: start from red or blue
         * so we use two seen table to track each possible way
         */
        ++seen_r[0];
        ++seen_b[0];
        vector<int> ans(n, -1);
        int steps = 0;
        /* bfs() */
        while(!q.empty()){
            //save the number of nodes of this layer
            int size = q.size();
            while(size--){
                int v = q.front().first;
                int is_red = q.front().second;
                q.pop();
                //if ans[v] == -1, update it directly.
                ans[v] = (ans[v] > 0) ? min(ans[v], steps) : steps;
                const unordered_set<int>& adjlist = is_red ? adjlist_r[v] : adjlist_b[v];
                vector<int>& seen = is_red ? seen_r : seen_b;
                for(const int& nb: adjlist){
                    if(seen[nb]) continue;
                    seen[nb]++;
                    q.push(pair<int, int>(nb, !is_red));
                }
            }
            //we've seen all nodes in this layer, steps++
            steps++;
        }
        return ans;
    }
};
