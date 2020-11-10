/* Problem:
 * There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling
 * up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could
 * choose the next direction.
 * Given the ball's start position, the destination and the maze, determine whether the ball could stop at
 * the destination. The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty
 * space. You may assume that the borders of the maze are all walls.The start and the destination coordinates
 * are represented by row and column indexes.
 * Example 1:
 * input:
 *     a maze represented by a 2D array.
 *     {{0, 0, 1, 0, 0},                 _ _ x _ S      x: block space (cannot pass through)
 *      {0, 0, 0, 0, 0},                 _ _ _ _ _      _: empty space (can pass through)
 *      {0, 0, 0, 1, 0},  -------------> _ _ _ x _      S: start
 *      {1, 1, 0, 1, 1},                 x x _ x x      E: end
 *      {0, 0, 0, 0, 0}}                 _ _ _ _ E
 *
 *     start = {0, 4}
 *     end = {4, 4}
 *
 * output: true
 * Explanation: 1 possible way is: S->left->down->left->down->down->down->right->right->End
 *
 *       _ _ x 1 S
 *       _ _ 1 1 _
 *       _ _ 1 x _
 *       x x 1 x x
 *       _ _ 1 1 E
 *
 * reference: https://www.cnblogs.com/grandyang/p/6381458.html
 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;
class coordinate{
private:
	int row;
	int col;
public:
	coordinate(int r, int c){
		row = r;
		col = c;
	};
	int get_row(){
		return row;
	};
	int get_col(){
		return col;
	};
};
class solution{
public:
	/* Solution: dfs + stack
	 * 1. Start from the start point
	 *    1. add this point into the stack
	 *    2. mark it as block place
	 *    3. call dfs()
	 * 2. in dfs()
	 *    0. try left/up/right/down 4 directions and
	 *    1. if there's a way to go, add a possible candidate(adjacent node) to the stack and go to the next position
	 *       until we reach the end. (return true when reach the end)
	 *    2. if there's no way to go, return false.
	 *    3. if dfs() return false, pop out the top item in the stack and go to step 2 try next one.
	 *
	 * 
	 * time complexity = O(|V| + |E|)
	 *  - here, vertex = block places (x)
	 *  -       edge = empty places (_)
	 *  Since we will mark that place as a block place once we pass through--> when we find out the path,
	 *  the whole graph will be marked as block places. And this means we've passed through all the places
	 *  that is (|V| + |E|) or we could put it in terms of matrix: O(m*n)
	 * Space complexity = O(|E|) or O(m*n) //E<=m*n
	 */ 
	vector<class coordinate> search_a_maze_for_an_exit(vector<vector<int> >& input, 
								class coordinate& start, class coordinate& end){
		vector<class coordinate> path;
		path.push_back(start);
		input[start.get_row()][start.get_col()] = 1;
		if(!dfs_try_to_end(input, start, end, path))
			path.pop_back();
		return path;
	}
	bool dfs_try_to_end(vector<vector<int> >& input, class coordinate& start,
				class coordinate& end, vector<class coordinate>& path){
		if(start.get_row() == end.get_row() && start.get_col() == end.get_col())
			return true;
		//offset for go up/down/left/right
		const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
		for(int i = 0; i < 4; i++){
			int new_row = start.get_row() + dir[i][0];
			int new_col = start.get_col() + dir[i][1];
			class coordinate next(new_row, new_col);
			if(can_enter(next, input)){
				input[next.get_row()][next.get_col()] = 1;
				path.push_back(next);
				if(dfs_try_to_end(input, next, end, path))
					return true;
				path.pop_back();
			}
		}
		return false;
	};
	bool can_enter(class coordinate co, vector<vector<int> >& input){
		int row = co.get_row();
		int col = co.get_col();
		if(row < 0 || row >= input.size())
			return false;
		if(col < 0 || col >= input[0].size())
			return false;
		//we must put this as the last checking point to avoid out of bound accessing of input
		if(input[row][col] == 1)
			return false;
		return true;
	}
};

int main(void){
	//initialize input data
	int input_row = 5;
	int input_col = 5;
	int input_raw[5][5] ={{0, 0, 1, 0, 0},
			      {0, 0, 0, 0, 0},
			      {0, 0, 0, 1, 0},
			      {1, 1, 0, 1, 1},
			      {0, 0, 0, 0, 0}};
	vector<vector<int> > input;
	for(int i = 0; i < input_row; i++){
		vector<int> v(input_raw[i], input_raw[i]+input_col);
		input.push_back(v);
	}
	//ready to deal with the problem
	coordinate start(0, 4);
	coordinate end(4, 4);
	solution sol;
	vector<class coordinate> ans = sol.search_a_maze_for_an_exit(input, start, end);
	cout<<" path = ";
	for(int i = 0; i < ans.size(); i++)
		cout<<ans[i].get_row()<<", "<<ans[i].get_col()<<"->"; 
	return 0;
}
