/* solution: Hashtbl
 * Ex:  ababcbacadefegdehijhklij
 *      S       E          --> the last idx of a is E, so now the temporary substring is between S and E
 *       t   t' E          --> next, we look at b, the last idx of b is t', and it's smaller than E.
 *              t          --> when t == E, the ans = E-S+1
 *               S    E    --> move S to E+1. the last idx of d is E, so now the temporary substring is between S and E
 *                t    t'  --> next, we look at e, the last idx of e is t'>E, so we have move extend E by setting E=t'
 *               S t   E   --> we keep iterate over the string to find out all the substrings that match the needs of our problem
 *
 * Note that we use a table to record all the last idx of each character in the string
 * to speed up the process
 * time complexity = O(n)
 * space complexity = O(26) or O(128)
 *    - if O(26): using char as index
 *    - if O(128): using ascii code as index
 * reference: HuaHua's video
 */
class Solution {
public:
    vector<int> partitionLabels(string S) {
        //record the last idx of each character in S
        vector<int> map(128, 0);
        for(int i = 0; i < S.length(); i++)
            map[S[i]] = i;
        //check the last idx of a character is bigger than the end idx so far
        vector<int> ans;
        int start = 0;
        int end = 0;
        for(int i = 0; i < S.length(); i++){
            end = max(end, map[S[i]]);
            if(i == end){
                ans.push_back(end-start+1);
                start = end+1;
            }
        }
        return ans;
    }
};
