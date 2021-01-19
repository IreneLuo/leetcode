#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <list>
#include <iomanip> //setw()
using namespace std;
enum{
	WHITE,
	GREY,
	BLACK
};
struct Edge{
	int from;
	int to;
	int weight;
	Edge(): from(0), to(0), weight(0) {};
	Edge(int f, int t, int w): from(f), to(t), weight(w) {};
};
class Graph{
private:
	vector<vector<int> > AdjMatrix;
	int num_vertex;
	vector<int> colored;  //for both
	vector<int> predecessor; //for both
	vector<int> discover_time; //for dfs()
	vector<int> finished_time; //for dfs()
public:
	Graph(int num);
	void AddEdge(int from, int to, int weight);
	int FindSetCollapsing(vector<int>& Subset, int curr);
	void GetSortedEdges(vector<Edge>& v);
	void UnionSet(vector<int>& Subset, int from, int to);
	void KruskalMST();
};
Graph::Graph(int num){
	num_vertex = num;
	AdjMatrix = vector<vector<int> >(num_vertex, vector<int>(num_vertex, 0));
}
void Graph::AddEdge(int from, int to, int weight){
	AdjMatrix[from][to] = weight;
}
/* FindSetCollapsing
 * 1. find the root of current node
 * 2. if current node is not the root
 *      - change its parent to the root
 *      - change its parent's parent to the root
 *    until current node is the root
 * 3. return the root
 */
int Graph::FindSetCollapsing(vector<int>& Subset, int curr){
	//find the root of current node
	int root = curr;
	while(Subset[root] >= 0){
		root = Subset[root];
	}
	//update current node's predecessor until current == root)
	while(curr != root){
		int parent = Subset[curr];
		Subset[curr] = root;
		curr = parent;
	}
	return root;
}
bool WeightCmp(Edge e1, Edge e2){
	return e1.weight < e2.weight;
}
/* GetSortedEdges
 * sort the edge by weight
 */
void Graph::GetSortedEdges(vector<Edge>& v){
	for(int i = 0; i < num_vertex-1; i++)
		for(int j = i+1; j < num_vertex; j++)
			if(AdjMatrix[i][j] != 0)
				v.push_back(Edge(i, j, AdjMatrix[i][j]));
	sort(v.begin(), v.end(), WeightCmp);
}
/* UnionSet
 * 1. check which set is bigger, move the smaller one to the bigger one
 *    (by adding count to the bigger one)
 * 2. set smaller one's parent to the bigger one's root
 */
void Graph::UnionSet(vector<int>& Subset, int from, int to){
	int xroot = FindSetCollapsing(Subset, from);
	int yroot = FindSetCollapsing(Subset, to);
	if(Subset[xroot] <= Subset[yroot]){
		Subset[xroot] += Subset[yroot];
		Subset[yroot] = xroot;
	}else{
		Subset[yroot] += Subset[xroot];
		Subset[xroot] = yroot;
	}
}
/* Kruskal Algorithm
 * 1. Sort the edge by weight
 * 2. Iterate over the edge with vertex a and b
 *    - if the root of set where a belongs to and the root of set where b belongs to
 *      are different
 *       - add this edge to EdgeSet(since a and b are at different set)
 *       - union a and b by checking Subset[]
 * Subset[]: record the root and number of members of each set
 * (a set = a connected component)
 * Ex:
 *     node# 0  1  2 3 4 5
 *      val  -1 -3 -2 2 1 1
 *     -----------------------
 *     if val > 0: val is the root of that node
 *     if val < 0: val is the number of members of the set (the node belongs to)
 *     Ex: Subset[0]=-1: this set only has node 0, the number of members = 1
 *         Subset[1]=-3: this set has 3 members and 1 is the root of this set
 *         Subset[4]=1 : the root of node 4 = node 1
 *         Subset[5]=1 : the root of node 5 = node 1
 *         Apparently, node 1,4,5 are a connected component in this undirected graph
 *                     node 2,3 are a connected component
 *     Note that in our example in main(), we don't have node 0, but we still allocate
 *     Subset to size of n for mapping subset[i] to node i.
 *
 */
void Graph::KruskalMST(){
	vector<Edge> EdgeSet;
	vector<int> Subset(num_vertex, -1);

	vector<Edge> IncreaseWeight;
	GetSortedEdges(IncreaseWeight);
	for(int i = 0; i < IncreaseWeight.size(); i++){
		int from = IncreaseWeight[i].from;
		int to = IncreaseWeight[i].to;
		if(FindSetCollapsing(Subset, from) != FindSetCollapsing(Subset, to)){
			EdgeSet.push_back(IncreaseWeight[i]);
			UnionSet(Subset, from, to);
			cout<<"union "<<from<<" , "<<to<<" subset = ";
			for(int i = 0; i < Subset.size(); i++)
				cout<<Subset[i]<<" ";
			cout<<endl;
		}
	}
	//Print EdgeSet
	cout<<" Edgeset "<<endl;
	for(int i = 0; i < EdgeSet.size(); i++){
		cout<<EdgeSet[i].from<<" - "<<EdgeSet[i].to<<" : "<<EdgeSet[i].weight<<endl;
	}
	cout<<" subset : ";
	for(int i = 0; i < Subset.size(); i++){
		cout<<Subset[i]<<" ";
	}
}
/*
 */
int main(void){
	//an undirected graph
	Graph g6(6);
	/*
    	g6.AddEdge(0, 1, 5);g6.AddEdge(0, 5, 3);
    	g6.AddEdge(1, 0, 5);g6.AddEdge(1, 2, 10);g6.AddEdge(1, 4, 1);g6.AddEdge(1, 6, 4);
    	g6.AddEdge(2, 1, 10);g6.AddEdge(2, 3, 5);g6.AddEdge(2, 6, 8);
    	g6.AddEdge(3, 2, 5);g6.AddEdge(3, 4, 7);g6.AddEdge(3, 6, 9);
    	g6.AddEdge(4, 1, 1);g6.AddEdge(4, 3, 7);g6.AddEdge(4, 5, 6);g6.AddEdge(4, 6, 2);
    	g6.AddEdge(5, 0, 3);g6.AddEdge(5, 4, 6);
    	g6.AddEdge(6, 1, 4);g6.AddEdge(6, 2, 8);g6.AddEdge(6, 3, 9);g6.AddEdge(6, 4, 2);
	*/
	g6.AddEdge(1, 2, 10);g6.AddEdge(1, 4, 1);g6.AddEdge(1, 5, 4);
    	g6.AddEdge(2, 1, 10);g6.AddEdge(2, 3, 5);g6.AddEdge(2, 5, 8);
    	g6.AddEdge(3, 2, 5);g6.AddEdge(3, 4, 7);g6.AddEdge(3, 5, 9);
    	g6.AddEdge(4, 1, 1);g6.AddEdge(4, 3, 7);g6.AddEdge(4, 5, 2);
    	g6.AddEdge(5, 1, 4);g6.AddEdge(5, 4, 2);g6.AddEdge(5,2,8);g6.AddEdge(5,3,9);
	g6.KruskalMST();
	return 0;
}
