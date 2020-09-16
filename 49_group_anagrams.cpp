class Solution {
public:
    #define MAX_ALPHA 26
    void count_letters(string s, int* tbl) {
        memset(tbl, 0, sizeof(int) * MAX_ALPHA);  
        // assume that strings are made of letters
        // all letters are lowercase
        for (int i = 0; i < s.size(); i++)
            tbl[s[i]-'a']++;
    }
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
         */
        int target_tbl[MAX_ALPHA];
        int table[strs.size()][MAX_ALPHA]; // worst case: strs.size() groups
        vector<vector<string>> ans;

        // table construction
        memset(table, 0, strs.size() * MAX_ALPHA * sizeof(int));

        // traverse each word
        for(int i = 0; i < strs.size(); i++) { // current str, O(strs)
            count_letters(strs.at(i), target_tbl);    
            int j, k;
            for (j = 0; j < ans.size(); j++) {     // object to compare, O(strs) if group nums = strs size
                for(k = 0; k < MAX_ALPHA; k++) { // look for every alphabet
                    if (table[j][k] != target_tbl[k]) // current str doesn't exist in this row, see next row
                        break;
                }
                if (k == MAX_ALPHA) {//match, append to output and jump to next str in strs
                    ans[j].push_back(strs.at(i));
                    break;
                }
            }
            if (k != MAX_ALPHA) { // create a new group and output
                memcpy(table[j], target_tbl, sizeof(target_tbl));
                vector<string> temp;
                temp.push_back(strs.at(i));
                ans.push_back(temp);
            }
        }
        return ans;
            
    }
};
