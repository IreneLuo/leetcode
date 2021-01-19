class Solution {
    /* solution: simulation/queue/greedy
     * The problem can reduce to:
     *   Can we transform the string S to the string T by
     *   moving smaller digits to the left?
     * Method:
     *  1. simulation:
     *  For each character c in T, move c in S to the left most
     *  Ex:     S         T
     *        84532     34852
     *        3 8452    ^        move 3 in S to the left most
     *        34 852     ^       move 4 in S to the left most
     *  time complexity = O(n^2)
     *     - like bubble sort, move n items n times
     *  However, we don't have to move them acutally.
     *  2. queue/greedy
     *  We can check if there's any digit in S before c smaller than c.
     *  If a digit before c in S is smaller than c, then we cannot move
     *  c to the left most.
     *   - 10 queues for digit 0-9 to save the indices of each digits in S
     *   Ex: 84556
     *      q  idx  q  idx
     *      q0: -   q5: 2,3
     *      ...     q6: 4
     *      q4: 1   q8: 0
     *
     *  time complexity = O(n)
     *  space complexity = O(n)
     *
     */
public:
    bool isTransformable(string s, string t) {
        vector<queue<int>> index(10);
        //save the indices of digits in S in the queue0 - queue9
        for(int i = 0; i < s.length(); i++){
            int target = s[i] - '0';
            index[target].push(i);
        }
        //check each character in t
        for(int i = 0; i < t.length(); i++){
            int d = t[i] - '0';
            //if cannot find the index of d in s, return false
            if(index[d].empty()) return false;
            //check the first indices of digit 0 to (d-1) 
            //if any one's index < d's index, return false (cannot sort)
            for(int cand = 0; cand < d; cand++){
                if(!index[cand].empty() && index[cand].front() < index[d].front())
                    return false;
            }
            index[d].pop();
        }
        return true;
    }
};
