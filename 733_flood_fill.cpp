/* solution: BFS + queue
 * time complexity = O(m*n)
 *   - V = how many total points that we can have at maximum = m*n
 *   - E <= 4mn (approximately) --> we can say that E = O(mn)
 *     ex: for a 3 * 3 matrix, each node has different amount of edges(that is directions to choose)
 *         [2 3 2]
 *         [3 4 3]  --> so the upper bound for each node will be 4, and total  = 4mn for mn nodes
 *         [2 3 2]
 *   - we use BFS here, and for BFS, the time complexity = |V|+|E| = 5mn = O(mn)
 *  space complexity = (m*n)
 */
class Solution {
    class Node{
    public:
        int row;
        int col;
        int color;
        Node(int r, int c, int co){
            row = r;
            col = c;
            color = co;
        }
    };
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        queue<Node*> q;
        set<Node*> visited;
        const int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        int start_color = image[sr][sc];
        //for edge case like
        // [0 0 0]
        // [0 1 1] start = {1,1}, newColor = 1
        // starting node and its adjacency nodes will be modified to 1
        // however image[next_row][next_col] == start_color --> this statement will always be true
        // and lead to a infinity loop
        // so we bypass this case.
        if(start_color == newColor)
            return image;

        //initialize the starting point
        Node* start = new Node(sr, sc, image[sr][sc]);
        q.push(start);
        visited.insert(start);
        //find out all the adjacency points of starting point
        while(!q.empty()){
            Node* curr = q.front();
            image[curr->row][curr->col] = newColor;
            q.pop();
            for(int dir = 0; dir < 4; dir++){
                int next_row = curr->row + directions[dir][0];
                int next_col = curr->col + directions[dir][1];
                //check if the next point will out of bound
                if(!is_valid(next_row, next_col, image))
                   continue;
                //if this new point has not visited yet and the color of it equals to the start color
                //we add it to the queue and mark it as visited
                Node* next = new Node(next_row, next_col, image[next_row][next_col]);
                if(visited.find(next) == visited.end() && image[next_row][next_col] == start_color){
                    q.push(next);
                    visited.insert(next);
                }
            }
        }
        return image;
    }
    bool is_valid(int row, int col, vector<vector<int>>& image){
        if(row < 0 || row >= image.size())
            return false;
        if(col < 0 || col >= image[0].size())
            return false;

        return true;
    }
};
