class MagicDictionary {
    /* solution:
     * Idea: fuzzy match
     * 1. create a fuzzy pattern for each word in the dictionary
     *                          buildDict()                   search()
     *      ----------------------------------------------------------------------
     *   words =      [hello] [hallo]         [pat]           [hello]
     *      ----------------------------------------------------------------------
     *   dict : {"*ello", "h"}{"*allo", "h"} {"*at", "p"}   {"*ello", "h"} -> find the pattern but h has already in dict->x
     *                {"h*llo", "e, a"}      {"p*t", "a"}   {"h*llo", "e"} -> find the pattern in the dict, and we have two choices
     *          {"he*lo", "l"}{"ha*lo", "l"} {"pa*", "t"}   {"he*lo", "l"}    "e, a" to replace *. However, we cannot choose e, since 
     *          {"hel*o", "l"}{"hal*o", "l"}                {"hel*o", "l"}     hello is the word the we want to search, so we can choose
     *          {"hell*", "o"}{"hall*", "o"}                {"hell*", "o"}     a, and h*llo can be replaced to hallo-> v
     *              |      |
     *              v      |---> * is changed from "o"
     *        a fuzzy pattern that we can use while searching a target word
     *
     *  time complexity = O(mn)
     *    Build Dict: O(mn)
     *       - create n fuzzy patterns for a word (length of a word=n)
     *       - total m words
     *    Search: O(n)
     *  space complexity = O(mn)
     */
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        dict.clear();
    }
    
    void buildDict(vector<string> dictionary) {
        for(string word: dictionary){
            /* change a character to * at one time */
            for(int i = 0; i < word.length(); i++){
                char ch = word[i];
                word[i] = '*';
                /* find the key==word, and insert the char into the entry */
                dict[word].insert(ch);
                /* recover the character */
                word[i] = ch;
            }
        }
    }
    
    bool search(string searchWord) {
        for(int i = 0; i < searchWord.length(); i++){
            char ch = searchWord[i];
            searchWord[i] = '*';
            if(dict.count(searchWord)){
                auto& cand_set = dict[searchWord];
                /* dict = ["h*llo", "a,e"]
                 * searchWord = hello
                 * When we fuzz the searchWord to "h*llo", and the orignal char is e
                 * we found that * can be replaced by a and e.
                 * However, we cannot replace * by e since the searchWord=hello.
                 * Luckily, we can replace * by a and get a new word "hallo"
                 * so here we just check
                 *   if original char cannot be found in the set, return true
                 *   if original char can be found in the set, but the size of set > 1,
                 *        which means that we can replace * by other characters, return true
                 */
                if(!cand_set.count(ch) || cand_set.size() > 1)
                    return true;
            }
            searchWord[i] = ch;
        }
        return false;
    }
private:
    unordered_map<string, unordered_set<char>> dict;
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
