#include <iostream>
#include <vector>
#include <set>
/* Implementation of Dijkstra's algorithm
 * We use a set instead of a priority queue here.
 * Since a set can order our items and we can just
 * call begin() or cbegin() to get the minimum item
 * LeetCode 1334.
 */
using namespace std;
void dijkstra(int start, int n, vector<vector<int> >& edges){
	/* adjlist: to, distance */
	vector<vector<pair<int, int> > > adjlist(n);
	cout<<"push from/to/distance "<<endl;
	for(int i = 0; i < adjlist.size(); i++){
		cout<<edges[i][0]<<", "<< edges[i][1]<<", "<<edges[i][2]<<endl;
		adjlist[edges[i][0]].push_back(pair<int, int>(edges[i][1], edges[i][2]));
	}
	/* */
	vector<int> visited(n, 0);
	/* a table that record the minimum distance of each node (from start node) */
	/* INT_MAX / 2 because we might add two distance together, so use INT_MAX/2 to avoid overflow */
	vector<int> distance(n, INT_MAX / 2);
	distance[start] = 0;
	/* prepare a set to get the node who has a  minimum distance: distance, node */
	set<pair<int, int> > q;
	q.insert(pair<int, int>(distance[start], start));

	/* dijkstra */
	while(!q.empty()){
		int d = q.cbegin()->first;
		int node = q.cbegin()->second;
		q.erase(q.cbegin());
		visited[node] = 1;
		vector<pair<int, int> >::const_iterator it;
		for(it = adjlist[node].cbegin(); it!=adjlist[node].cend(); it++){
		//for(int n = 0; n < adjlist[node].size(); n++){
			int nb = it->first;
			int dis = it->second;
			if (visited[nb]) continue;
			if(distance[nb] > distance[node] + dis){
				distance[nb] = distance[node] + dis;
				q.insert(pair<int, int>(distance[nb], nb));
			}
		}
	}
	cout<<"Result of dijkastra: the minimum path from "<<start<<" to "<<endl;
	for(int i = 0; i < n; i++){
		cout<< i<<", dis = "<<distance[i]<<endl;
	}
}
int main(void){
	int data[][3] = {{0, 1, 5}, {0, 3, 12},
			{1, 0, 5}, {1, 2, 3}, {1, 3, 3},
			{2, 1, 3}, {2, 3, 2},
			{3, 0, 12}, {3, 1, 3}, {3, 2, 2}};
	vector<vector<int> > edges;
	for(int i = 0; i < 10; i++){
		vector<int> v(data[i], data[i] + sizeof(int) * 3);
		edges.push_back(v);
	}
	dijkstra(0, 4, edges);
	return 0;
}
