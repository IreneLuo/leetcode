/* solution: BFS + queue
 * The key to understand how to solve this kind of problem is noticing
 * each of these arrays are entities
 * each of these keys are relationships that map the entities with each other
 * so when we think about "entities", "relationships" or "dependencies" --> we can think about "graph"
 *  --> we can now model the problem: graph
 *  --> method: BFS + queue
 *
 * time complexity = |V| + |E| = rooms + keys = O(R+K)
 *  - V = rooms
 *  - E = |keys| //for loop
 *  for the whole process, we do v1+v1keys+v2+v2keys+..+vn+vnkeys =|V| + |E|
 * space complexity = |V| = rooms //for the rooms that we push into the queue
 */
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        if(rooms.size() == 0)
            return true;

        queue<int> q;
        set<int> seen;
        //initialize queue and hashtbl for the start
        int start = 0;
        q.push(0);
        seen.insert(0);
        //find out the keys in this room
        while(!q.empty()){
            int curr_room = q.front();
            q.pop();
            for(int key : rooms[curr_room]){
                if(seen.find(key) == seen.end()){
                    q.push(key);
                    seen.insert(key);
                    //if we've seen all the nodes, return true
                    if(seen.size() == rooms.size())
                        return true;
                }
            }
        }
        return seen.size() == rooms.size();
    }
};
