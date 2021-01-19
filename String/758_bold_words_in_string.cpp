/* solution: set/string
 * This problem on Leetcode is blocked!
 * The code has not been compiled on Leetcode yet.
 *
 * Idea:
 * We capture all the substring and look up the dictionary
 * to check if this substring matches with an entry in the dictionary.
 * Ex: S="aabcd", words=[ab,bc]
 *     substring = a, aa, a, ab, b, bc, c, cd, d
 *          bold = [00000] --> if bold[i] = 1, then it means this character
 *                             is part of an entry in the dictionary
 *     1. when substring = ab -> we set bold to [01100]
 *     2. when substring = bc -> we set bold to [01110]
 *     					          | |-----> </b> should be added after here
 *                                    So now we know that <b> shoud be added at before here
 * time complexity = O(nL^2)
 *     - L = max length of a word, in this problem is 10
 *     - Generally, there are n*(n-1)/2 substrings of a given string
 *       so the time complexity will be O(n^2*n) 
 *           - n*2 substrings
 *           - copy each substrings takes n time
 *       However, here length of a substring must be <= 10
 *       so the number of substrings will be reduced to nL
 *       and copy each substrings takes L time
 *       the total will be nL^2
 * space complexity = O(n)
 * Reference: HuaHua's video
 * https://www.youtube.com/watch?v=rUNE3VVcXAs&list=PLLuMmzMTgVK49Hph4vV8DAzGZpj4azwmz&index=16
 */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;
string boldWords(vector<string>& words, string& str){
	unordered_set<string> dictionary(words.begin(), words.end());
	int max_substr_len = 10;
	int n = str.length();
	cout<<"n = "<<n<<endl;
	vector<int> bold(n, 0);
	for(int i = 0; i < n; i++){
		for(int len = min(max_substr_len, n-i); len >= 1; --len){
			if (dictionary.count(str.substr(i, len))){
				std::fill(bold.begin()+i, bold.begin()+i+len, 1);
				break;
			}
		}	
	}
	cout<<"bold:"<<endl;
	for(int i = 0; i < bold.size(); i++){
		cout<<bold[i];
	}
	cout<<endl;
	string ans;
	for(int i = 0; i < n; ++i){
		if(bold[i] && (i == 0 || !bold[i-1])) ans += "<b>";
		ans += str[i];
		if(bold[i] && (i == n-1 || !bold[i+1])) ans+= "</b>";
	}
	return ans;
}
int main(void){
	vector<string> words;
	words.push_back("ab");
	words.push_back("bc");
	string str = "aabcd";
	string ans = boldWords(words, str);
	cout<<ans<<endl;
	return 0;
}
