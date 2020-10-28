class Solution {
public:
    /* solution:
     * Compare words[i] & words[i+1] by each character, and return false in following situations
     *   - if the ith character of  words[i] > words[i+1], return false (if < return true)
     *   - if words[i] is shorter than words[i+1] but not a substring of words[i+1], reutrn false
     *
     *  time complexity = O(n), where n is the size of words
     *  space complexity = O(1)
     */
    vector<int> order_dic;
    bool is_lexicographicaly_sorted(string str1, string str2){
        int len_str1 = str1.size();
        int len_str2 = str2.size();

        for(int i = 0; i < len_str1 && i < len_str2; i++){
            //once we find a different character, compare and return the result
            if(str1[i] != str2[i])
                return (order_dic[str1[i] - 'a'] < order_dic[str2[i] - 'a']);
        }
        // if all the characters' order are correct, but str1 is longer than str2, return false
        return (len_str1 < len_str2);
    }
    bool isAlienSorted(vector<string>& words, string order) {
        // create an dictionary for the characters in string order
        // to record the orders.
        for(int i = 0; i < 26; i++)
            order_dic.push_back(0);

        for(int i = 0; i < order.size(); i++)
            order_dic[order[i] - 'a'] = i;

        for(int i = 0; i < words.size() - 1; i++){
            if(!is_lexicographicaly_sorted(words[i], words[i+1]))
                return false;
        }
        // if we compare all the words and still nothing wrong, return true
        return true;
    }
};
