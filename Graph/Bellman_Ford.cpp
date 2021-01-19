#include <iostream>
#include <vector>
#include <iomanip> //setw()
#include <set>
#include <queue>
#include <iterator>
#include <list>
using namespace std;
class Graph{
private:
	vector<list<pair<int, int> > > AdjList;//AdjList[from] = <to, weight>
	int num_vertex;
public:
	Graph(int num);
	void AddEdge(int from, int to, int weight);
	bool BellmanFord();
	void Relax(int from, int to, int weight, vector<int>& distance, vector<int>& predecessor);
};
Graph::Graph(int num){
	num_vertex = num;
	AdjList = vector<list<pair<int, int> > >(num_vertex);
}
void Graph::AddEdge(int from, int to, int weight){
	AdjList[from].push_back(pair<int, int>(to, weight));
}
void Graph::Relax(int from, int to, int weight,
		vector<int>& distance, vector<int>& predecessor){
	if(distance[from] + weight < distance[to]){
		distance[to] = distance[from] + weight;
		predecessor[to] = from;
	}
}
bool Graph::BellmanFord(){
	//init
	int MAX_DISTANCE = INT_MAX / 2;
	vector<int> distance(num_vertex, MAX_DISTANCE);
	vector<int> predecessor(num_vertex, -1);
	//start from node 2
	int start = 0;
	distance[start] = 0;
	//iterate v-1 times
	for(int i = 0; i < num_vertex - 1; i++){
		for(int v = 0; v < num_vertex; v++){
			list<pair<int, int> >::iterator it;
			for(it = AdjList[v].begin(); it!= AdjList[v].end(); it++){
				Relax(v, it->first, it->second, distance, predecessor);
			}
		}
	}
	//print for verification
	cout<<"#"<<setw(8)<<"dist"<<setw(8)<<"pred"<<endl;
	for(int i = 0; i < num_vertex; i++){
		cout<<i<<setw(8)<<distance[i]<<setw(8)<<predecessor[i]<<endl;
	}
	//check if there's any negative cycle
	for(int from = 0; from < num_vertex; from++){
		list<pair<int, int> >::iterator it;
		for(it = AdjList[from].begin(); it!= AdjList[from].end(); it++){
			int to = it->first;
			int weight = it->second;
			if(distance[to] > distance[from] + weight)
				return false;
		}
	}
	return true;
}
/*
 */
int main(void){
	//an undirected graph
	Graph g(6);
	cout<<"graph 1"<<endl;
	g.AddEdge(0, 1, 5);
    	g.AddEdge(1, 4, -4);g.AddEdge(1, 2, 6);
    	g.AddEdge(2, 4, -3);g.AddEdge(2, 5, -2);
    	g.AddEdge(3, 2, 4);
    	g.AddEdge(4, 3, 1);g.AddEdge(4, 5, 6);
    	g.AddEdge(5, 0, 3);g.AddEdge(5, 1, 7);
	if(g.BellmanFord())
		cout<<"There's no negative cycle in this graph"<<endl;
	else
		cout<<"There's a negative cycle"<<endl;

	Graph g2(4);
	cout<<"graph 2"<<endl;
	g2.AddEdge(0,1,2);
	g2.AddEdge(1,2,-5);
	g2.AddEdge(2,1,1); g2.AddEdge(2,3,3);
	if(g2.BellmanFord())
		cout<<"There's no negative cycle in this graph"<<endl;
	else
		cout<<"There's a negative cycle"<<endl;
	return 0;
}
