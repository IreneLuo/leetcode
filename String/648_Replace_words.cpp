class Solution {
public:
    vector<string> parsing_str(string str, char delimeter) {
        istringstream iss(str);
        string result;
        vector<string> ans;
        while(getline(iss, result, delimeter))
            ans.push_back(result);
        return ans;
    }
    string replaceWords(vector<string>& dictionary, string sentence) {
        /* solution 1:
         * 1. traverse each word in sentence
         * 2. for each word
         *    a) start with the first letter--> find in dictionary
         *    b) if a) fail, see the next letter
         *    c) if a) success, replace the word with prefix
         */
        //or we could use a trie
        unordered_set<string> dict;
        for(auto s: dictionary)
            dict.insert(s);

        vector<string> splitted = parsing_str(sentence, ' ');
        for(auto& word: splitted){
            for(int len = 0; len < word.length(); len++){
                string s = word.substr(0, len);
                if(dict.count(s)){
                    word = s;
                    break;
                }
            }
        }
        string ans;
        for(int i = 0; i < splitted.size(); i++){
            ans += splitted[i];
            if(i != splitted.size() -1)
                ans += " ";
        }
        return ans;
    }
};
