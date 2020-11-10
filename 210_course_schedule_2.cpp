/* solution: 
 *  It's a topological ordering problem.
 *  time complexity = O(|V| + |E|) //building adjlist and deal with the queue
 *  space complexity = O(|V|)      //not sure
 */
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        //1. construct adjacent lists for each node
        //2. construct an indegree table
        unordered_map<int, list<int>> adjlist;
        unordered_map<int, int> indegree;
        for(int i = 0; i < prerequisites.size(); i++){
            int from = prerequisites[i][1];
            int to = prerequisites[i][0];
            adjlist[from].push_back(to);
            indegree[to]++;
        }
        //3. push the node whose indegree is 0 into the queue
        queue<int> q;
        for(int i = 0; i < numCourses; i++){
            if(indegree[i] == 0)
                q.push(i);
        }
        //4. pop out the node in queue, add it to the answer (the nodes in queue must be indegree=0)
        vector<int> ans;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            ans.push_back(node);
            //5. traverse the adjacents nodes and destroy the edge to them
            // ex: 0->1 : ind(0)=0, ind(1)=1
            //     now we pop out 0, so imagine that no one can reach 1, so we must decrease indegree of 1 to 0 (ind(1)=0)
            for(auto it : adjlist[node]){
                indegree[it]--;
                //once any of node's indegree is zero, then push it to the queue
                if(indegree[it] == 0){
                    q.push(it);
                }
            }
        }
        //if the graph is cyclic, then a topological ordering cannot be presented
        //the way to know this situation is checking the ans size.
        //if this graph is cyclic, then some of its nodes' indegree must be non-zero
        //and cannot be push to the queue, so the size of ans will different with numCourse(num of total nodes)
        if (ans.size() != numCourses)
            ans.clear();
        return ans;
    }
};
