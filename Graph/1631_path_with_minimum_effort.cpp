/* solution: dijkstras' algorithm
 * time complexity = O(|V|+|E|)
 *  - initialize = m*n //for loop
 *  - while loop = |V| + |E|
 * space complexity = O(|V|) = O(mn)
 */

/* Example:         
 *             A(1)--1---B(2)---0--C(2)
 *              |         |         |
 *              | 2       | 6       | 0
 *              |         |         |
 *             D(3)--5---E(8)---6--F(2)
 *              |         |         |
 *              | 2       | 5       | 3
 *              |         |         |
 *             G(5)--2---H(3)---2--I(5)
 * 
 *      Note that:
 *      For E, we might push <E, 6>, <E, 5> and <E, 5> into the min-Heap,
 *      since E has neighbors B, D, H.
 *      <E, 6>: B->E has a min effort 6
 *      <E, 5>: D->E and H->E has a min effort 5
 *      so we cannot push a pointer(points to E) into the min-Heap
 *      because the min effort stored in nodeset table will be changed at any time
 *      and that's why in line 147 we copy the node info of E and push it into the heap
 */
/* struct Node
 *    id: id of a node, was calculated by row and col
 *    row: row position in the input
 *    col: col position in the input
 *    min_effort: the minimum distance from start(0, 0) to this node
 *    from: the node that has a min effort to this node
 *    height: raw data of this node in the input
 */
struct Node{
    int id;
    int row;
    int col;
    int min_effort;
    int from;
    int height;
    Node(int i, int r, int c, int m, int f, int h):
                id(i), row(r), col(c), min_effort(m), from(f), height(h){};
};
/* A customized operator to build a min-Heap
 * (use a>b then the smallest item will be pop up to the top)
 */
class myGreater{
public:
    bool operator()(const Node* a, const Node* b){
        return (a->min_effort) > (b->min_effort);
    }
};
class Solution {
public:
    /* we create a vector "nodeset" to bind all the nodes info.
     *    <nodeset>     id   row col   minEffort  ...
     *    ptr   ----->  A    0   0     INT_MAX   ...
     *    ptr   ----->  B    0   1     INT_MAX   ...
     *    ...   -----> ...
     */
    void construct_nodes_info(vector<vector<int>>& heights, int col_len, int row_len,
                         vector<Node*>& nodeset, int start, vector<int>& seen){
        //construct info of each node
        for(int row = 0; row < row_len; row++){
            for(int col = 0; col <col_len; col++){
                Node* node = new Node((row * col_len) + col, row, col,
                                      INT_MAX,-1, heights[row][col]);
                nodeset.push_back(node);
            }
        }
        //set starting point's info
        nodeset[start]->min_effort = 0; //self to self dosen't has any distance, so set to 0
        nodeset[start]->from = -1;      //-1 means it is the staring point
        seen.resize(row_len*col_len, 0);
    }
    int minimumEffortPath(vector<vector<int>>& heights) {
        int col_len = heights[0].size();
        int row_len = heights.size();
        vector<Node*> nodeset;
        priority_queue<Node*, vector<Node*>, myGreater> pq; //min-Heap--> each time we have to choose the node who has min effort
        vector<int> seen; //to record the node has been visited or not
        
        //initialize the starting node
        int start = 0;
        int end = col_len * row_len - 1;

        construct_nodes_info(heights, col_len, row_len, nodeset, start, seen);
        pq.push(nodeset[start]);

        /* four directions
         *  left : 0, -1
         *  up   : -1, 0
         *  right: 0, 1
         *  down : 1, 0
         */
        int directions[5] = {0, -1, 0, 1, 0};
        while(!pq.empty()){
            //retrieve the node who has a min effort
            Node* curr = pq.top();
            pq.pop();
            //if curr node is the target node, stop the while loop
            if(curr->id == end)
                break;

            //if the info of this node from min-Heap is not the latest info, ignore it
            if(curr->min_effort > nodeset[curr->id]->min_effort)
                continue;
            seen[curr->id]++;

            //check all the adjacency nodes of curr node
            for(int d = 0; d < 4; d++){
                int adj_row = (curr->row) + directions[d];
                int adj_col = (curr->col) + directions[d+1];
                //if out the boundary, ignore it
                if(adj_row < 0 || adj_row >= row_len || adj_col < 0 || adj_col >= col_len)
                    continue;
                int adj_id = adj_row * col_len + adj_col;
                //if the adjacency node has been visited, ignore it
                if(seen[adj_id] > 0)
                    continue;
                /*  Calculate the effort of the path:
                 *       (xxx)--->curr--->adj
                 *             x       y
                 *  x = the min effort of (a set of nodes -> curr node)
                 *  y = the distance of (curr node -> adj node)
                 *  ==> due to the problem's definition
                 *      temp_effort = max(x, y)
                 *  However, if we've already known there's a node Z -> adj node has
                 *  a min effort = z, so we have to keep the minimum one 
                 *  ==> adj->min_effort = min(adj->min_effort, temp_effort)
                 *
                 */
                Node* adj = nodeset[adj_id];
                int temp_effort = max(curr->min_effort, abs(adj->height - curr->height));
                // if temp_effort isn't smaller than the min_effort of adj
                // we won't push it into the queue (to save more time)
                if(temp_effort > adj->min_effort){
                    continue;
                }
                adj->min_effort = temp_effort;
                adj->from = curr->id;
                Node* newadj = new Node(adj->id, adj->row, adj->col, 
                                        adj->min_effort , adj->from, adj->height);
                pq.push(newadj);
            }
        }
        return nodeset[end]->min_effort;
    }
};
