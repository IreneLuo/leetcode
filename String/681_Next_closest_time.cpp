#include <iostream>
#include <set>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
/* Solution 1: BruteForce
 * 1. add 1 min each time
 *    - ++min
 *    - if min == 60, ++hr
 * 2. if new time is valid, return the answer
 *    - transfer new time into a set
 *    - compare set(new time) with set(old time)
 * time complexity = O(24*60)=O(1440)
 *   - worst case: 00:00->the next day 00:00--> we have to add 24*60 mins to find the ans
 *   - best case: 12:54-> 12:55 --> add 1 min to find the ans
 * space complexity = O(1)
 */
string nextClosestTime_bruteforce(string& time){
	set<char> oldtime(time.begin(), time.end());
	int hr = stoi(time.substr(0, 2));
	int min = stoi(time.substr(3, 2));
	while(true){
		++min;
		if(min == 60){
			min = 0;
			++hr;
			hr %= 24;
		}
		char buffer[5];
		sprintf(buffer, "%02d:%02d", hr, min);
		set<char> newtime(buffer, buffer + sizeof(buffer));
		if(includes(oldtime.begin(), oldtime.end(), newtime.begin(), newtime.end()))
				return string(buffer);
	}
}
/* solution 2: dfs
 * 1. time: h1h2:m1m2
 *    use dfs to try all combinations of h1h2m1m2
 * 2. for each combination
 *    - check time format is correct (min<60 hr<24)
 *    - check difference and keep the smallest difference
 * 3. return the combination that has the smallest difference
 *
 * time complexity = O(4^4)
 *    - 4 time blanks to fill, each blank we have 4 choices
 * space complexity = O(4)
 */
int toMin(int hr, int min){
	return hr * 60 + min;
}
//22:22 = 22*60+22=1320+22=1342
//23:59 = 23*60+59=1380+59=1439
//diff = -97
//-97+1440=1343mins
//actually 1+1342=1343mins
//if diff is negative we need to add 24*60 to become a valid difference
int diff(int t1, int t2){
	//if a==b, the difference = 24hrs
	if(t1 == t2) return INT_MAX;
	return ((t2-t1)+(24*60)) % (24 * 60);
}

void dfs(int depth, vector<int>& digits, vector<int>& newtime, int& oldMin, int& bestMin){
	if(depth == 4){
		int hr = newtime[0] * 10 + newtime[1];
		int min = newtime[2] * 10 + newtime[3];
		if(hr > 23 || min > 59) return;
		int newMin = toMin(hr, min);
		//we must put oldMin as first parameter, and newMin or bestMin as second parameter
		//since we want to know the difference between oldMin and newMin/bestMin
		//and newMin/bestMin are all occur later than oldMin
		if(diff(oldMin, newMin) < diff(oldMin, bestMin))
			bestMin = newMin;
		return;
	}
	for(int i = 0; i < 4; i++){
		newtime[depth] = digits[i];
		dfs(depth+1, digits, newtime, oldMin, bestMin);
	}

}
string nextClosestTime_dfs(string& time){
	//1. extract 4 digits from the time
	vector<int> oldtime;
	oldtime.push_back(time[0]-'0');
	oldtime.push_back(time[1]-'0');
	oldtime.push_back(time[3]-'0');
	oldtime.push_back(time[4]-'0');
	vector<int> newtime(4, 0);
	int hr = oldtime[0] * 10 + oldtime[1];
	int min = oldtime[2] * 10 + oldtime[3];
	int oldMin = toMin(hr, min);
	int bestMin = oldMin;
	dfs(0, oldtime, newtime, oldMin, bestMin);
	char buffer[5];
	sprintf(buffer, "%02d:%02d", bestMin / 60, bestMin % 60);
	return string(buffer);
}
int main(void){
	string time = "19:34";
	string time2 = "23:59";
	//cout<<"sol1: "<<nextClosestTime_bruteforce(time2)<<endl;
	cout<<"sol2: "<<nextClosestTime_dfs(time2)<<endl;
	return 0;
}
