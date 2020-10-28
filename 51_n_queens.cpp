class Solution {
public:
    /*  
     * choice: each row has 1 Q, Q can put at position 1-n
     * constraints: row/col/diagonally
     * goal: row = n
     * time complexity: O(n^n) --> not sure
     * space complexity: O(n)
     */
    vector<string> transfer(vector<int> raw, int n){
        vector<string> ans;
        string s = "";
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(raw[i] == j)
                    s+="Q";
                else
                    s+=".";
            }
            ans.push_back(s); 
            s = "";
        }
        return ans;
    }
    bool isValid(vector<int>& queensPosition){
        int idxOfCandidate = queensPosition.size() - 1;
        int candidate = queensPosition[idxOfCandidate];
        for(int i = 0; i < idxOfCandidate; i++){
            int queen = queensPosition[i];
            int colDistance = abs(candidate - queen);
            int rowDistance = idxOfCandidate - i;
            if(colDistance == 0 || (colDistance == rowDistance))
                return false;
        }
        return true;
    }
    void rowPlacements(int row, int n, vector<int>& queensPosition, vector<vector<string>>& ans){
        if(row == n){
            ans.push_back(transfer(queensPosition, n));
            return;
        }
        // explaination 1 from myself: 
        // time = (n-1) * (n-2) * ...*1 = (n-1)! => O((n-1)!) = O(n^n)

        // explaination 2 from back to back swe = O(n^n)
        // for loop: O(n) because it starts from 0 to n-1 --> total = [(n-1)-0]+1 = n iterations
        // base cases: O(n^n) because we have n^n leaves, and O(1) for recursive case
        //  |--> how many calls we'll make? loosely, the amount of calls: n times
        for(int i = 0; i < n; i++){
            queensPosition.push_back(i);
            if(isValid(queensPosition)){
                rowPlacements(row+1, n, queensPosition, ans);
            }
            queensPosition.pop_back();
        }  
    } 
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<int> queensPosition;
        rowPlacements(0, n, queensPosition,ans);
        return ans;
    }
};
