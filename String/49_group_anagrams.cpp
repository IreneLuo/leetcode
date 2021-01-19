class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        /* Solution 1:
         * 1. Create a two-dimensional table, each row represents a group.
         *    This table will has 26 columns to store the count of letters in each string.
         *    g1: _0_, ..., _25_ --> ex: g1 consists of 1 "a", 1 "e", and 1 "t"
         *    g2: _0_, ..., _25_ --> ex: g2 consists of 2 "a", 1 "c"
         *    ...
         *    gn: _0_, ..., _25_
         *
         * 2. traverse each word in input. For each string:
         *    a. count the letters
         *    b. look up table, if match --> push to vector[g1]
         *                      if mismatch --> add a group information
         * Time complexity: O(strs^2)
         * Space complexity:O(strs) + O(strs) = O(strs)
         * Faster than 5.03% / memory less than 91.18%
         *
         * Solution2: we can transfer step1's table into a hashmap
         *   Hashmap: key = the count of the letters in each word
         *            value = each word
         *    [#2#1#0#0...#0]: aab
         *    [#1#2#0#0...#0]: abb
         *  time complexity = O(nk)
         *  space complexity = O(nk)
         *    - n: the length of strs
         *    - k: the max length of a word in strs
         *
         * Solution3: or we can sort the word as a key (the code below)
         *   Hashmap: key = string after sorting
         *            value = each word
         *    [abt]: bat
         *    [ant]: nat, tan
         *    [aet]: ate, eat, tea
         *  time complexity = O(nklogk)
         *    - n: the length of strs
         *    - k: the max length of a word in strs
         *          so sorting time = klogk
         *  space complexity = O(nk)
         */
        unordered_map<string, vector<string>> hashtbl;
        for(auto word: strs){
            string sorted = word;
            sort(sorted.begin(), sorted.end());
            hashtbl[sorted].push_back(word);
        }
        vector<vector<string>> ans;
        for(auto it: hashtbl){
            ans.push_back(it.second);
        }
        return ans;
    }
};
