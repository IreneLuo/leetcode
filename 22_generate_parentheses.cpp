class Solution {
public:
    /* solution: recursive calls
     * choice: place "(" or ")"
     * constraints: we cannot close until we have the open--> the count of open matters
     * goal:n*2 placements
     * Method:
     * Note that we use leftCount and rightCount to notify the number of left/right parenthesis remains
     * 1. if leftCount > 0, push ( into str, do a recursive call
     * 2. if leftCount < rightCount, push ) into str, do a recursive call (it means that str[the back] is "(")
     * 3. if both leftCount and rightCount are zero, push str into the answer
     *
     * time complexity = see the solution
     * space complexity = O(n*2) = O(n)
     *
     * ex: n = 3 --> leftCount, rightCount = (3, 3)
     *                   [3,3]""
     *                   /   
     *                [2,3]"("
     *                /      \
     *       [1,3]"(("       "()"[2,2]
     *       /       \             / \
     *   [0,3]"(((" "(()"[1,2]   ... ...
     *     |             |   \
     *   [0,2]"((()"   [0,2] [1,1]
     *     |             |     |
     *   [0,1]"((())"  [0,1] [0,1]
     *     |             |     |
     *   [0,0]"((()))" [0,0] [0,0]
     */
    void chooseOneSymbol(int leftCount, int rightCount, string s, vector<string>& ans){
        if(leftCount == 0 && rightCount == 0){
            ans.push_back(s);
            return;
        }
        if(leftCount > 0){
            chooseOneSymbol(leftCount-1, rightCount, s+"(", ans);
        }
        if(leftCount < rightCount){
            chooseOneSymbol(leftCount, rightCount-1, s+")", ans);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        chooseOneSymbol(n, n, "", ans);
        return ans;
    }
};
