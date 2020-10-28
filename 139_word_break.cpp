class Solution {
public:
    /* Solution: bottom up dynamic programing
     * we decompose our string to : 
     * string = prefix + suffix
     *  - prefix: we use array prefixInDict to keep a single dynamic programming state
     *    that indicates whether or not we are able to decompose our string.
     *  - suffix: we search if there's any word in the dictionary as same as the suffix
     * time complexity = O(n*m)
     * space complexity = O(n)
     * 
     * note that for the optimization, check "back to back swe"
     */
    bool wordBreak(string s, vector<string>& wordDict) {
        int strsize = s.size();
        //prefixInDict[i] = true means that we can decompose the prefix s[1..i] of our string
        vector<bool> prefixInDict(strsize + 1);
        //base case: we can decompose empty string
        prefixInDict[0] = true;
        //we start to see prefix[1...i] can be decomposed or not
        for(int i = 1; i <= strsize; i++){
            for(const auto& word : wordDict){
                //if word size > i, then the word is not a substring of our string, so skip this word
                if(i < word.size())
                    continue;
                //string[1...i] = prefix[1...mididx-1]+suffix[mididx...]
                //ex: string = "hello", word = "llo".
                //    when i = 5, mididx = 5-3=2
                //    "hello" = "he" + "llo" -->2. we look up the dictionary to see if "llo" is one of a word in it.
                //                |----------> 1. we access prefixInDict[2] to check that "he" can be decomposed or not
                //    if 1,2 are true, then string "hello" can be decomposed, so we set prefixInDict[5] = true
                int mididx = i - word.size();
                // prefix + suffix == word in dict
                if(prefixInDict[mididx] == true && s.substr(mididx, word.size()) == word){
                    prefixInDict[i] = true;
                    break;
                }
            }
        }
        return prefixInDict[strsize];
    }
};
