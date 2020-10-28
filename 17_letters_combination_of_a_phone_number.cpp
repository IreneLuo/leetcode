class Solution {
public:
    /* solution:
     * 1. store the mappings into a hash table
     *    ex: <key, value> = <4, "ghj">
     * 2. we use a recursive function to go through each digit in input
     *    In the recursive function:
     *    0. if this digit is out of the length, store the temp str,
     *       and return. It means we've finished a pair of ans.
     *    1. find the mapping value of this digit(we called candidate)
     *    2. insert a character of the candidate into the temp str
     *    3. go to next digit and call the recursive function again.
     * ex: "23" --> "abc" & "def"
     *  for 2 , iterate "abc"
     *          1. --> str = a
     *          for 3 , iterate "def"
     *                  --> str = ad --> hit the end of input, return
     *                      str = ae --> hit the end of input, return
     *                      str = af --> hit the end of input, return
     *          we've iterated over "def" so return
     *          2. --> str = b
     *          for 3 , iterate "def"
     *                  --> str = ad --> hit the end of input, return
     *                      str = ae --> hit the end of input, return
     *                      str = af --> hit the end of input, return
     *          we've iterated over "def" so return
     *          3....
     *
     *  time complexity = O(4^n)
     *  space complexity = O(n) //the depth of the recursive calls (stack)
     */
    unordered_map<int, string> map  = {
        {0, ""}, {1, ""}, {2, "abc"},
        {3, "def"}, {4, "ghi"}, {5, "jkl"}, {6, "mno"},
        {7, "pqrs"}, {8, "tuv"}, {9, "wxyz"}
    };
    vector<string> letterCombinations(string digits) {
        if(digits.size() == 0) return {};
        vector<string> ans;
        _letterCombinations(0, "", digits, ans);
        return ans;  
    }
    void _letterCombinations(int order, string pair,
                        string input, vector<string>& ans){
        if(order == input.size()){
            ans.push_back(pair);
            return;
        }

        int digit = input[order] - '0';
        string candidate;
        // time = O(1)
        if (map.find(digit) != map.end())
            candidate = map.at(digit);
        // max size of candidate is 4 so for this for loop
        // if n is a huge value, the time for this loop will be 4 again
        // so the time = O(1)
        for(int i = 0; i < candidate.size(); i++){
            pair += candidate[i];
            // view1:
            // but how many times do we call this recursive function?
            // the depth of calls = n (since we iterate over n digits)
            // branching factor = 4 (general)
            // so time = O(4^n)
            _letterCombinations(order+1, pair, input, ans);
            pair = pair.substr(0, pair.length()-1);
            // view2:
            // we can also use T(n)<= 4T(n-1)+O(1) to express the time complexity
            // 4 is because we have run candidate 4 times
            // T(n-1) is because while we see the next digit, n will -1
        }
    }
};
