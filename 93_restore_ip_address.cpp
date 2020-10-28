class Solution {
    /* Solution:
     * Let's think about choice, constraints, and our goal.
     * 1. choice: characters in 1 seg could be 1 to 3
     * 2. constraints: seg <= 255, cannot start with 0 (ex: 025 -> x)
     * 3. goal: 4 segments, and ptr(that we use to cut off a segment) should be length of input
     * So we use recursive function to handle this problem
     * For each segment, we use a for loop to decide the content of the segment
     * Once we decide the segment, then check the constraints
     * and then call the function again to deal with the next segment
     * until we meet the goal.
     *
     * time complexity = O(1)
     * space complexity = O(1)
     *
     *  branching factor = 3 (see below)
     *  depth = 4 (we need 4 segments) --> we'll have 4 recursive calls before base case stop us
     *  so time = 3 ^ 4, if n is a huge number, time still won't change
     *
     *                 25525511135
     *             /        |         \
     *  2.5525511135   25.525511135  255.25511135
     *                                 / | \
     *                                     255.255.11135
     *                                        / | \
     *                                            255.255.111.35
     *                                                 |
     *                                            255.255.111.35
     */
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> cand;
        vector<string> ans;
        _restoreIpAddresses(0, 0, s, cand, ans);
        return ans;
    }
#define STR2INT(s) (stoi(s))
    void candToAnswer(vector<string>& cand, vector<string>& ans){
        string tmp = cand[0]+"."+cand[1]+"."+cand[2]+"."+cand[3];
        ans.push_back(tmp);
    }
    bool StartWithNonZero(string s){
        if(s.size() > 1 && s[0] == '0')
            return false;
        return true;
    }
    void _restoreIpAddresses(int segStart, int segCnt, string input,
                             vector<string>& cand, vector<string>& ans){
        // base cases for time = O(1)
        if(segCnt == 4 && segStart == input.size())
            candToAnswer(cand, ans);
        else if(segCnt == 4)
            return;
        // for loop always run 3 iterations, so time = O(1)
        for(int i = 1; i <=3; i++){
            if(segStart+i > input.size())
                return;
            string tmp = input.substr(segStart, i);
            if(STR2INT(tmp) <= 255 && StartWithNonZero(tmp)){
                cand.push_back(tmp);
                _restoreIpAddresses(segStart+i, segCnt+1, input, cand, ans);
                //remember to pop out the candidate
                cand.pop_back();
            }
        }
    }
};
