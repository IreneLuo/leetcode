class Solution {
public:
    /* solution:
     * 1. create a hash table (hashtbl_target) for characters in target
     * 2. create a hash table (hashtbl_window_char) for characters in input
     * 3. we use a left and a right pointer to control a substring window
     *    a. at first, left = right = 0
     *    b. start moving the right pointer, and store every char into the hashtbl_window_char,
     *       until we collect all the characters in the target
     *    c. Once we collect all the chararacter, we store the substring that embraced by the window,
     *       and start moving the left pointer (since this substring meets our target but it might not the smallest string)
     *    d. before moving the left pointer
     *       - remember to update the value in hashtbl_window_char by decreasing 1
     *       - if the count in hashtbl_window_char is less than the count in hashtbl_target, stop moving,
     *         since the substring in the window is no longer meet the criteria
     *         (not all targeted characters constain in substring)
     *       - otherwise, keep moving the left pointer to find a smallest substring.
     * 
     *   s = search string length
     *   t = pattern string length
     * time complexity = O(S + T)
     *    - S for traversing the string. Since every single indice can be maximum touched two times(left and right pointer), and this goes in linear time
     *    - T for building requirments hashtable
     * space complexity = O(S + T)
     *    - T: in worst case, every character in t is unique, so we are going create T pairs items in the hashtbl
     *    - S: in worst case, the window contains the whole string of s, so we have to keep it in our ans. 
     *
     */
    string minWindow(string s, string t) {
        unordered_map<char, int> hashtbl_target;
        unordered_map<char, int> hashtbl_window;
        int charFreqInWindow = 0;
        int charFreqTarget = 0;
        int left = 0;
        int right = 0;
        string ans;

        /* insert <char, count> into the hash table
         * once we meet the char again, increase the counter by 1
         * Note) [] operator will return a value if key exists, return 0 if key doesn't exists
         */
        for(int i = 0; i < t.size(); i++)
            hashtbl_target[t[i]] = hashtbl_target[t[i]] + 1;

        charFreqTarget = hashtbl_target.size();

        while(right < s.size()){
            //insert <char, count> into the hashtbl_window
            char ch = s[right];
            hashtbl_window[ch] = hashtbl_window[ch] + 1;

            //find this char in the hashtbl_target
            auto it = hashtbl_target.find(ch);
            // if it exists, check character frequency in window is enough or not
            // if yes, charFreqInWindow+1 which means that we had already collected all the chars for this alphabet
            if(it != hashtbl_target.end()){
                //cout << "find in harshtbl_target : "<<ch<<endl;
                // cannot use >= here
                // if we use >=, we might count the same alphabet again
                // ex: if hashtbl_target[B] = 2
                //     then once hashtbl_window[B] >= 2, it will increase everytime when we go to this line
                //     However, we only want to know that if we have already collected all the char of this alphabet,
                //     so just increase once when we meet the criteria
                bool done_for_this_alph = hashtbl_window[ch] == hashtbl_target[ch];
                if(done_for_this_alph)
                    charFreqInWindow++;
            }
            // if we have collected all the alphabets, start moving the left pointer
            while(charFreqInWindow == charFreqTarget && left <= right){
                string candidate = s.substr(left, right - left + 1);
                if (candidate.size() < ans.size() || ans.size() == 0)
                    ans = candidate; 
                // before moving, decrease the count of this char
                ch = s[left];
                hashtbl_window[ch]--;
                // after decreasing the counter, check that do the new window still constains all the targeted characters
                // if not, decrease the charFreqInWindow
                it = hashtbl_target.find(ch);
                if(it != hashtbl_target.end()){
                    bool still_contains_all_char_in_target = hashtbl_window[ch] >= hashtbl_target[ch];
                    if(!still_contains_all_char_in_target)
                        charFreqInWindow--;
                }
                left++;
            }  
            right++;      
        }

        return ans;
    }
};
