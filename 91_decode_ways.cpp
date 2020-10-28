class Solution {
public:
    /* solution: dynamic programming
     * 
     * time complexity = O(n)
     *   - branching factor = 2
     *   - depth = n
     *   so a loosely time complexity is O(2^n)
     *   however we have history[] in memory, so this help us save more time
     *   so we only have to spend our time on left substr which is equal to a linked list
     *   so our time complexity is O(n)
     * space complexity = O(n)
     *
     *  ex:   left tree: when snippet length = 1
     *        right tree: when snippet length = 2
     *        we can observe that history[] will be filled once we go to the end of left-most subtree
     *        so the rest of the node can look up history table to get the answer
     *         
     *                              2101
     *                            /       \
     *                           /         \
     *       history[0]<--   "2"101          "21"01 
     *                       /     \          /     \
     * history[1]<--     2"1"01     2"10"1   21"0"1   21"01"
     *                  /     \     /         /         |
     * history[2]<-- 21"0"1  21"01" 210"1"  210"1"      |
     *              /         |      |       |          v
     *          210"1"        |------|-------|----->(cannot start with 0)
     *            |                  v       |
     *            |----> save history[3] <----
     *     
     */
    
    // if str stars by "0" or str is larget than 26, it will return false
    bool isValid(string str){
        if((str != "0") && (str[0] == '0'))
            return false;

        int num = atoi(str.c_str());
        return (num <= 26) && (num >= 1);
    }
    //return how many ways for decoding this substr
    int ways_of_decoding_substr(string s, vector<int>& history, int start){
        // base case: hit the end so we return 1
        if(start >= s.size())
            return 1;
        // look up history[]
        if(history[start] > -1)
            return history[start];
        int ways = 0;
        //the largest alphabet is Z(26) so the upper bound of snippetlen is 2
        for(int snippetlen = 1; snippetlen <= 2; snippetlen++){
            if((start+snippetlen) <= s.size()){
                string substr = s.substr(start, snippetlen);
                if(isValid(substr)){
                    //we ask if s[start+1] and s[start+2] have answers and accumulate the answer
                    ways += ways_of_decoding_substr(s, history, start + snippetlen);
                }
            }
        }
        history[start] = ways;
        return history[start];
    }
    int numDecodings(string s) {
        //history[i] = ways of decoding s[i..end]
        vector<int> history(s.size(), -1);
        return ways_of_decoding_substr(s, history, 0);
    }
};
