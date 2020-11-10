#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
/* solution: tree back traverse
 * This problem will give us
 *  - a set "folders" that contains <child, parent>
 *  - a set "access" that contains the folders that the user has access to
 *      - the children of the folder in it are unlocked(accessable)
 *      - all folders are unlock by default
 *  - a "target" that is the folder that the user want to access
 *  for example:
 * Input:                   
	[
 	["A", null]                  A
 	["B", "A"],                  |---B*       ====>3. B is in "access" set --> Bingo!
	["C", "A"],                      |---F    ====>2. f is not in "access" set
 	["F", "B"],         --->         |   |--G ====>1. G is not in "access" set
 	["D", "C"],                      |   |--H
 	["E", "C"],                      |
 	["G", "F"],                      C
 	["H", "F"]                       |--D
	]                                |--E
 * 
 *  access = {B}
 *  target = G
 *  The answer is yes, G can be accessed because B has been accessed,
 *  so all the children of B can be accessed as well
 *
 *  Method:
 *  we just search target upwards, check if its ancestor stays in the "access" set.
 *
 *  Time complexity = O(|E| + |h|) = O(|E|)
 *    - we can ignore |h| since a hashtbl building would take most of the time.
 *    - h: the height of the tree
 *  Space complexity = O(|V|)
 */
using namespace std;
bool has_access(string target, set<string>& access, vector<vector<string> >& folders){
	//build a hashtbl for child to parent node
	unordered_map<string, string> hashtbl;
	//O(|E|)
	for(int i = 0; i < folders.size(); i++){
		vector<string> f = folders[i];
		hashtbl.insert(make_pair(f[0], f[1]));
	}
	//start from target, climbing upwards to find if any of its ancestor is in the access
	string curr = target;
	//O(height of tree)
	while(curr != "null"){
		//climbing upwards
		curr = hashtbl[curr];
		if(access.find(curr) != access.end())
			return true;
	}
	return false;
}
int main(void){
	string target = "B";
	set<string> access;
	access.insert("A");
	string s[] = {"A", "null", "B", "A", "C", "A"};
	vector<vector<string> > folders;
	for(int i = 0; i < 6; i+=2){
		vector<string> v;
		v.push_back(s[i]);
		v.push_back(s[i+1]);
		folders.push_back(v);
	}
	if(has_access(target, access, folders))
		cout<<" can access!"<<endl;
	else
		cout<<" cannot access!"<<endl;
	return 0;
}
