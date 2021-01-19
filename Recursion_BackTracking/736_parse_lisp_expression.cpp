class Solution {
   /* solution: recursion + hashtbl
    * Example: parse("(mult 3 (add 2 3))")
    *          = parse(3) * parse("(add 2 3)")
    *                        = parse("2") + parse("3")
    *          = parse(3) * 5
    *          = 15
    * Example: parse("(let x 2 (mult x 5))")
    *          => token=let,x,2,(mult x 5)
    *          => insert(x,2)
    *          => parse("(mult x 5)")
    *              = parse("x") * parse("5")
    *              = 10
    * Example: parse("(let a1 3 b2 (add a1 1) b2)")
    *            => token=let,a1,3,b2,(add a1 1) b2)
    *                         |--|  |-------|    |-|
    *            => insert(a1, parse("3"))
    *               insert(b2, parse("(add a1 1)"))
    *                          => token=add,a1,1
    *                              = parse("a1") + parse("1")
    *                              = 4
    *            => parse("b2") = 4
    * reference: https://www.youtube.com/watch?v=XS6CXH2UORM&ab_channel=happygirlzt
    */
public:
    int evaluate(string expression) {
        return parse(expression, {});
    }
    /* int parse(string expr, unordered_map<string, int> map)
     *  - Call split() to retrieve the tokens in the expression
     *  - Analysis the token in the expression and
     *     - caculate the answer with operands (*, +)
     *     - create a new map if token is "let"
     */
    int parse(string expr, unordered_map<string, int> map){
        //we have to convert from string to const char* for using atoi()
        if(is_number(expr)) return atoi(expr.c_str());
        if(is_alpha(expr)) return map[expr];
        int ans = 0;
        vector<string> subexpr = split(expr);
        /* subexpr[0] = "add"/"mult"/"let"
         * subexpr[1] = a number or a string 
         * subexpr[2] = a number or a string
         * subexpr[...]
         * subexpr[n] = a sub-expression (if subexpr[0] is "let")
         */
        if(subexpr[0] == "add"){
            ans = parse(subexpr[1], map) + parse(subexpr[2], map);
        }else if(subexpr[0] == "mult"){
            ans = parse(subexpr[1], map) * parse(subexpr[2], map);
        }else{
            //Dealing with inner "let" expression
            //we create a new map with original map data and
            //insert new data for current "let" expression
            unordered_map<string, int> newmap = map;
            for(int i = 1; i < subexpr.size()-1; i+=2){
                string key = subexpr[i];
                newmap[key] = parse(subexpr[i+1], newmap);
            }
            ans = parse(subexpr.back(), newmap);
        }
        return ans;
    }
    bool is_number(string str){
        char ch = str[0];
        return (ch >= '0' && ch <= '9') || ch == '-';
    }
    //a token could combine with an alphabet and a digit: a1, b2
    //so we only check the first character
    bool is_alpha(string str){
        char ch = str[0];
        return (ch >= 'a' && ch <='z');
    }
    /* list<string> split(string str)
     *  - Split an expression into several token and
     *    return them as a list
     */
    vector<string> split(string str){
        vector<string> tokenlist;
        //remove the outer ()
        int start = 0;
        str = str.substr(1, str.length()-2);
        //use start and end index to split each token
        while(start < str.length()){
            int end = getTokenEndingIdx(str, start);
            string token = str.substr(start, end - start);
            tokenlist.push_back(token);
            start = end + 1;
        }
        return tokenlist;
    }
    /* int getTokenEndingIdx(string str, int start)
     * find out a token's ending index
     */
    int getTokenEndingIdx(string str, int start){
        int idx = start;
        //extract the whole expression in the ()
        if(str[idx] == '('){
            int count = 1;
            idx++;
            while(idx < str.length() && count > 0){
                if(str[idx] == '(')
                    count++;
                else if(str[idx] == ')')
                    count--;
                idx++;
            }
        }else{
            while(idx < str.length() && str[idx] != ' '){
                idx++;
            }
        }
        return idx;
    }
};
