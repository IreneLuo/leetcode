class Solution {
public:
    unordered_map<char, int> count_letters(string s) {
        unordered_map<char, int> map;

        for(int i = 0; i < s.size(); i++) {
            char ch = s[i];
            auto it = map.find(ch);
            if (it == map.end()) //not find
                map.insert(make_pair(ch, 1));
            else //if find, add value
                it->second = it->second + 1;
        }
        return map;
    }
    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
        /* Solution 2:
         * 1. combine set B into one word
         *    a. count letters in B and keep the max counts
         * 2. iterate over each word in a
         *    a. check if letter counts in A >= letter counts in B
         *    b. add to output if universal
         * note.
         *   faster than 7.98% / memory less than 11.76%
         *   Time complexity = O(max(B*(longest string in B), A*(longest string in A)))
         *   Space complexity = O(A)
         *     // because the max count of pair in maps will be 26 --> O(1)
         *     // so we only only have to consider the space of output vector
         */
        unordered_map<char, int> map_b;
        unordered_map<char, int> map_t;
        vector<string> ans;
        // traverse each string in B
        for (int i = 0; i < B.size(); i++) {
            // get a temp map from a string in B
            map_t = count_letters(B[i]);
            // compare map_t with the map_b and keep the max value
            for (auto it = map_t.begin(); it != map_t.end(); it++) {
                auto it2 = map_b.find(it->first); // if a key in map_t is also in map_b
                if (it2 == map_t.end()) //not find --> add it to map_b
                    map_b.insert(make_pair(it->first, it->second));
                else // if find -> keep the max count into map_b
                    it2-> second = max(it->second, it2->second);
            }
        }

        // now map_b is ready!       
        // traverse each string in A
        auto itb = map_b.begin();
        for (int i = 0; i < A.size(); i++) {
            // get a temp map from a string in A
            map_t = count_letters(A[i]);
            // compare map_b with the map_t, if match, append to output
            for (itb = map_b.begin(); itb != map_b.end(); itb++) {
                auto ita = map_t.find(itb->first); // if a key in map_t is also in map_b
                if (ita == map_t.end()) //not find --> current string in A is not universal
                    break;
                else { // if find -> continue
                    if(ita->second >= itb->second)
                        //see next letters
                        continue;
                    else
                        // fail --> current string in A is not universal
                        break;
                } 
            } // finished checking current string in A
            if(itb == map_b.end()) // current string in A is universal
                ans.push_back(A[i]);  
        }

        return ans;
    }
};
