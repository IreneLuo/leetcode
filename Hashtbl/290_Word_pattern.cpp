class Solution {
public:
    /* Solution 2: Two Hash Maps
     * 1. Parse strings str to words ("dog cat cat dog" -> "dog", "cat", "cat", "dog")
     * 2. Traverse each word in str and each character in pattern.
     *    ex: pattern="abba" and str="dog cat cat fish" 
     *    1> "a" and "dog"    --> cannot find any key in hash tbls
     *       insert to hashtbl_pat = [< a, dog>]
     *       insert to hashtbl_str = [<dog, a>]
     *    2> "b" and "cat" --> cannot find any key in hash tbls
     *       insert to hashtbl_pat = [< a, dog>, <b, cat>]
     *       insert to hashtbl_str = [<dog, a>, <cat, b>]
     *    3> "b" and "cat" --> find a key = b in hastbl_pat,
     *                         retrieve the value "cat"
     *        hashtbl[b] = cat = "cat" in str --> match
     *    4> "a" and "fish" --> find a key a
     *        hashtbl[a] = dog != "fish" in str --> mismatch
     * 
     * time complexity = O(n)
     *    - n: the number of words in s or 
     *          the number of characters in pattern
     * Space complexity = O(m)
     *    - m: the number of unique words in s
     *    - the map for characters  has space complexity O(1) since
     *      there can at most be 26 keys
     */
    vector<string> parsing_str(string str) {
        vector<string> decode_str;
        unordered_map<string, int> map;
        int map_value = 1;
        string::size_type left = 0, right = 0;
        
        while(right != string::npos) {
            right = str.find(" ", left);
            string temp;
            if (right == string::npos) {
                temp = str.substr(left, str.size() - left);         
            } else {
                // read a word in str
                temp = str.substr(left, right-left);
            }
            decode_str.push_back(temp);  
            left = right + 1;
        }
        return decode_str; 
    }

    bool wordPattern(string pattern, string str) {

        if (pattern == "")
            return false;

        unordered_map<char, string> map_pat;
        unordered_map<string, char> map_str;
        vector<string> parsing_a = parsing_str(str);
        for(int i = 0; i < parsing_a.size(); i++) {
            char *ch = &pattern[i];
            auto itpat = map_pat.find(*ch);
            auto itstr = map_str.find(parsing_a[i]);
            if (itpat == map_pat.end()) {
                if(itstr == map_str.end()){
                    // cannot find both, so insert them into hash tbls
                    map_pat.insert(pair<char, string> (*ch, parsing_a[i]));
                    map_str.insert(pair<string, char> (parsing_a[i], *ch));
                }else{
                    // one match but the other mismatch, return false
                    return false;
                }
            } else {
                // if cannot find the pattern as a key in str's hash tbl, then return fail
                if (itpat->second != itstr->first)
                   return false;
            }
        }
        return true;        
    }
};
