class Solution {
public:
    /* solution:
     * choice: yes / no for each digit
     * goal: index == length of the input
     * method: 
     * We choose yes or no (if yes, we push the digit)
     * then go to the next digit by calling a recursive function
     * 
     * time complexity = O(2^n)
     * branching factor = 2 (choice for yes or no)
     * depth of recursive calls = n (goal is to go through every digit in the input)
     * (another expression: T(n)<=2T(n-1)+O(1))
     * space complexity = O(n) (to store the candidate answer temporarily)
     *
     * See HuaHua's video for another solution
     */
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        _subsets(0, {}, nums, ans);
        return ans;
    }
    void _subsets(int index, vector<int> cand, vector<int>& input,  vector<vector<int>>& ans){
        // when index == input's size, push back cand because we've already go through the input
        if(index == input.size()){
            ans.push_back(cand);
            return;
        }
        cand.push_back(input[index]); //choice: if we choose input[index]
        _subsets(index+1, cand, input, ans); // go to the next digit
        cand.pop_back(); //choice: if we don't choose input[index]
        _subsets(index+1, cand, input, ans); // go to the next digit
    }
};
