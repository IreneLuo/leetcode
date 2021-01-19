class Solution {
    /* solution 1: Bellman-Ford
     * Find the max length from k to other nodes
     * If not all the nodes are reachable, return -1
     *
     * For more analysis, see HuaHua's video
     */
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        /* N <= 100, w<=100, so we know that
         * the max time of node u->v will < 101*100
         */
        int MAX_TIME = 101*100;
        /* distance from k to each node */
        vector<int> dist(N, MAX_TIME);
        dist[K-1] = 0;
        for(int n = 0; n < N; n++){
            for(int i = 0; i < times.size(); i++){
                int start = times[i][0] - 1, end = times[i][1] - 1, d = times[i][2];
                dist[end] = min(dist[end], dist[start] + d);
            }
        }
        
        /* reference the max item in dist */
        int ans = *max_element(dist.begin(), dist.end());
        return ans == MAX_TIME ? -1 : ans;
    }
};
