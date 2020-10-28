#include <limits.h>
// similar problem: Leetcode 442. Find All Duplicates in an Array
class Solution {
  public:
    int distanceOfClosestRepeatedEntries(vector<string>& sentence) {
       unordered_map<string, int> hash_tbl;
        // cannot set ans to -1 otherwise ans won't be updated during whole process
        int ans = INT_MAX;

        if(sentence.size() == 0)
            return {};

        for(int i = 0; i < sentence.size(); i++){
            // if the item exists, get the value
            // 1. calculate a new distance between current idx and last occurence idx
            // 2. update the idx of current item into the hash tbl
            auto it = hash_tbl.find(sentence.at(i));
            if(it != hash_tbl.end()){
                int last_occur_idx = it->second;
                ans = min(ans, i - last_occur_idx);
                it->second = i;
            // if the item doesn't exist, insert it into the hash table
            }else{
                hash_tbl.insert(pair<string, int>(sentence.at(i), i));
            }
        }
        return (ans != INT_MAX) ? ans : -1;
    }
};
