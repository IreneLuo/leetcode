/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

/* Solution:
 * Method: BFS + hashmap
 * time complexity = |V|+|E|
 *   - note that it's an undirected graph, so actually we access each edge twice: (A->B) & (B->A)
 * space complexity = |V|
 * ex:   V = A, B   E = {A,B} 
 *       hashtbl         note> A'and B' are the clones of A and B
 *       A      A'   --> we push <A, A'> into hashtbl when intialize, also push A into the queue
 *                       then we retrieve the top of the queue = A, and add all adjacents of A into hashtbl
 *       B      B'   --> B is the adjacent of A, so we add <B, B'> to the hashtbl
 *                       now we must create the relationship between A' and B'
 *                       --> A'->neighbor.push_back( hashtbl[B]) to add B' into the neighbor list of A'
 */
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(node == NULL)
            return NULL;

        unordered_map<int, Node*> hashtbl;
        queue<Node*> q;

        //initialize
        q.push(node);
        //Node* clone = new Node(node->val);
        hashtbl.insert(make_pair (node->val, new Node(node->val)));
        while(!q.empty()){
            Node* curr = q.front();
            q.pop();
            for(Node* adj : curr->neighbors){
                if(hashtbl.find(adj->val) == hashtbl.end()){
                    q.push(adj);
                    hashtbl.insert(make_pair(adj->val, new Node(adj->val)));
                }
                //neighbor(clone of curr node) = neighbor(clone of curr node's adj)
                hashtbl[curr->val]->neighbors.push_back(hashtbl[adj->val]);
            }
        }
        return hashtbl[node->val];
    }
};
