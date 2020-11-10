/*
 * Model: graph
 *   - note that when we have a graph problem, we don't consider it as a connected graph
 *   - it might be a partial-connected graph that have several subgraph
 * Method: 
 *  - BFS: is good for regions, level by level
 *  - DFS: following path
 *
 */
/* solution: DFS
 * (Detect A Cycle In A Graph (Deadlock Detection))
 * Model: graph
 *  - it's a problem of detecting a cycle(deadlock) in a graph.
 *  - if a cycle is found, then the prerequisites are impossible to take
 * Method: DFS (to explore the path)
 * Main concept:
 *   1. use colors to idendity the status of the node
 *      - white: uninvestigate
 *      - gray: investigating
 *      - black: investigated
 *   2. In our dfs funtion, we visit a white node, change the color of it to gray and explore all the adjacents of it.
 *      If we find an ajdacent is gray, return false since it means that this adjacent has been visited, so there must
 *      a cycle in this graph.
 *      If we explore all the adjacents of it and no gray adjacents are found, then change this node to black.(A black
 *      node means we've already visited all the nodes from this node and there's nothing cycle inside)
 * time complexity = |V|+|E| = numCourses + #set in prerequisites
 * space complexity = |V|
 */
enum Color{
    White,
    Gray,
    Black
};
class Node{
public:
    int id;
    int color;
    vector<Node*> adj;
    Node(int i, int c): id(i), color(c) {};
};
class Solution {
public:
    vector<Node*> courses;
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        initialize_nodeinfo(numCourses, prerequisites);
        //we cannot consider all the nodes in this are connected, so
        //we must traverse all the node to check if there's any deadlock
        for(int i = 0; i < numCourses; i++){
            //only look for white nodes
            if(courses[i]->color == White && !dfs_detect_cycle(courses[i]))
                return false;
        }   
        return true;
    }
    //construct all the nodes info(id, color, adj)
    void initialize_nodeinfo(int numCourses, vector<vector<int>>& edges){
        for(int i = 0; i < numCourses; i++){
            Node* n = new Node(i, White);
            courses.push_back(n);
        }
        for(vector<int> edge : edges){
            int to = edge[0];
            int from = edge[1];
            (courses[from]->adj).push_back(courses[to]);
        }
    }
    bool dfs_detect_cycle(Node* curr){
        if(curr->color == Gray)
            return false;
        //if the color of this course is White, change the color to Gray, and make a recursive call to explore its adjacents
        curr->color = Gray;
        vector<Node*> adj = curr->adj;
        for(Node* n : adj){
            if(n->color!=Black && !dfs_detect_cycle(n))
                return false;
        }
        //after traversing all the adjacents, change the color to black
        curr->color = Black;
        return true;
    }
};
