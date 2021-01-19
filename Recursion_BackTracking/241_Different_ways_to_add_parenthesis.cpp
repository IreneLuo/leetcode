/* solution: recursive call + hashtbl
 * Main idea:
 *    When we encounter an operator, split the string into two parts.
 *    Then we keep split those two substring into four parts, until
 *    there's no operator in any substring
 * Example: () means a recursive call
 * "ways(2*3-4*5)"
 *    = ways (2) X* ways(3-4*5) = 2 * {-17, -5} = {-34, -10}#
 *                  = ways(3) X- ways(4*5) = 3-20 = -17 => insert map<4*5, 20>
 *                  = ways(3-4) X* ways(5) = -1 * 5 = -5 => insert map<3-4, -1>
 *    = ways (2*3) X- ways(4*5) = {6} X- {20} = {-14}#
 *    = ways (2*3-4) X* ways(5) = {-2, -2} * 5 = {-10, -10}#
 *      = ways(2) X* ways(3-4) = 2*-1 = -2
 *      = ways(2*3) X- ways(4) = 6-4 = -2
 *
 * time complexity = O(2^n)
 * space complexity = O(2^n)
 */
namespace ting{
    int add(int a, int b) {return a + b;}
    int minus(int a, int b) {return a - b;}
    int multi(int a, int b) {return a * b;}
}
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        return ways(input);
    }
    const vector<int> ways(const string& input){
        vector<int> ans;
        unordered_map<string, vector<int>> map;
        //return the ways if we've already handled this input
        if(map.count(input))
            return map[input];
        //iterate over the input string to find out the operator and split the input
        for(int i = 0; i < input.length(); i++){
            char ch = input[i];
            if(ch == '+' ||ch == '-' ||ch == '*'){
                const vector<int>& left = ways(input.substr(0, i));
                const vector<int>& right = ways(input.substr(i+1));
                //funtion pointer who points to a function to do the operations
                std::function<int(int, int)>f;
                switch(ch){
                    case '+': f = ting::add; break;
                    case '-': f = ting::minus; break;
                    case '*': f = ting::multi; break;
                }
                for(int a: left)
                    for(int b: right)
                        ans.push_back(f(a, b));
            }   
        }
        //base cases: string doesn't have any operator like '5'
        if(ans.empty())
            ans.push_back(stoi(input));
        //insert a <key, value> pair into the map
        return map[input] = ans;
    }
};
