/* solution: mapping/math
 * Observation:
 *    I    1     *) ab pattern: b>a
 *    II   2        if we find an ab pattern, we can calculate the answer
 *    III  3        by a+b-2a
 *    IV   4 *      Ex: IV = 1+5-1-1=4
 *    V    5            IX = 1+10-1-1=9
 *    VI   6
 *    VII  7
 *    VIII 8
 *    IX   9 *
 *    X   10
 *    
 *  time complexity = O(n)
 *  space complexity = O(1)
 */
class Solution {
public:
    int romanToInt(string s) {
        map<char, int> mapping_table{{'I', 1}, {'V', 5}, {'X', 10},{'L', 50},
                                     {'C', 100}, {'D', 500}, {'M', 1000}};
        int ans = 0;
        int p = 0;
        for (char i : s){
            ans += mapping_table[i];
            //if value of current idx > value of previous idx
            //ans = ans - 2 * value of previous idx
            if(p && (mapping_table[i] > mapping_table[p]))
                ans -= mapping_table[p] << 1; //IX = I + X - I - I = X - I
            p = i;
        }
        return ans;
    }
};
