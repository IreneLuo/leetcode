class Solution {
    /* solution 1: bitmask + bfs
     *  1. Create a bitmask to represent a subset
     *       - bit i: node i is in this subset or not
     *         1 is yes, 0 is no
     *       - Example: bitmask 0x3 = node 1, 2, are in this subset
     *  2. For each subset, we use two bfs() to find the max diameter of it
     *      - bfs(start, seentbl) -> start from the first node in this subset
     *                               find a furthest node f1 in this subset
     *      - bfs(f1, seentbl2) -> start from the farthest node f1, and find
     *                             another furthest node f2, then the max
     *                             diameter = length(f1~f2)
     *  Since after bfs(start, seentbl), seentbl will be changed, so we copy
     *  seentbl to seentbl2 before bfs(start, seentbl) to make sure that traverse
     *  from f1 to f2 won't fail
     *  
     *  Note that, we could also use dfs() instead of bf() here.
     *  time complexity = O(2^n * n)
     *      - combination(all possible subsets) = O(2^n)
     *      - 2* bfs(find the max distance of two nodes) = O(n)
     *  space complexity = O(n)
     *  Similar: 1245 tree diameter
     *  Reference: HuaHua's video(DP solution)
     */
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        vector<int> ans(n-1, 0);
        /* build an adjlist */
        adj = vector<vector<int>>(n);
        for(const auto& e: edges){
            adj[e[0]-1].push_back(e[1]-1);
            adj[e[1]-1].push_back(e[0]-1);
        }
        /* enumerate all the possible subsets */
        for(int m = 1; m < (1<<n); m++){
            //init the subset and seen tbl for this subset
            subset = vector<int>(n, -1);
            /* set the nodes in this subset as candidates of seen */
            for(int i = 0; i < n; i++)
                if(m & (1<<i)) subset[i] = 0;
            seen = vector<int>(subset.begin(), subset.end());
            /* only 1 node in a subtree is not valid, so skip it */
            if(__builtin_popcount(m) <= 1) continue;
            /* bfs() return
             *       - max distance of this subset
             *       - max count of nodes of this subset
             *       - furthest node
             * the first bfs() we start from the first node(the first i that m[i] is 1)
             * to traverse the subset, until we visit the furtherst node
             * the second bfs() we start from the furthest node and traverse the subset
             * until we visit another furtherst node, the max distance will be our answer
             */
            data ret = bfs(__builtin_ctz(m), subset);
            /* if the count the nodes != the number of all nodes in this subset
             * we skip this subset since it's not a connect component
             */
            if(ret.max_cnt != __builtin_popcount(m)) continue;
            ret = bfs(ret.furthest_node, seen);
            ++ans[ret.max_dist-1];
        }
        return ans; 
    }
private:
    struct data{
        int max_dist;
        int max_cnt;
        int furthest_node;
        data(int d, int c, int f): max_dist(d), max_cnt(c), furthest_node(f) {}
    };
    vector<vector<int>> adj;
    vector<int> seen;
    vector<int> subset;
    queue<int> q;
    data bfs(int curr, vector<int>& seentbl){
        int node = curr;
        int member_cnt = 0;
        /* if subset = 1,2 and dist = -1, member_cnt = 0
         * when we visit 1, dist = 0, member_cnt = 1
         * when we visit 2, dist = 1, member_cnt = 2
         */
        int dist = -1;
        q.push(curr);
        while(!q.empty()){
            int size = q.size();
            while(size--){
                node = q.front(); q.pop();
                ++member_cnt;
                seentbl[node] = 1;

                for(int nb: adj[node]){
                    if(seentbl[nb] == 0) {
                        q.push(nb);
                    }
                }
            }
            ++dist;
        }
        return data(dist, member_cnt, node);
    }
};
