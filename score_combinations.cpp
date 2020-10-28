class Solution {
  public:
    /*  solution:
     *  we use a two-dimentional table to save our history value
     *  table like this
     *      score | 0  1  2  ... 12
     *    nums[i] |----------------
     *          {}| 0  0  0  ... 0  --> 1. an empty number cannot sum up to any score, so we set this row to 0 
     *         [2]| 1
     *       2,[3]| 1            a
     *    2,3,[7] | 1     b  ... X
     *              |-----------------> 2. who can combine to the score 0? only the empty, so we set this column to 1
     *    after step 1 and 2, we can now calculate the value in each position.
     *    The method is: X = with[num] + without [num] = a + b
     *        X = how many ways can we combines to score[col]
     *        a = if we don't choose [nums], how many ways can we combines to score[col]
     *            a can be accessed by row-1
     *        b = if we choose [nums], how many ways can we combines to score[col]
     *            b can be accessed by col-[nums]
     *            since col indicates to score, score - nums = scoreleft
     *            so now we need to know how many ways can we combines to scoreleft.
     *            Fortunately, the answer has already existed in the table
     */
    int totalWaysToReachScore(int finalScore, vector<int>& pointEvents) {
        vector<vector<int>> waysCache;
        for(int row = 0; row <= pointEvents.size(); row++){
                vector<int> rawdata(finalScore+1, 0);
                waysCache.push_back(rawdata);
        }
        for(int row = 1; row <= pointEvents.size(); row++)
            waysCache[row][0] = 1;
        for(int i = 1; i <= pointEvents.size(); i++){
            int num = pointEvents[i - 1];
            for(int t = 1; t <= finalScore; t++){
                int withoutNum = waysCache[i-1][t];
                int withNum = 0;
                if(t >= num){
                    withNum = waysCache[i][t-num];
                }
                waysCache[i][t] = withoutNum + withNum;
            }
        }
        return waysCache[pointEvents.size()][finalScore];
    }
};
