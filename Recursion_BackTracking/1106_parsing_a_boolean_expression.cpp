class Solution {
    /* solution: recursion
     * Step:
     *   Extract a character ch:
     *   if ch == t, return true
     *   if ch == f, return false
     *   if ch == !, parse(string+1) //to skip (
     *   if ch == & or |, parse(string+1) //to skip (
     *      and & or | the answer that return from parse(string+1)
     * Constraints:
     *   if ch == {} () ,  skip it
     * Goal:
     *   if ch ==  the end of the string
     *
     * time complexity = O(n)
     * space complexity = O(1)
     *
     * Example:
     *   parse("|(&(t,f,t),!(t))")
     *    =false |= parse("&(t,f,t),!(t))") 
     *                 = true  &= parse("t,f,t),!(t))")
     *                 = true  &= parse("f,t),!(t))")
     *                 = false &= parse("t),!(t))")
     *                 = false            ^break here
     *    =false |= parse("!(t))")
     *                 = !parse("t))")
     *                 = !true
     *    =false
     * 
     */
public:
    bool parseBoolExpr(string expression) {
        int start = 0;
        return parse(expression, start);
    }
    bool parse(string& expr, int& idx){
        char ch = expr[idx];
        //once we extract a character, idx++
        idx++;
        if(ch == 't') return true;
        if(ch == 'f') return false;
        if(ch == '!'){
            //++idx to make sure that we start at a meaningful character(not (){},)
            bool ans = !parse(expr, ++idx);
            //now idx will at ), so we increase idx to 1 to start a new parse()
            //with a sub-expression if possible
            idx++;
            return ans;
        }
        bool is_and = (ch == '&');
        bool ans = is_and;
        //idx++ to make sure that we start at a meaningful character(not (){},)
        idx++;
        //& and | operator might have more operands, so we use a while loop to handle them
        while(true){
            if(is_and)
                ans &= parse(expr, idx);
            else
                ans |= parse(expr, idx);
            //if current position is a ')', break the while loop since 
            //& or | operation has finished
            //no matter current position is a ')' or not, increase idx to 1
            if(expr[idx++] == ')'){
                break;
            }
        }
        return ans;
    }
    
};
