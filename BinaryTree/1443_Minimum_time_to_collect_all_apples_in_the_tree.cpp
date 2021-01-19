class Solution {
        /* Consider 2 situations:
         *  - if a subtree has apples, then cost + 2
         *  - if root of a subtree has an apple, then cost + 2
         *    note that 2 is one way to the subtree + one way back to curr node
         * If the edges are in ordered, each edge = parent -> child
         * then we can use dfs() directly
         * If the edges are unordered, we have to build an undirected graph
         * to connect all the nodes, and add a seen tbl to ensure that each
         * node is accessed only once.
         *
         * time complexity = O(n)
         * space complexity = O(n)
         * 
         */
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        /* 1. if edges are ordered
        vector<vector<int>> adjlist(n);
        for(vector<int> e: edges)
            adjlist[e[0]].push_back(e[1]);
        return dfs(0, adjlist, hasApple);
        */
        /* 2. if edges are unordered */
        vector<int> seen(n, 0);
        vector<vector<int>> adjlist(n);
        for(vector<int> e: edges){
            adjlist[e[0]].push_back(e[1]);
            adjlist[e[1]].push_back(e[0]);
        }
        return dfs(0, adjlist, hasApple, seen);
    }
    /* 1. if edges are ordered
    int dfs(int curr, vector<vector<int>>& adjlist, vector<bool>& hasApple){
        int ans = 0;
        for(int nb: adjlist[curr]){
            int cost = dfs(nb, adjlist, hasApple);
            if(cost > 0 || hasApple[nb])
                ans += 2 + cost;
        }
        return ans;
    }
    */
    int dfs(int curr, vector<vector<int>>& adjlist, vector<bool>& hasApple,
           vector<int>& seen){
        int ans = 0;
        seen[curr] = 1;
        for(int nb: adjlist[curr]){
            if(seen[nb]) continue;
            int cost = dfs(nb, adjlist, hasApple, seen);
            if(cost > 0 || hasApple[nb])
                ans += 2 + cost;
        }
        return ans;
    }
};
