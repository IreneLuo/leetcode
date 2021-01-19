class Solution {
    /* solution 1: find the smallest distance - Floyd-Warshall
     * Main concept of finding a minimum path:
     *  d[u][v] = d[u][k]+d[k][v]
     * Example: [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], threshold = 4
     *
     *        table d: (init)
     *              0  1  2  3
     *          -|--------------
     *          0|  m  3  m  m
     *          1|  3  m  1  4
     *          2|  m  1  m  1
     *          3|  m  4  1  m
     *
     *        table d: (processing)
     *              0  1  2  3
     *          -|--------------   for k = 0 to 3, we iterate every two node
     *          0|  6  3  4  7     to find the smallest distance
     *          1|  3  2  1  2
     *          2|  4  1  2  1 
     *          3|  5  2  1  2  
     *        Last, we cnt the numbers of edges that <= threshold
     *        and return the node that has the smallest count.
     *
     * time complexity = n^3
     * space complexity = n^2
     * For dijkstra solution, see HuaHua's video
     */
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> d(n, vector<int>(n, INT_MAX/2));
        /* initialize d
         * edge[0] = from, edge[1] = to, edge[2] = distance
         */
        for(auto edge: edges){
            d[edge[0]][edge[1]] = edge[2];
            d[edge[1]][edge[0]] = edge[2];
        }
        /* find the smallest path of each node */
        for(int k = 0; k < n; ++k)
            for(int u = 0; u < n; ++u){
                //min(d[u][u]+d[u][v], d[u][u]) must be d[u][u]-> so skip
                if(u == k) continue;
                for(int v = 0; v < n; ++v)
                    d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
            }
        /* count the neighbors of a node whose distance <= distanceThreshold*/
        int ans = -1;
        int min_count = INT_MAX;
        for(int u = 0; u < n; ++u){
            int cnt = 0;
            for(int v = 0; v < n; ++v){
                if(u != v && d[u][v] <= distanceThreshold){
                    cnt++;
                }
            }
            /* if more than 2 nodes have same count, choose the greater one */
            if(cnt <= min_count){
                min_count = cnt;
                ans = u;
            }
        }
        return ans;
    }
};
