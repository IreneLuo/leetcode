class Solution {
    /* solution 1: DFS
     * Main idea:
     * In each iteration(DFS), cut off a substring with a specific length
     * and insert it into the unordered set. If the substring has already been
     * inserted into the set, then we drop it off, and choose a longer length
     * of a substring and try again until we finish cutting off whole string.
     *
     * time complexity: O(n)
     * space complexity: O(n) //for unordered_set and stack depth
     *
     *
     */
private:
    unordered_set<string> substr_so_far;
    void dfs(string& s, int start, int& ans){
        if(start == s.length()){
            ans = (substr_so_far.size() > ans) ? substr_so_far.size() : ans;
            return;
        }
        for(int i = start; i < s.length(); i++){
            string cand = s.substr(start,  i - start + 1);
            if(!substr_so_far.insert(cand).second) continue;
            dfs(s, i+1, ans);
            substr_so_far.erase(cand);
        }
    }
    /* solution 2: bitmask + unordered_set
     * We use a set of bitmask to represent the ways to split the string.
     * Once we split a substring, we check if the substr has already existed in
     * our set since the problem is asking for unique substrings.
     * If string length = n, then we can split at most n-1 substrings
     * so the bitmask can range from 0 ~ 1 <<n-1
     * (note that for the end of string we must split)
     * Ex: ababccc bitmask = 1101101 (1: split / 0: do not split)
     *        ababccc 
     *        1101101
     *     ------------
     *    ==> we can split the string into a, b, ab, c, cc 5 substrings
     *    ==> bitmask can be 0x0 to 0x1111111
     *
     */
    int sol2(string& s){
        int n = s.length();
        int split_ways = 1 << (n-1);
        unordered_set<string> seen;
        int ans = 0;
        //Choose a pattern
        //ex: a pattern can be 0x1101101
        for(int pattern = 0; pattern < split_ways; pattern++){
            //__builtin_popcount(pattern) returns the amount of bit that is 1
            //since the amount of bit 1 means the number of substring that
            //the pattern split
            if(__builtin_popcount(pattern) < ans) continue;
            int start = 0;
            bool validstr = true;
            //split the pattern by checking each bit
            for(int idx = 0; idx < n && validstr; idx++){
                if(pattern & (1<<idx) || (idx == n-1)){
                    string str = s.substr(start, idx - start + 1);
                    start = idx + 1;
                    //if we already insert this substring into seen table
                    //it will return false
                    validstr &= seen.insert(str).second;
                }
            }
            if(validstr && seen.size() > ans)
                ans = seen.size();
            //clear the seen table for the next iteration
            seen.clear();
        }
        return ans;
    }
public:
    int maxUniqueSplit(string s) {
        /* solution 1:
        if(s.length() == 1)
            return s.length();
        int ans = 0;
        dfs(s, 0, ans);
        return ans;
        */
        return sol2(s);
    }
};
