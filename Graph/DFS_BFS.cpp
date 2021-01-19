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
class Graph{
private:
	vector<list<int> > adjlist;
	int num_vertex;
	vector<int> distance; //for bfs()
	vector<int> colored;  //for both
	vector<int> predecessor; //for both
	vector<int> discover_time; //for dfs()
	vector<int> finished_time; //for dfs()
public:
	Graph(int num);
	void build_adjlist(int from, int to);
	void bfs(int start);
	void dfs(int start, int& time);
	void dfs_visit(int start);
	void find_connected_component();
	void print_predecessor();
	void setcollapsing(int idx);
};
Graph::Graph(int num){
	num_vertex = num;
	adjlist.resize(num);
}
void Graph::build_adjlist(int from, int to){
	adjlist[from].push_back(to);
}
void Graph::bfs(int start){
	//init
	colored = vector<int>(num_vertex, WHITE);
	distance = vector<int>(num_vertex, INT_MAX);
	predecessor = vector<int>(num_vertex, -1);
	queue<int> q;
	int curr = start;
	for(int idx = 0; idx < num_vertex; idx++){
		/* we'll start from the start node
		 * and visit all the nodes in this connect component
		 */
		if(colored[curr] == WHITE){
			q.push(curr);	
			colored[curr] = GREY;
			distance[curr] = 0;
			while(!q.empty()){
				int node = q.front(); q.pop();
				colored[node] = BLACK;
				for(list<int>::iterator it = adjlist[node].begin();
						it != adjlist[node].end(); it++){
					if(colored[*it] == WHITE){
						q.push(*it);
						colored[*it] = GREY;
						distance[*it] = distance[node] + 1;
						predecessor[*it] = node;
					}
				}
			}
		}
		//it this graph has several connected components
		//we have to visit all of them
		curr = idx;
	}
	//print the data to check the algorithm is correct or not
	cout<<setw(3)<<"node"<<setw(8)<<"colored"<<setw(12)<<"distance"<<setw(12)<<"predecessor"<<endl;
	for(int i = 0; i < num_vertex; i++){
		cout<<setw(3)<<i<<setw(6)<<colored[i]<<setw(10)<<distance[i]<<setw(8)<<predecessor[i]<<endl;
	}
	find_connected_component();
}

void Graph::dfs(int idx, int& time){
	colored[idx] = GREY;
	discover_time[idx] = ++time;
	for(list<int>::iterator adj = adjlist[idx].begin();
			adj != adjlist[idx].end(); ++adj){
		if(colored[*adj] == WHITE){
			predecessor[*adj] = idx;
			dfs(*adj, time);
		}
	}
	finished_time[idx] = ++time;
	colored[idx] = BLACK;
}
void Graph::dfs_visit(int start){
	//init
	colored = vector<int>(num_vertex, WHITE);
	predecessor = vector<int>(num_vertex, -1);
	discover_time = vector<int>(num_vertex, 0);
	finished_time = vector<int>(num_vertex, 0);
	int time = 0;
	int curr = start;
	for(int i = 0; i < num_vertex; i++){
		if(colored[curr] == WHITE){
			dfs(curr, time);
		}
		curr = i;
	}
	cout<<"idx"<<setw(10)<<"colored"<<setw(8)<<"pred"<<setw(10)<<"discover"<<setw(10)<<"finished"<<endl;
	for(int i = 0; i < num_vertex; ++i){
		cout<<i<<setw(10)<<colored[i]<<setw(8)<<predecessor[i]<<setw(8)<<discover_time[i];
		cout<<setw(8)<<finished_time[i]<<endl;
	}
	find_connected_component();
}
void Graph::find_connected_component(){
	cout<<"predecessor:"<<endl;
	print_predecessor();

	for(int i = 0; i < num_vertex; ++i)
		setcollapsing(i);

	cout<<"after setcollapsing, predecessor:"<<endl;
	print_predecessor();
	cout<<"show each component"<<endl;
	int cnt = 0;
	for(int root = 0; root < num_vertex; root++){
		if(predecessor[root] == -1){
			cout<<"component "<<++cnt<<": "<<root<<" ";
			for(int j = 0; j < num_vertex; j++){
				if(predecessor[j] == root)
					cout<<j<<" ";
			}
			cout<<endl;
		}
	}
}
void Graph::print_predecessor(){
	for(int i = 0; i < num_vertex; ++i)
		cout<<setw(4)<<i;
	cout<<endl;
	for(int i = 0; i < num_vertex; ++i)
		cout<<setw(4)<<predecessor[i];
	cout<<endl;
}
void Graph::setcollapsing(int curr){
	//find the root of current node
	int root = curr;
	while(predecessor[root]>=0){
		root = predecessor[root];
	}
	//update current node's predecessor until current == root)
	while(curr != root){
		int parent = predecessor[curr];
		predecessor[curr] = root;
		curr = parent;
	}
}
/*
 *    0  3
 *    | / 
 *    1 - 4
 *    |
 *    2 - 5   6 - 7
 */
int main(void){
	//an undirected graph
	Graph g1(8);
	g1.build_adjlist(0, 1); 
	g1.build_adjlist(1, 2); g1.build_adjlist(1, 0); 
	g1.build_adjlist(1, 3); 
	g1.build_adjlist(1, 4); 
	g1.build_adjlist(2, 5); g1.build_adjlist(2, 1); 
	g1.build_adjlist(3, 1); 
	g1.build_adjlist(4, 1); 
	g1.build_adjlist(5, 2); 
	g1.build_adjlist(6, 7); 
	g1.build_adjlist(7, 6); 
	cout<<"------dfs------"<<endl;
	g1.dfs_visit(0);
	cout<<"------bfs------"<<endl;
	g1.bfs(0);
	return 0;
}
