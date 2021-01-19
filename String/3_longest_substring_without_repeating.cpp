class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        /* Solution:
         * 1. create an unordered_map<char, int> to store 
         *    each character and its index
         *    --> since we already know that there's at most 128
         *        characters in ASCII so we use vector instead of map
         *        to save more space
         * 2. Iterate over the character in s
         *   a. if cannot find the key in map --> add character and idx into map
         *   b. if find the key in map
         *      1. calculate the length of the sliding window
         *      2. clear and set a new starting index
         *      3. update value in the map
         * time complexity = O(n)
         * space complexity = O(n)
         *          0 1 2 3 4 5 6 7 8
         * Example: a b c d e a f d b
         *          i       j                    a:1, b:2, c:3, d:4, e:5
         *          i         j                  a is dup, i=max(0,map[a])=1
         *            i       j                  len=j-i+1=5, update a:6
         *            i         j                a:6, b:2, c:3, d:4, e:5,f:7
         *              i         j              a:6, b:1, c:3, d:4, e:5,f:7, d is dup
         *                  i     j              i=max(2,map[d])=4, len=j-i+1=5, update d:9
         *                  i       j            a:6, b:1, c:3, d:9, e:5,f:7, b is dup
         *            ^     i       j            map[b]=1 < i so i won't change-> case 1
         *                                       len = j-i+1=5
         *                                       a:6, b:9, c:3, d:9, e:5,f:7
         *
         */
        if (s == "")
            return 0;

        vector<int> nextPos(128, -1);
        int maxlength = INT_MIN;
        for(int start = 0, curr = 0; curr < s.length(); curr++){
            /* Case 1: why we need to use max()?
             * if curr has appeared once, get the previous position of curr
             * if the preveous positoin < start, then we don't have to
             * change the start(it means this letter doesn't in the sliding
             * window)
             *
             */
            char c = s[curr];
            start = max(nextPos[c], start);
            /* calculate the lenght of this sliding window */
            maxlength = max(maxlength, curr - start + 1);
            /* update current position of this letter
             * we add 1 because it's the new position that
             * we can start next time
             */
            nextPos[c] = curr + 1;
        }
        return maxlength;
    }
};
