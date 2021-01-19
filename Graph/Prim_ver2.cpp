#include <iostream>
#include <vector>
#include <iomanip> //setw()
#include <set>
#include <queue>
#include <iterator>
#include <list>
using namespace std;
class mycompare{
public:
	bool operator()(const pair<int, int> p1, const pair<int, int> p2)const{
		if(p1.first == p2.first)
			return p1.second > p2.second;
		return p1.first > p2.first;
	}
};
class Graph{
private:
	vector<list<pair<int, int> > > AdjList;
	int num_vertex;
public:
	Graph(int num);
	void AddEdge(int from, int to, int weight);
	void PrimMST_MinQueue();
};
Graph::Graph(int num){
	num_vertex = num;
	AdjList = vector<list<pair<int, int> > >(num_vertex);
}
void Graph::AddEdge(int from, int to, int weight){
	AdjList[from].push_back(pair<int, int>(to, weight));
}
void Graph::PrimMST_MinQueue(){
	int MAX_WEIGHT = 1000;
	//init
	set<int> visited;
	vector<int> predecessor(num_vertex, -1);
	//for verfication so we save the key value but not necessary
	vector<int> key_backup(num_vertex, MAX_WEIGHT);
	//both are fine!
	//priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	priority_queue<pair<int, int>, vector<pair<int, int> >, mycompare > pq;
	//start from node 2
	int start = 2;
	//in this queue: <key, node#>
	pq.push(pair<int, int>(0, 2));
	key_backup[start] = 0;
	//keep searching the smallest key
	while(!pq.empty()){
		int key = pq.top().first;
		int from = pq.top().second;
		cout<<"key, from = "<<key<<", "<<from<<endl;
		pq.pop();
		visited.insert(from);
		list<pair<int, int> >::iterator it;
		//in AdjList: <to, weight>
		for(it = AdjList[from].begin(); it != AdjList[from].end(); it++){
			int to = it->first;
			int weight = it->second;
			if(!visited.count(to) && weight < key_backup[to]){
				key_backup[to] = weight;
				predecessor[to] = from;
				pq.push(pair<int, int>(weight, to));
			}
		}
	}
	//print
	cout<<"print key, predecessor, visited table"<<endl;
	cout<<"note that #0 is invalid since our node starts from 1 instead of 0"<<endl;
	cout<<"#"<<setw(6)<<"key"<<setw(6)<<"pred"<<setw(8)<<"visited"<<endl;
	for(int i = 0; i < num_vertex; i++){
		cout<<i<<setw(6)<<key_backup[i]<<setw(6)<<predecessor[i]<<setw(8);
		if(visited.count(i))
			cout <<"1"<<endl;
		else
			cout <<"0"<<endl;
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
	/*          10
	 *        1-----2
	 *        |4\ /2|
	 *       1|  5  |5
	 *        |8/ \9|
	 *        4-----3
	 *           7
	 */
	g6.AddEdge(1, 2, 10);g6.AddEdge(1, 4, 1);g6.AddEdge(1, 5, 4);
    	g6.AddEdge(2, 1, 10);g6.AddEdge(2, 3, 5);g6.AddEdge(2, 5, 8);
    	g6.AddEdge(3, 2, 5);g6.AddEdge(3, 4, 7);g6.AddEdge(3, 5, 9);
    	g6.AddEdge(4, 1, 1);g6.AddEdge(4, 3, 7);g6.AddEdge(4, 5, 2);
    	g6.AddEdge(5, 1, 4);g6.AddEdge(5, 4, 2);g6.AddEdge(5,2,8);g6.AddEdge(5,3,9);
	g6.PrimMST_MinQueue();
	return 0;
}
