#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(void) {
	// constructors: one-dimentional
	vector<int> first;              // empty vector of ints
	vector<int> first_with_size(5); //empty vector of 5 ints
	vector<int> second(5, 10);      // 5 integers with value 10
	vector<int> third(second.begin(), second.end());//from another vector
	vector<int> fourth(third);      // copy the value of vector third
	// the iterator constructor can also be used to construct from arrays
	int ages[] = {10, 20, 30};
	vector<int> fifth (ages, ages + sizeof(ages) / sizeof(int));

	// constructors: two-dimentional
	// 1. fill constructor
	// vector v_int will look like:
	// 10 10
	// 10 10
	// 10 10
	vector<vector<int> > v_fill(3, vector<int>(2, 10));
	// 2. resize()
	vector<vector<int> > v_resize(3);
	for(int i = 0; i < 3; i++)
		v_resize[i].resize(2, 10);
	//3. push_back()
	vector<vector<int> > v_pushback;
	for(int i = 0; i < 3; i++){
		vector<int> temp;
		for(int j = 0; j < 2; j++){
			temp.push_back(10);
		}
		v_pushback.push_back(temp);
	}
	//4. hardcode value (c++ 11)
	/*
	vector<vector<int> > v_hardcode {
				{10, 10},
				{10, 10},
				(10, 10}
				};
	*/
	// constructors: two-dimentional - string
	const string dir[8][2] = {
		{"A","null"},
 		{"B", "A"},
		{"C", "A"},
		{"F", "B"},
		{"D", "C"},
		{"E", "C"},
		{"G", "F"},
		{"H", "F"}
	};
	vector<vector<string>* > vvp;
	vector<string> vec_str[8];
	//push string into the vector
	for(int i = 0; i < 8; i++){
		vec_str[i].push_back(dir[i][0]);
		vec_str[i].push_back(dir[i][1]);
		//push vector* into another vector
		vvp.push_back(&vec_str[i]);
	}

	cout <<" 2D-vector : "<<endl;
	vector<vector<string>* >::iterator it;
	for (it = vvp.begin(); it != vvp.end(); ++it){
		vector<string>::iterator it2;
		//note that it->vector*, so we have to use *it to reference the real contents in vector*
		for(it2 = (*it)->begin(); it2 != (*it)->end(); it2++)
			cout << *it2<<", ";
		cout<<endl;
	}
	cout << "\n";
	return 0;
}
