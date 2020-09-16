class Solution {
public:
    string minRemoveToMakeValid(string s) {
        /* solution :
         * We use a stack to check whether parentheses are pairs or not.
         * And we keep the idx of the char that need to be removed in an array.
         * While we traversing the character in the string:
         * 1. push the index of "(" into the stack
         * 2. if we encounter a ")", then pop out the top of the stack
         *    (which means we find a match pair of "()")
         * 3. when we encounter a ")" but the stack is empty then remove this ")"
         * 4. after traversing the string, if stack is non-empty, then remove those
         *    "(" from the string. (which means the items in the stack cannot become
         *     pairs)
         */
        stack<int> mystack;
        // keep the index of the char that need to be removed
        // the items set to true will be removed at the end;
        vector<bool> remove(s.size(), false);
        string ans;
        
        for(int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                mystack.push(i);
                //set true until we find the pair of this char
                remove.at(mystack.top()) = true;
            } else if (s[i] == ')') {
                if (!mystack.empty()) { //find a pair
                    remove.at(mystack.top()) = false;
                    mystack.pop();
                }else { //s[i] cannot find any pair, so remove it later
                    remove.at(i) = true;
                }          
            }
        }

        //anything remains in the stack cannot become pairs, so remove them later
        while(!mystack.empty()) {
            remove.at(mystack.top()) = true;
            mystack.pop();
        }

        //remove the items and combine a new string
        for (int i = 0; i < s.size(); i++) {
            if(remove.at(i))
                continue;
            else
                ans+=s[i];
        }
        return ans;
    }
};
