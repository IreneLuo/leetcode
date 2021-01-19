class Solution {
    /* solution: recursion + map
     * if formula has more than one ():
     *    -recursive call: breakdown the sub-formula
     * if formula does not have ():
     *    -getName: get the atoms' names
     *    -getCount: get the atoms' counts
     * time complexity = O(n)
     * space complexity = O(n)
     */
public:
    string countOfAtoms(string formula) {
        string ans;
        int idx = 0;
        map<string, int> atoms_map = _countOfAtoms(formula, idx);
        for(auto& it : atoms_map){
            ans += it.first;
            if(it.second != 1)
                ans += to_string(it.second);
        }
        return ans;
    }
    /* if formula starts from (, this function will parse the sub-formula
     * until it finds a balanced )
     * ex: "K4(ON(SO3)2)2"
     *     |  |  |-1-| | |  1. {S:1, O:3}
     *     |  |----2---| |  2. {O:1, N:1} + {S:1, O:3} * 2
     *     |------3------|     = {N:1, O:7, S:2}
     *                      3. {K:4} + {N:1, O:7, S:2} * 2
     *                         = {K:4, N:2, O:14, S:4}
     */
    map<string, int> _countOfAtoms(string& formula, int& idx){
        map<string, int> atoms_map;
        while(idx < formula.length()){
            if(formula[idx] == '('){
                //call _countOfAtoms to handle sub-formula in ()
                //++idx to jump to the character next to '('
                map<string, int> temp_map = _countOfAtoms(formula, ++idx);
                int count = getCount(formula, idx);
                //add value * count to the atoms_map[key]
                //[key, value] comes from temp_map
                for(auto& it: temp_map){
                    atoms_map[it.first] += (it.second) * count;
                }
            }else if(formula[idx] == ')'){
                idx++;
                return atoms_map;
            }else{
                string name = getName(formula, idx);
                atoms_map[name] += getCount(formula, idx);
            }
        }
        return atoms_map;
    }
    string getName(string& formula, int& idx){
        string name;
        //if this character is an alphabet && 
        //  - it's a lowercase
        //  - or it's the first character and an uppercase
        while(isalpha(formula[idx]) && (name.empty() || islower(formula[idx]))){
            name += formula[idx];
            idx++;
        }
        return name;
    }
    int getCount(string& formula, int& idx){
        string count;
        while(isdigit(formula[idx])){
            count += formula[idx];
            idx++;
        }
        return count.empty() ? 1 : stoi(count);
    }
};
