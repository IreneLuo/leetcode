class Solution {
    /* solution 1: dfs
     * We color the nodes in red or blue to seperate them
     * Ex: 1->2->4
     *     |->3
     *
     *    after coloring: 1(r) -> 2(b) -> 4(r)
     *                     |----> 3(b)
     *    If a color conflict occurs, then the graph is not a bipartition
     *
     *  time complexity = O(|V|+|E|)
     *  space complexity = O(|V|+|E|)
     *  Reference: HuaHua's video
     *  Similar: leetcode 785
     */
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        /* build adjlist
         * e[0]=from, e[1]=to
         * since number starts from 1 to N, so we use number-1 as our index of nodes
         * time: O(|E|)
         */
        adjlist = vector<vector<int>>(N);
        for(vector<int>& e: dislikes){
            adjlist[e[0]-1].push_back(e[1]-1);
            adjlist[e[1]-1].push_back(e[0]-1);
        }
        /* color table
         * 0:no color, 1:red, -1:blue
         */
        colored = vector<int>(N, 0);
        /* iterate all the nodes */
        for(int i = 0; i < N; i++){
            if(colored[i] != 0) continue;
            if(!dfs(i, 1)) return false;
        }
        return true;
    }
private:
    vector<vector<int>> adjlist;
    vector<int> colored;
    bool dfs(int curr, int color){
        colored[curr] = color;
        for(int nb: adjlist[curr]){
            //color confict!
            if(colored[nb] == color) return false;
            //if(colored[nb] == !color) continue;
            if(colored[nb] == 0 && !dfs(nb, -color)) return false;
        }
        return true;
    }
};
