class Solution {
public:
    /*  solution:
     *  time complexity = O(n)
     *   - create count_tbl: O(n)
     *   - create split_tbl: O(n)
     *   - iterate over split_tbl: O(n) (worst case is that each char appears once, so we have to interate n times)
     *  Space complexity = O(n)
     *   - for all the tables: c*n, we can ignore c(constant)
     */
    int longestSubstring(string s, int k) {

        if(s.size() == 0)
            return 0;

        // create a counting table to count the appearenced times for each character
        vector<int> count_tbl(26, 0);
        for(int i = 0; i < s.size(); i++){
            count_tbl[s[i] - 'a']++;
        }
        // create a table to store the split points
        vector<int> split_tbl;
        for(int i = 0; i < s.size(); i++){
            if(count_tbl[s[i] - 'a'] < k)
                split_tbl.push_back(i);
        }

        // if the split_tbl is empty, return size of s.
        // It means that all the characters in this string appear more than or equal to k times
        if(split_tbl.size() == 0)
            return s.size();
        // otherwise, push the size of string into the split_tbl
        else
            split_tbl.push_back(s.size());

        // Now, we are ready for dealing with substrings that split by those spilt points
        // Our main goal is to break those substrings down into small pieces, until all the charaters
        // in the substring meets the criteria(appears no less than k times)
        int longest = 0;
        int start = 0;
        for(int i = 0; i < split_tbl.size(); i++){
            int end = split_tbl[i];
            if(end-start >= k) { //only if end-start >= k, this substring can meet the criteria
                string substr = s.substr(start, end-start);
                longest = max(longest, longestSubstring(substr, k));
            }
            start = end + 1;
        }
        return longest;
    }
};
