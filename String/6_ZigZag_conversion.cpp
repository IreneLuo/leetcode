class Solution {
public:
    string convert(string s, int numRows) {
        /* Solution 1:
         * 1. start from s[0], put each character into input by increasing index
         * 2. when index = numRows - 1 or 0, change the direction
         * 3. after traversing s, combine the answer into a string and return
         * Time complexity  = O(max(n, numRows))
         * Space complexity = O(max(n, numRows))
         */
        
        // use a two-dimensional vector to store the character.
        // input = 
        // [string 0]
        // [string 1]
        // [string 2]
        // ...
        // [string N]
        vector<vector<string>> input(numRows, vector<string>(1, ""));
        int row = 0;
        // true: increasing idx, false: decreasing idx
        bool direction = true;
        string ans="";

        // traverse each character in s and put into the vector input
        // time complexity = O(n)
        for (int i = 0; i < s.size(); i++) {
            // 1. cannot use input[][].push_back() without vector initialization
            // 2. cannot push back s[i] into vector because data type mismatch.
            //    s[i]=char, vector element=string --> use substr can get a part of the string
            input[row][0] += s.substr(i, 1);

            if (row == 0)
                direction = true;
            if (row == (numRows - 1))
                direction = false;

            if (direction && numRows > 1)
                row+=1; //increasing idx
            else if (!direction && numRows > 1)
                row-=1; //decreasing idx
            else
                row = 0;// if numRows=0
            
        }
        // concat the elements in input into the answer
        // time complexity = O(numRows)
        for (int i = 0; i < numRows; i++)
            ans = ans+ input[i][0];

        return ans;
    }
};
