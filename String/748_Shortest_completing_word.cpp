class Solution {
    /* solution:
     *  1. create a hashtbl for storing the alphabets in the licensePlate
     *  2. iterate over the words to check that:
     *       do all the alphabets in hashtbl also exist in the word
     * time complexity = O(n)
     *    n = words length
     * space complexity = O(1) //hashtbl 26
     */
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        //since hashtbl only contains alphabets, we use vector instead of unordered_map
        //to save more time
        vector<int> dict(26, 0);
        //O(7)
        for(char ch: licensePlate)
            if(isalpha(ch)) ++dict[tolower(ch)-'a'];
        string ans;
        int min_len = INT_MAX;
        //O(wordslen)*O(26)
        for(const string& s: words){
            if(s.length() >= min_len) continue;
            if(!match(s, dict)) continue;
            min_len = s.length();
            ans = s;
        }
        return ans;
    }
private:
    //O(26)
    bool match(const string& str, vector<int>& dict){
        vector<int> strfreq(26, 0);
        for(char ch: str) ++strfreq[tolower(ch)-'a'];
        for(int i = 0; i < 26; i++)
            if(strfreq[i] < dict[i]) return false;
        return true;
    }
};
