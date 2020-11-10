/* Minimum spanning tree
 * When we find a set of edges that connects all the vertices with minimum costs.
 * Note that every edge cost is different and positive.
 *
 * Two MST algorithms:
 *  1. What is the principle of Prim's algorithm?
 *     Build a minimum spanning tree, investigate every edge that can extend this tree without creating a cycle,
 *     and then make the choice of the smallest edge. 
 *     <note> Prim's v.s Dijkastra's
 *     reference: https://www.itdaan.com/tw/5eb8b64e4910712cace5e10f5740663b
 *     Prim: the goal of it is to find out a minimum spanning tree. So we will get a set of edges that connected to
 *           all the edges with minimum cost. This means that an edge from A to B might not be the smallest edge.
 *           In Prim's algorithm, we care about the final minimum cost, not the smallest edge between each node.
 *           Hence, in the implementation, we choose the smallest edge in each iteration to collect the edge of
 *           a minimum spanning tree.
 *     Dijkastra:(shortest path): the goal of it is to find out a minimum path tree. So we will get a set of edges
 *           and each edge will be the minimum edge for two vertices in the graph. Hence, in the implementation,
 *           we care about "is the node "source"->node "x" the shortest path?", and we calculate the cost of whole path
 *           (ex: source -> y -> z -> x) to check the answer.
 *  2. Kruskal's algorithm
 *
 */
#include <iostream>
#include <queue> //for priority queue
#include <vector>
#include <list>
using namespace std;
struct NODE{
	int id;
	int distance;
	int predecessor;
	NODE(int n, int d, int p): id(n), distance(d), predecessor(p) {};
};
typedef struct NODE MYNODE;
class myCompare{
public:
	/* TODO: if use > the anwer will wrong */
	bool operator()(const NODE* a, const NODE* b){
		return (a->distance > b->distance);
	}
};
class GRAPH_SHORTPATH{
private:
	int num_node;
	priority_queue<NODE*, vector<NODE*>, myCompare> pq;
	vector<bool> visited;
	vector<NODE*> nodeset;
	vector<list<pair<int, int> > > adjlist;
public:
	GRAPH_SHORTPATH():num_node(0){};
	GRAPH_SHORTPATH(int n){
		num_node = n;
		adjlist.resize(num_node);
		visited.resize(num_node);
	}
	void AddEdge(int from, int to, int distance){
		adjlist[from].push_back(make_pair(to, distance));
	}
	void initialize_source(int start){
		for(int i = 0; i < num_node; i++){
			NODE* node;
			// node, distance, predecessor
			if(i == start){
				node = new NODE(i, 0, -1);
				pq.push(node);
			}else{
				node = new NODE(i, INT_MAX, -1);
			}
			nodeset.push_back(node);
		}
	}
	void print_data(void){
		cout<<" ------print the table------ " <<endl;
		for(vector<NODE*>::iterator it = nodeset.begin(); it!=nodeset.end(); it++)
			cout<<" node "<<(*it)->id<<" distance "<<(*it)->distance<<" from "<<(*it)->predecessor<<endl;
	}
	void prim(int start){
		/*
		for(int i = 0; i < 6; i++){
			cout<<"adjlist "<< i << " : ";
			for(list<pair<int, int> >::iterator it = adjlist[i].begin(); it != adjlist[i].end(); it++)
				cout<<it->first<<","<< it->second<<" / ";
			cout<<endl;
		}
		*/
		//initialize node, distance, and predecessor
		initialize_source(start);
		//choose a node which has the  minimum distance from the min-heap
		while(!pq.empty()){
			//get a node that has the minimum distance with its predecessor
			NODE* node = pq.top();
			pq.pop();
			int target = node->id;
			cout<<"extract from minqueue: id = "<<target<< " distance = "<<node->distance<<endl;
			visited[target] = true;
			//find out all the adjancent nodes of this node and update their distances
			list<pair<int, int> >::iterator it;
			for(it = adjlist[target].begin(); it!=adjlist[target].end(); it++){
				int adjnode = it->first;
				int distance = it->second;
				//if the adjencent node has been visited, we don't need to look into this node
				if(visited[adjnode])
					continue;
				//TODO: note that only this line is different with dijkastra's algorithm
				if(nodeset[adjnode]->distance > distance){
					nodeset[adjnode]->distance = distance;
					nodeset[adjnode]->predecessor = target;
					pq.push(nodeset[adjnode]);
				}
				cout<<" from "<<target<<" to "<<adjnode<<" d = "<<nodeset[adjnode]->distance<<endl;
			}
		};
		print_data();
	}
};
int main(void){
	class GRAPH_SHORTPATH g6(7);
	g6.AddEdge(0, 1, 5);g6.AddEdge(0, 5, 3);
	g6.AddEdge(1, 0, 5);g6.AddEdge(1, 2, 10);g6.AddEdge(1, 4, 1);g6.AddEdge(1, 6, 4);
	g6.AddEdge(2, 1, 10);g6.AddEdge(2, 3, 5);g6.AddEdge(2, 6, 8);
	g6.AddEdge(3, 2, 5);g6.AddEdge(3, 4, 7);g6.AddEdge(3, 6, 9);
	g6.AddEdge(4, 1, 1);g6.AddEdge(4, 3, 7);g6.AddEdge(4, 5, 6);g6.AddEdge(4, 6, 2);
	g6.AddEdge(5, 0, 3);g6.AddEdge(5, 4, 6);
	g6.AddEdge(6, 1, 4);g6.AddEdge(6, 2, 8);g6.AddEdge(6, 3, 9);g6.AddEdge(6, 4, 2);
	g6.prim(2);
	return 0;
}
