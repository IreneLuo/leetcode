class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        /* Solution:
         * 1. create an unordered_map<char, int> to store each character and its index
         * 2. Iterate over the character in s
         *   a. if cannot find the key in map --> add character and idx into map
         *   b. if find the key in map
         *      1. calculate current length of longest substring
         *      2. clear and set a new starting index
         *      3. update value in the map
         * 3. Calculate current length of longest substring
         * faster than 73.53% / memory less than 56.78%
         * time complexity = O(n)
         * space complexity = O(n)
         */
        if (s == "")
            return 0;

        unordered_map<char, int> map;// space complexity = O(n)
        int start = 0;
        int current_longest_length = 0;
        int i = 0;
        for (i = 0; i < s.size(); i++) { // time complexity = O(n)
            auto it = map.find(s[i]);
            if (it == map.end()) {
                map.insert(make_pair(s[i], i));

            } else {
                current_longest_length = max(current_longest_length, i - start);
                // for case "abba", when it comes to start = 2, s[3] = a,
                // "a" can be found in map with value 0
                // new start = 0 + 1 = 1 < start = 2 --> error, since new start should always > start
                if ((it->second + 1) > start)
                    start = it->second + 1;
                it->second = i;
    
            }
        }
        current_longest_length = max(current_longest_length, i - start);
        return current_longest_length;
    }
};
