class Solution {
public:
    /* solution: recursion
     * 1. We try all the possible ways to choose the integers(x),
     * and deduce the total by x, and use a new total to the next iteration
     * to choose another integer until the total <= 0. The one who let total<=0
     * is the winner.
     * 2. For example, if total = 4, max = 3 --> we can choose 1 2 3
     * then we can try (1,2,3) (1,3,2) (2,1,3)(2,3,1)(3,1,2)(3,2,1)
     * this will take O(3!) (like a permutation)
     * However, the order of choosing integers is not important
     * the result of choosing sequence (1,2,x) is as same as (2,1,x)
     * so we can use a history table to record the path that we've been visited before.
     * And now the problem turns into a combination problem
     * so it only takes O(2^3) = O(2^N) if n numbers to choose
     * 
     * For each iteration:
     * choice:
     *    choose an integer X from 1~N 
     *    total = total - X
     * constraints:
     *    X cannot be choosed before
     * goal:
     *    1. total <= 0
     * or 2. history[path] has value
     *
     * time complexity = O(2^N)
     *     // we can choose numbers from 1 to N
     * space complexity = O(N)
     *     //the depth of the tree is the amount of numbers that we can chosoe
     *
     *                    restut: [0000]=-1, return false
     *                                   4{}
     *                   |----------------|-----------------|
     *  A               3{1}             2{2}              1{3}
     *              |---------|t      |--------|t     t|--------|t          
     *  B          1{12}    0{13}    1{12}    -1{23}  -1{23}   0{31}
     *              |t        |        |t      |       |        |
     *  A        -2{123}      f     -2{123}    f       f        f
     *              |                  |
     *  B           f                  f
     *           [0111]=1  [0101]=1  [0111]=1 [0110]=1
     *
     *  Since the problem says "Assume both players play optimally."
     *  so B can always choose a best answer to win the game
     *  ==> A cannot win
     *  
     */
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        //if sum < desiredTotal, A won't win since even A choose maxChoosableInteger is
        //less than disiredTotal
        int sum = (1 + maxChoosableInteger) * maxChoosableInteger / 2;
        if(sum < desiredTotal) return false;
        //if desiredTtoal <= 0, A will win if A choose zero or any integer
        if(desiredTotal <= 0) return true;
        //each digit represent a number
        //[0x0111] = the path that has integer 1,2 and 3 
        history = vector<char>(1<<maxChoosableInteger, 0);
        return _canIWin(maxChoosableInteger, desiredTotal, 0);
    }
private:
    //0:init, -1:cannot win, 1:can win
    //[0111] = 1 : with the path 123 or 132 or 321... can win the game
    vector<char> history;
    bool _canIWin(int candidate, int goal, int state){
        if(goal <= 0) return false;
        if(history[state]) return history[state] == 1;
        for(int i = 1; i <= candidate; i++){
            //if the integer has been choosed, we cannot choose it this time
            if(state & (1 <<(i-1))) continue;
            //update the new state with the integer that we just select
            int new_state = state | 1 << (i-1);
            //if you cannot win the game, I win
            if(!_canIWin(candidate, goal-i, new_state)){
                history[state] = 1;
                return true;
            }
        }
        //if you win, I lose the game
        history[state] = -1;
        return false;
    }
};
