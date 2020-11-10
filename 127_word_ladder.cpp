class Solution {
public:
    /* solution:
     * We can consider this problem as a graph problem.
     * The beginWord is a start vertex
     * The endWord is an end vertex
     * The wordList is other vertices
     * And we have to find a shortest path from start vertex to end vertex
     * The problem is we don't know the relationships of each vertex.
     * Here's the idea:
     * ex: for a word "hit" --> we can change any one of a character of it,
     *                          so the patterns are: *it, h*t, hi*
     *     we can construct a hashtbl and use those patterns as keys, those words as values
     *     so that we can bind all the vertices together by using these keys.
     *     For this problem, we can build a hashtbl from wordList like this:
     *     <key>   <value>
     *     *ot      hot, dot, lot
     *     h*t      hot 
     *     ho*      hot
     *     d*t      dot
     *     do*      dot, dog
     *     l*t      lot
     *     lo*      lot, log
     *     *og      dog, log, cog
     *     l*g      log
     *     c*g      cog
     *     co*      cog
     *    
     *     in this way, we can easily find the neighbors of beginWord by using patterns.
     *     
     * time complexity = O(W*L)   //initialize_hashtbl_for_word_patterns()
     *    - W = the wordlist length
     *    - L = length of each word
     * space complexity = O(W)
     *
     * note that in BackToBackSWE, the solution is a bit different (use a distance and save in each node rather using one variable "level")
     */
    unordered_map<string, vector<string>> hashtbl;
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<string> q;
        set<string> visited;

        //initialize hashtbl
        initialize_hashtbl_for_word_patterns(wordList);
        //push beginWord into queue and visited set
        q.push(beginWord);
        visited.insert(beginWord);
        int level = 1;
        int cnt_in_level = 1;
        //use queue to investigate all the possible wordlist
        while(!q.empty()){
            string word = q.front();
            q.pop();
            //try every pattern of this word to find it's neighbors
            //one pattern will get a list of neighbors
            for(int i = 0; i < word.size(); i++){
                vector<string> possible_words = find_possible_words_by_pattern(i, word);
                //investigate every neighbor in the possible_words
                for(string s : possible_words){
                    //this word is the end
                    if(s == endWord)
                        return level+1; //including beginWord
                    //first time to access this word
                    if(visited.find(s) == visited.end()){
                        q.push(s);
                        visited.insert(s);
                    }
                }  
            }
            cnt_in_level--;
            //after dealing with all neighbors, update level value and get ready to handle the next level
            if(cnt_in_level == 0){
                level++;
                cnt_in_level = q.size();
            }
        }
        return 0;
    }
    void initialize_hashtbl_for_word_patterns(vector<string>& wordList){
        for(string s : wordList){
            for(int i = 0; i < s.size(); i++){
                string pattern = s.substr(0, i) + "*"+s.substr(i+1, s.size()-(i+1));
                if(hashtbl.find(pattern) == hashtbl.end()){
                    vector<string> v;
                    hashtbl.insert(make_pair(pattern, v));
                }
                hashtbl[pattern].push_back(s);
            }
        }
    }
    vector<string> find_possible_words_by_pattern(int i, string s){
        string pattern = s.substr(0, i) + "*"+s.substr(i+1, s.size()-(i+1));
        //if it cannot find this pattern, return null
        return hashtbl[pattern];
    }
};
