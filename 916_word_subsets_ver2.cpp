class Solution {
public:
    #define MAX_LETTER 26
    void count_letters(string s, int* map) {
        for (int j = 0; j < MAX_LETTER; j++)
            map[j] = 0;

        for(int i = 0; i < s.size(); i++) {
            int idx = s[i] - 'a';
            map[idx]++;
        }
    }
    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
        /* Solution 2:
         * 1. combine set B into one word
         *    a. count letters in B and keep the max counts
         * 2. iterate over each word in a
         *    a. check if letter counts in A >= letter counts in B
         *    b. add to output if universal
         * note.
         *   unordered_map version: faster than 7.98% / memory less than 11.76%
         *   array version: faster than 89.71% / memory less than 82.35%
         *   Time complexity = O(max(B*(longest string in B), A*(longest string in A)))
         *   Space complexity = O(A)
         *     // because the max count of pair in maps will be 26 --> O(1)
         *     // so we only only have to consider the space of output vector
         */
        int map_b[MAX_LETTER] = {0};
        int map_t[MAX_LETTER] = {0};
        vector<string> ans;
        // traverse each string in B
        for (int i = 0; i < B.size(); i++) {
            // get a temp map from a string in B
            count_letters(B[i], map_t);
            // compare map_t with the map_b and keep the max value
            for (int j = 0; j < MAX_LETTER; j++)
                map_b[j] = max(map_b[j], map_t[j]);
        }

        // now map_b is ready!       
        // traverse each string in A
        for (int i = 0; i < A.size(); i++) {
            // get a temp map from a string in A
            count_letters(A[i], map_t);
            int j;
            // compare map_b with the map_t, if match, append to output
            for (j = 0; j < MAX_LETTER; j++) {
                 if (map_t[j] < map_b[j])
                     break;
             }
            if (j == MAX_LETTER) //current string in A is universal
                ans.push_back(A[i]); 
        }

        return ans;
    }
};
