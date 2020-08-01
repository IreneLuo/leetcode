#include <vector>
#include <iostream>

using namespace std;

/* Problem: [Array] Rotating a 2D matrix
 * ex:            --> 
 * [10,40,70]          [30, 20, 10]
 * [20,50,80]          [60, 50, 40]
 * [30,60,90]          [90, 80, 70]
 */
vector< vector<int> > rotate(vector< vector<int> >& matrix) {
      int x_len = matrix[0].size();
      vector< vector<int> > ans(x_len, vector<int>(x_len));
      cout << "x_len="<<x_len << "ans size= "<<ans.size()<<endl;

      for (int i = 0 ; i < x_len; i++){
        ans[i][0] = matrix[x_len - 1][i];
        ans[i][1] = matrix[x_len - 2][i];
        ans[i][2] = matrix[x_len - 3][i];
      }
      return ans;
 }

int main (void){
	vector< vector<int> > matrix(3);
	vector< vector<int> > ans(3, vector<int>(3));
	for (int i = 0; i < 3 ; i++)
		matrix[i].resize(3);
	cout << "matrix size = "<< matrix.size()<<endl;

	for (int i = 0; i < matrix[0].size(); i++){
		cout << "\n";
		matrix[0][i] = 10 + i * 30;
		matrix[1][i] = 20 + i * 30;
		matrix[2][i] = 30 + i * 30;
	}
	cout << "\n\n";
	ans = rotate(matrix);
	for (int i = 0; i < ans[0].size(); i++){
		for (int j = 0; j < ans[0].size(); j++)
			cout << ans[i][j] << ", ";
		cout << "\n";
	}
	return 0;
}
