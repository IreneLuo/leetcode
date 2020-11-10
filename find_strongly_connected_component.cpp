#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <iterator>

/*  Problem: Testing strong connectivity of a graph
 *  Given a directed graph determine if it is strongly connected. Return true if it is, otherwise return false.
 *  <note>
 *  A directed graph is "weakly connected" if all vertices are reachable when all edges are interpreted as undirected.
 *  A directed graph is "strongly connected" if for all possible vertices "u" there is a path to any other vertex "v"
 *  and there is a path from that v back to the origianl u.
 *
 *  ex: We use this graph here
 *      so our adjancency list:       reverse adjacency list:
 *                  [0]: 1                [0]: 3
 *                  [1]: 2                [1]: 0
 *                  [2]: 3,4              [2]: 1,4
 *                  [3]: 0                [3]: 2
 *                  [4]: 2                [4]: 2
 *
 *     0 -> 1 -> 2 <-> 4              0 <- 1 <- 2 <-> 4
 *     ^         /                     \       ^
 *      \       /             --->      \     /
 *       \     v                         v   /
 *          3                              3
 *    Then we use these 2 adjency list + BFS to check if all the nodes are visited
 *    If yes, then this graph is strongly connected, which means that each node
 *    are able to reach any of node in this graph.
 *    Reasons:
 *       Take node 0 for example:
 *       We use BFS to find that "who can 0 reach"? (from 0->V)
 *         - The answer is set1 = {0, 1, 2, 4, 3}
 *       We use BFS to find that "who can reach 0"? (from U->0)
 *         - Just reverse the arrow of each edge than we can know who can reach 0
 *         - Than answer is set2 = {0, 3, 2, 1, 4}
 *       Actually, we can consider 0 as a "bridge" from U->0->V
 *         - If we want to know that "can 2 reach 4 ?"
 *           Through set1 we know that 2->0
 *           Through set2 we know that 0->4
 *           so 2 can pass through 0 and reach 4 (2->0->4)
 *         - Once Set1 contains all the nodes in the graph, and set2 contains all the nodes as well,
 *           then we can say this graph is strongly connected since every node can reach other nodes in this graph.
 *  time complexity = O(|V|+|E|)
 *    - Brute-force: |V|(|V|+|E|), because for every node, we use BFS to check if this node can reach every other nodes.
 *                                 and we have |V| nodes in total.
 *    - Improve: 2(|V|+|E|), only do BFS for original adjacency list and reversed adjacency list, so total in twice
 *  space complexity = O(|V|)
 *
 */
using namespace std;
class Graph{
	int node_count;
	list<int>* adj;
	list<int>* rev_adj;
public:
	Graph(int v);
	void add_edge(int from, int to);
	bool is_graph_strongly_connected();
	bool all_nodes_reached_via_bfs(list<int>* adj);
	void reverse_adj();
	void print_adj(list<int>* adj);
};
//constructor
Graph::Graph(int v){
	/* Create n's list<int> for adjacency list */
	this->node_count = v;
	adj = new list<int>[node_count];
	rev_adj = new list<int>[node_count];
}
void Graph::add_edge(int from, int to){
	adj[from].push_back(to);
}
bool Graph::is_graph_strongly_connected(){
	print_adj(adj);
	bool reached = all_nodes_reached_via_bfs(adj);
	if(!reached)
		return false;
	reverse_adj();
	return all_nodes_reached_via_bfs(rev_adj);
}
bool Graph::all_nodes_reached_via_bfs(list<int>* adj){
	queue<int> q;
	set<int> visited;
	//start from the node 0:
	//add it into the queue and visited
	int start = 0;
	q.push(start);
       	visited.insert(start);
	while(!q.empty()){
		int node = q.front();
		q.pop();
		for(list<int>::iterator it = adj[node].begin(); it != adj[node].end(); it++){
			if(visited.find(*it) == visited.end()){
				q.push(*it);
       				visited.insert(*it);
			}
		}
	}
	return(visited.size() == node_count);
}
void Graph::reverse_adj(){
	for(int to = 0; to < node_count; to++){
		for(list<int>::iterator from = adj[to].begin(); from != adj[to].end(); from++){
			rev_adj[*from].push_back(to);
		}
	}
	print_adj(rev_adj);
}
void Graph::print_adj(list<int>* adj){
	for(int i = 0; i < node_count; i++){
		cout<<i;
		for(list<int>::iterator it = adj[i].begin(); it != adj[i].end(); it++){
			cout<<"->"<<*it<<endl;
		}
	}
}
int main(void){
	Graph g(5);
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(2, 4);
	g.add_edge(4, 2);
	g.add_edge(2, 3);
	g.add_edge(3, 0);
	bool ans = g.is_graph_strongly_connected();
	cout<<" ans = "<<ans<<endl;
	return 0;
}
