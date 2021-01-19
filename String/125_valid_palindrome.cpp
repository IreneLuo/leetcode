 bool isPalindrome(string s) {
        /* Solution 1:
         * 1. remove all the non alphanumeric characters in string s and store in string input
         * 2. check if string input is palidrome or not
         *      method 1. make a copy of string input and reverse it, then compare with string input
         *      method 2. compare the beginning element with the ending element in string input.
         *                Then compare the next and the previous element until meet the center of the string.
         */
        if (s == "")
            return true;

        string input;
        for (int i = 0; i < s.size(); i++) {
            if (isalpha(s[i]))
                input += tolower(s[i]);
            else if (isdigit(s[i]))
                input += s[i];
        }
        /* method 1
        string input_inverse;
        input_inverse = input;
        reverse(input_inverse.begin(), input_inverse.end());
        return (input == input_inverse);
        */
        /* method 2 */
        bool ans = true;
        for (int i = 0; i < input.size() / 2; i++) {
            if (input[i] != input[input.size()-1-i])
                ans = false;
        }
        return ans;
    }
