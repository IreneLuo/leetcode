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
	void FloydWarshall();
	void print(vector<vector<int> >& dis, vector<vector<int> >& pred);
};
Graph::Graph(int num){
	num_vertex = num;
	AdjList = vector<list<pair<int, int> > >(num_vertex);
}
void Graph::AddEdge(int from, int to, int weight){
	AdjList[from].push_back(pair<int, int>(to, weight));
}
void Graph::print(vector<vector<int> >& dis, vector<vector<int> >& pred){
	for(int i = 0; i < num_vertex; i++)
		cout<<setw(5)<<i;
	cout<<setw(5)<<"/";
	for(int i = 0; i < num_vertex; i++)
		cout<<setw(5)<<i;
	cout<<endl;
	cout<<"----------------------------------------"<<endl;
	for(int i = 0; i < num_vertex; i++){
		cout<<i;
		for(int j = 0; j < num_vertex; j++)
			cout<<setw(5)<<dis[i][j];
		cout<<setw(5)<<"/";
		for(int j = 0; j < num_vertex; j++)
			cout<<setw(5)<<pred[i][j];
		cout<<endl;
	}

}
void Graph::FloydWarshall(){
	//init
	//int MAX_DISTANCE = INT_MAX / 2;
	int MAX_DISTANCE = 50;
	vector<vector<int> > distance(num_vertex, vector<int>(num_vertex, MAX_DISTANCE));
	vector<vector<int> > predecessor(num_vertex, vector<int>(num_vertex, -1));
	for(int i = 0; i < num_vertex; i++){
		distance[i][i] = 0;
		for(list<pair<int, int> >::iterator it = AdjList[i].begin();
				it != AdjList[i].end(); it++){
			int to = it->first;
			int weight = it->second;
			distance[i][to] = weight;
			predecessor[i][to] = i;
		}
	}
	//print for verification
	print(distance, predecessor);
	cout<<endl;

	//choose an intermediate point at one time
	for(int k = 0; k < num_vertex; k++){
		for(int u = 0; u < num_vertex; u++){
			for(int v = 0; v < num_vertex; v++){
				if(distance[u][k] != MAX_DISTANCE && distance[u][v] > distance[u][k] + distance[k][v]){
					distance[u][v] = distance[u][k] + distance[k][v];
					predecessor[u][v] = predecessor[k][v];
				}
			}
		}
		cout<<"add intermediate: "<<k<<endl;
		print(distance, predecessor);
		cout<<endl;
	}
}
/*
 */
int main(void){
	Graph g10(4);
	g10.AddEdge(0, 1, 2);g10.AddEdge(0, 2, 6);g10.AddEdge(0, 3, 8);
    	g10.AddEdge(1, 2, -2);g10.AddEdge(1, 3, 3);
    	g10.AddEdge(2, 0, 4);g10.AddEdge(2, 3, 1);
	g10.FloydWarshall();
	return 0;
}
