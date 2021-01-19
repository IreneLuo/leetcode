class Solution {
public:
    bool checkRecord(string s) {
        /* solution 1
        int absent = 0;
        int late = 0;
        for(char ch: s){
            if(ch == 'A'){
                ++absent;
                //we only count late when L appears continuously
                late = 0;
            }
            if(ch == 'L')
                ++late;
            if(absent > 1 || late > 2) return false;
        }
        return true; 
        */
        /* solution 2: using regular expression
         * Rules for more than one 'A' (absent):
         *     - . : an arbitrarily symbol
         *     - * : a symbol can appear once or more than once
         *     so A.*A could be AA or ABA or ABBBLLA
         * Rules for more than two continuous 'L' (late)
         *     - we just use LLL
         */
        return !std::regex_search(s, std::regex("A.*A|LLL"));
    }
};
