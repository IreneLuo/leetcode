class Solution {
    /* solution: bfs + queue
     * Note that we use color to indicate that the adjacents of mine is in the other set or not.
     * ex: E(A,B) --> A and B must be different color, since the character of bipartited graph
     *     so A must find out all the adjacents of it and mark their colors as an oppisite color.
     *     That means if A find an adjacent that has a same color as A's, then it must not be a bipartitied graph.
     * Method
     * 1. pick up a start node and push it into the queue, mark it as visited
     * 2. search all the adjacents of target node
     *    1. if adjacent is uncolored: color it
     *    2. if adjacent is colored: return false if color of adjacent are as same as target node
     *    3. if adjacent is visited or not: mark it as visited if not, and push it to the queue
     *
     * time complexity = O(|V|+|E|)
     *   - actually, we will look at every edge twice since it's a undirectional graph
     *     so |V|+2|E| = |V|+|E|
     *   - we won't visit the vertex again if we've visited it.
     *
     * space complexity = O(|V|) //not sure
     */
enum color{
    WHITE,
    BLACK,
    NON_COLORED,
};
public:
    bool isBipartite(vector<vector<int>>& graph) {
        if(graph.size() == 0)
            return false;
        queue<int> q;
        vector<bool> visited(graph.size(), false);
        vector<int> coloring(graph.size(), NON_COLORED);
        int start = 0;
        for(int i = 0; i < graph.size(); i++){
            if(!visited[i]){
                start = i;
                q.push(start);
                //it's a undirected graph, so we record the status of visit to avoid infinite loop
                visited[start] = true;
                coloring[start] = WHITE;
                while(!q.empty()){
                    int curr = q.front();
                    q.pop();
                    //find out all the adjacents of the front node in queue
                    for(auto adj: graph[curr]){
                        if(coloring[adj] == NON_COLORED)
                            coloring[adj] = (coloring[curr] == WHITE) ? BLACK: WHITE;
                        if(coloring[adj] == coloring[curr])
                            return false;
                        if(!visited[adj]){
                            visited[adj] = true;
                            q.push(adj);
                        }
                    }
                }
            }
        }
        return true;
    }
};
