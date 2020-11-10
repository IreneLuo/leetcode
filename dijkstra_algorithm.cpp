/* Dijkstra Algorithm
 * It's kind of a greedy algorithm that for each iteration,
 * we choose an currently optimal solution for the answer.
 * 
 * Basic operations for this algorthm
 * 1. extract a node which has the minimum distance
 *    - we use the priority heap in STL to implement
 * 2. notify this node as visited
 * 3. find out all the adjencey nodes of this node and update their distances
 * 2. rebuild the heap
 *    - priority heap: pop()
 *
 * Data structure
 * vector<NODE*> dataset: record the distance and the predecessor of each node
 * vector<bool> vistited: the status of each node (has been visited or not)
 * priority_queue<NODE*, vector<NODE*>, myCompare> pq: it's a min-Heap so that every time 
 *                                                     we can get the min node from the top
 * 
 *      <min-Heap>                 <dataset>           <visited>
 *                              id distance predecessor
 *      ---------------------------------------------------------
 *         []              [0]  0    0         0         false  
 *        /  \             [1]  1  INT_MAX    -1         false
 *      []   []                         ...             
 *            |            [n]  1  INT_MAX    -1         false
 *            ----> a copy of an element in <dataset>
 *
 * Reference: http://alrightchiu.github.io/SecondRound/single-source-shortest-pathdijkstras-algorithm.html
 * See Leetcode 1631. Path With Minimum Effort
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
	void build_adjacency_list(int from, int to, int distance){
		adjlist[from].push_back(make_pair(to, distance));
	}
	void initialize_source(int start){
		for(int i = 0; i < num_node; i++){
			NODE* node;
			// node, distance, predecessor
			if(i == start){
				node = new NODE(i, 0, 0);
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
	void dijkastra(int start){
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
			list<pair<int,int> >::iterator it;
			for(it = adjlist[target].begin(); it!=adjlist[target].end(); it++){
				int adjnode = it->first;
				int distance = it->second;
				//if the adjencent node has been visited, we don't need to look into this node
				if(visited[adjnode])
					continue;
				//TODO: here's the difference with Prim's Algorithm
				if(nodeset[adjnode]->distance > nodeset[target]->distance + distance){
					nodeset[adjnode]->distance = nodeset[target]->distance + distance;
					nodeset[adjnode]->predecessor = target;
					//Note that we don't push all the value when initializing, since
					//we might update the distance here, and the priority queue that
					//we use for min-Heap might not heapify a correct min value to the
					//top.So we push the node info after updating the distance
					NODE* copy_adj = new NODE(nodeset[adjnode]->id, nodeset[adjnode]->distance, 
							 nodeset[adjnode]->predecessor);
					pq.push(copy_adj);

				}
				cout<<" from "<<target<<" to "<<adjnode<<" d = "<<nodeset[adjnode]->distance<<endl;
			}
		};
		print_data();
	}
};
int main(void){
	class GRAPH_SHORTPATH gsp(6);
	gsp.build_adjacency_list(0, 1, 8);gsp.build_adjacency_list(0, 5, 1);
	gsp.build_adjacency_list(1, 0, 3);gsp.build_adjacency_list(1, 2, 1);
	gsp.build_adjacency_list(2, 0, 5);gsp.build_adjacency_list(2, 3, 2);gsp.build_adjacency_list(2, 4, 2);
	gsp.build_adjacency_list(3, 1, 4);gsp.build_adjacency_list(3, 2, 6);gsp.build_adjacency_list(3, 4, 7);
	gsp.build_adjacency_list(3, 5, 3);
	gsp.build_adjacency_list(5, 3, 2);gsp.build_adjacency_list(5, 4, 8);
	gsp.dijkastra(0);
	return 0;
}
