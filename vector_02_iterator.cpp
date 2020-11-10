#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	// example for vector.begin() & vector.end()
	vector<int> myvector;
	for (int i = 1; i < 5; i++)
		myvector.push_back(i);

	cout << "myvector = ";
	for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		cout << *it << ", ";
	cout <<endl;
	// example for vector.rbegin() & vector.rend()
	cout << "reverse myvector = ";
	for (vector<int>::reverse_iterator rit = myvector.rbegin(); rit != myvector.rend(); ++rit)
		cout << *rit << ", ";
	cout <<endl;

	return 0;
}
