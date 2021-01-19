class Solution {
    /* solution: recursion
     * Main idea:
     *   - Calculate the number of parentheses to check if the string is balanced or not.
     *   - if string[i] = (, counter ++
     *   - if string[i] = ), counter --
     *   - when counter == 0, it means the string is balanced
     * case 1: ()
     *    - if string len = 2, return 1
     * case 2: (A) the whole string is balanced
     *    - return 2 * A
     * case 3: (A)(B)(C) substring is balanced
     *    - return A + B + C
     * time complexity = O(n) ~ O(n^2)
     *    - best case: ()()()()...()
     *      read a pair of () then enter into the next recursive call.
     *      total n/2 recursive calls
     *      ==> O(n/2) = O(n)
     *    - worst case: (((((((...)))))))
     *      1st for loop: n (we need to calculate the counter by traversing whole string)
     *      2nd for loop: n-2
     *      3rd for loop: n-4
     *      total n/2 recursive calls
     *      ==> O(n* n/2) = O(n^2)
     * space complexity = O(n) //function calls' stack size
     * 
     * ex: score("(()(()))")
     *     = 2 * score("()(())")
     *     = 2 * (score("()") + score("(())")
     *     = 2 * (1 + 2 * score("()"))
     *     = 2 * (1 + 2 * 1)
     *     = 6
     * For an improved solution: see huahua's video
     */
public:
    int scoreOfParentheses(string S) {
       return score(S, 0, S.length()-1);      
    }
    int score(string& str, int left, int right){
        //case 1: string = ()
        if((right - left) == 1) return 1;
        int balance = 0;
        //case 3: string = ()()
        //if it's balance before the last ")",
        //split the string into two sub-strings
        //note that i won't equals to the right
        for(int i = left; i < right; i++){
            if(str[i] == '(') balance++;
            if(str[i] == ')') balance--;
            if(balance == 0){
                return score(str, left, i) + score(str, i+1, right);
            }
        }
        //case 2: string = (())
        return 2 * score(str, left+1, right-1);
    }
};
