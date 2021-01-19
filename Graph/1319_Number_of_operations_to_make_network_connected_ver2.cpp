class Solution {
    /* solution 1: join-find algorithm
     * Reference: HuaHua's video
     */
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if(connections.size() < n-1) return -1;
        /* initialize the parent info for each node
         * iota(start, end, val) will increase 1 to each item
         * and item will start from val
         * Ex: [[0,1],[0,2],[0,3],[1,2],[1,3]] n = 6

         * 1. join
         *       0 1 2 3 4 5
         * -----------------------------------------
         *       0 1 2 3 4 5  init  
         *       1 1 2 3 4 5  [0,1]: parent[find(0)] = 1
         *       1 2 2 3 4 5  [0,2]: parent[find(0)] = parent[1] = 2
         *                                  =parent[0] = find(1) = parent[1] = 1
         *       2 2 3 3 4 5  [0,3]: parent[find(0)] = 3
         *                                  =parent[0] = find(1) = parent(1) = 2
         *       2 3 3 3 4 5  [1,2]: parent[find(1)] = 3 --> parent[1] = find(1) = parent[2] = find(2) = parent[3]
         *                                  =parent[1] = find(3) = 3
         *       2 3 3 3 4 5  [1,3]: parent[3] = 3 --> parent[1] = find(1) = parent[2] = find(2) = parent[3]
         *
         * 2. count
         *       2 3 3 3 4 5  for i = 0 ~ 3, just insert 3
         *                     i=4, insert 4
         *                     i=5, insert 5
         *    size = 3 --> ans = 3-1=2
         *
         * time complexity = O(V+E)
         * space complexity = O(E)
         */
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);
        /* join all the nodes time:O(E)*/
        for(const vector<int>& v: connections){
            /* if v=[a, b]
             * set parent[a's parent] = b's parent
             */
            parent[find(v[0], parent)] = parent[find(v[1], parent)];
        }
        
        /* count the number of connected components time:O(V)*/
        unordered_set<int> s;
        for(int i = 0; i < n; i++){
            s.insert(find(i, parent));
        }
        return s.size() - 1;
    }
    int find(int curr, vector<int>& parent){
        if(parent[curr] == curr)
            return curr;
        parent[curr] = find(parent[curr], parent);
        return parent[curr];
    }
};
