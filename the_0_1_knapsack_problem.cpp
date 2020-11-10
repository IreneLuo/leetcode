/* solution:Bottom-up
 * For top-down method, see the solution.
 * We use a table to calculate the max value for different weight
 * ex:
 *           weight  0  1  2  3  4  5  6
 *           value ----------------------
 *             0(0)| 0  0  0  0  0  0  0 --> we don't have any value, so we don't have any weight
 *           +60(2)| 0  0 60 60 60 60  60
 *           +50(3)| 0  0 60 60 60 110 110
 *           +70(4)| 0  0 60 60 70 110 130
 *           +30(5)| 0  0 60 60 70 110 130 --> (1)
 *           ==> the max value = 130 = 60+70 and weight = 6
 *           (1) = max(value with 30, value without 30)
 *               = max(30 + tbl[row-1][6-5], tbl[row-1][6])
 *               = max(30, 130)
 *               for the value with 30: we add 30, and now the weight = 6-5=1
 *               so we look up the table to find out the max value for weight 1 and do not exclude 30
 */
class Solution {
  public:
    int knapsack(vector<int>& values, vector<int>& weights, int maxWeightConstraint) {
      int itemCount = values.size();
      int tbl[itemCount+1][maxWeightConstraint+1];
      //for the first row and first column in tbl is 0 value and 0 weight
      for(int row = 0; row <= itemCount; row++){
        for(int weight = 0; weight <= maxWeightConstraint; weight++){
          //we have to -1 to get the real idx of this item in vector values and weights
          int idxOfItem = row - 1;
          if(row == 0 || weight == 0){
            tbl[row][weight] = 0;
          }else if(weights[idxOfItem] > weight){
            tbl[row][weight] = tbl[row-1][weight];
          }else{
            int withItem = values[idxOfItem] + tbl[row-1][weight-weights[idxOfItem]];
            int withoutItem = tbl[row-1][weight];
            tbl[row][weight] = max(withItem, withoutItem);
          }
        }
      }
      return tbl[itemCount][maxWeightConstraint];
    }
};
