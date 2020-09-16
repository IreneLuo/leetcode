class Solution {
public:
    bool isValid(string s) {
        /* solution:
         * Main idea: push the open brackets, then pop out the item from
         *            from the stack when s[i] is an close brackets
         * 1. create a map to record items <"close bracket", "open bracket">
         * 2. traverse over the character in the string
         *    a. push the char into the stask if it's an open bracket
         *    b. return false if it's a close bracket, but there's nothing can be
         *       popped-out from the stack.
         *    b. pop out the char from the stack if it's not an open bracket.
         *       Compare the pop-out value with the value in map
         *       1. keep checking the next char if comparing succeed.
         *       2. return false if comparing fail
         * 3. After traversing over the string,
         *    return true if stack.length is 0, return false if not
         *
         * Time complexity: O(n)
         * Space complexity: O(n)
         * Note> if there's only one type of parentheses, we can use a
         *       counter instead of a stack to save space to O(1).
         *       if we see an open bracket, counter++
         *       if we see a close bracket, counter--
         *       if counter == 0, return true...
         */
        unordered_map<char, char> symbol_map ({{')','('}, 
                                            {'}','{'}, 
                                            {']','['}});
        stack<int> open_stack;
        for (int i = 0; i < s.size(); i++) {
            //find a pair in the map --> pop out and compare
            if(symbol_map.find(s[i]) != symbol_map.end()) {
                // ex: "]["--> is unbalanced
                if(open_stack.empty()) {
                    return false;
                }else {
                    char pop_symbol = open_stack.top();
                    char map_symbol = symbol_map.at(s[i]);
                    if (pop_symbol != map_symbol)
                        return false;
                    else // compairing finished, so pop out the top value
                        open_stack.pop();
                }
            // cannot find a pair in the map --> push to the stack
            } else {
                open_stack.push(s[i]);
            }
        }
        return (open_stack.size() == 0);
    }
};
