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
	void Relax(int from, int to, int weight, vector<int>& distance, vector<int>& predecessor);
	void DFS(int curr, vector<int>& topology_order, vector<int>& colored,
		vector<int>& finished, vector<int>& discover, int& time, int& count, vector<int>& predecessor);
	void GetTopologySort(int start, vector<int>& topology_order, vector<int>& predecessor);
	void DAG();
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
void Graph::DFS(int curr, vector<int>& topology_order, vector<int>& colored,
		vector<int>& finished, vector<int>& discover, int& time, int& count, vector<int>& predecessor){
	colored[curr] = 1;
	discover[curr] = ++time;
	for(list<pair<int, int> >::iterator it = AdjList[curr].begin();
			it != AdjList[curr].end(); it++){
		int nb = it->first;
		if(colored[nb] == 0){
			predecessor[nb] = curr;
			DFS(nb, topology_order, colored, finished, discover, time, count, predecessor);
		}
	}
	colored[curr] = 2;
	finished[curr] = ++time;
	topology_order[count--] = curr;
}
void Graph::GetTopologySort(int start, vector<int>& topology_order, vector<int>& predecessor){
	vector<int> colored(num_vertex, 0);
	vector<int> finished(num_vertex, 0);
	vector<int> discover(num_vertex, 0);
	int i = start;
	int time = 0;
	int count = num_vertex - 1;
	for(int j = 0; j < num_vertex; j++){
		if(colored[i] == 0)
			DFS(i, topology_order, colored, finished, discover, time, count, predecessor);
		i = j;
	}
}
void Graph::DAG(){
	//init
	int MAX_DISTANCE = INT_MAX / 2;
	vector<int> distance(num_vertex, MAX_DISTANCE);
	vector<int> predecessor(num_vertex, -1);
	vector<int> topology_order(num_vertex, 0);
	int start = 0;
	distance[start] = 0;
	//traverse the graph by dfs method and do a topology sort
	//note that predecessor is unnecessary
	GetTopologySort(start, topology_order, predecessor);
	//access each vertex according to the order in topology_order[]
	//for each vertex, do Relax() for its edges
	for(int i = 0; i < num_vertex; i++){
		int v = topology_order[i];
		for(list<pair<int, int> >::iterator it = AdjList[v].begin();
				it != AdjList[v].end(); it++){
			Relax(v, it->first, it->second, distance, predecessor);
		}
	}
	//print for verification
	cout<<"topology order:";
	for(int i = 0; i < num_vertex; i++)
		cout<<setw(4)<<topology_order[i];
	cout<<endl;
	cout<<"#"<<setw(8)<<"dist"<<setw(8)<<"pred"<<endl;
	for(int i = 0; i < num_vertex; i++)
		cout<<i<<setw(8)<<distance[i]<<setw(8)<<predecessor[i]<<endl;
}
/*
 */
int main(void){
	Graph g8(7);
   	g8.AddEdge(0, 1, 3);g8.AddEdge(0, 2, -2);
    	g8.AddEdge(1, 3, -4);g8.AddEdge(1, 4, 4);
    	g8.AddEdge(2, 4, 5);g8.AddEdge(2, 5, 6);
    	g8.AddEdge(3, 5, 8);g8.AddEdge(3, 6, 2);
    	g8.AddEdge(4, 3, -3);g8.AddEdge(4, 6, -2);
    	g8.AddEdge(5, 6, 2);
	g8.DAG();
	return 0;
}
