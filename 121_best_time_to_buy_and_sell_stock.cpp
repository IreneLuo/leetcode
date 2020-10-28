class Solution {
public:
    /* solution 1: 
     * we iterate the input, and everytime we check:
     *  1. the difference between current item with min and remains the maximum difference (i.e max profit)
     *  2. if current item < min, replace the min
     *  so instead of using 2 for loop, we only check the (current-min) to get the max profit
     * time complexity = O(n)
     * space complexity = O(1)
     */
    int maxProfit(vector<int>& prices) {

      if(prices.size() == 0)
          return 0;
      int min = prices[0];
      int max_profit = 0;
      for(int i = 0; i < prices.size(); i++){
        if(prices[i] > min){
          int diff = prices[i] - min;
          max_profit = (diff > max_profit) ? diff : max_profit;
        }else if(prices[i] < min){
          min = prices[i];
        }
      }
      return max_profit;

        
    /* solution 2: recursive calls
     *  time compelxity = O(n)
     *  space complexity = O(n)
     *  
     *  everytime we consider two things:
     *   1. if we buy the stock yesterday, we can earn: yesterday's profit + (today price - yesterday price)
     *   2. if we just buy it today, we can earn 0
     *  the max of 1 and 2 is day ith's profit
     *  after we traverse over the input, we can find the max profit
     *   
     */
        /*
        if(prices.size() == 0)
          return 0;
        int maxProfit = 0;
        getDayiProfit(prices, 1, 0, maxProfit);
        return maxProfit;
        */
    }
    /*
    void getDayiProfit(vector<int>& prices, int day, int yesterdayProfit, int& maxProfit){
        if(day == prices.size())
            return;
        int todayProfit = max(0, yesterdayProfit+(prices[day]-prices[day-1]));
        maxProfit = max(maxProfit, todayProfit);
        getDayiProfit(prices, day+1, todayProfit, maxProfit);
    }
    */
};
