class Solution {
public:
    /* solution: dynamic programming
     * time complexity = O(n)
     * space complexity = O(n)
     * For optimization (space to O(1)) see HuaHua's video
     * 
     * Let's find out the pattern first.
     * For example: {1,2,3,4,5}
     *   end at n[i]   odd#                     even#
     *      {1}        1   {1}                   0
     *     {..2}       1   {1,2}                 1  {2}    
     *    {....3}      2   {2,3},{3}             1  {1,2,3}
     *   {......4}     2   {2,3,4}{3,4}          2  {1,2,3,4}{4}
     *  {........5}    3   {1,2,3,4,5}{4,5}{5}   2  {2,3,4,5}{3,4,5}
     *
     *  odd#(i) = numbers of odd sum when subarrays ends at n[i]
     *  even#(i)= numbers of even sum when subarrays ends at n[i]
     *  When subarray ends at n[i].
     *  If n[i] is odd,
     *     - odd#(i) = even#(i-1) + 1 (odd + even = odd and 1 is n[i] itseof)
     *     - even#(i) = odd#(i-1)     (odd + odd = even)
     *  If n[i] is even,
     *     - odd#(i) = odd#(i-1)
     *     - even#(i) = even#(i-1) + 1
     *
     *  so for implementation, we can create an 2D array
     *  and calculate the odd# and even# for each subarrays that ends at n[i]
     */
enum{
    ODD,
    EVEN,
    TYPE
};
    int numOfSubarrays(vector<int>& arr) {
        constexpr int mod = 1e9+7;//pow(10, 9) + 7;
        const int num_size = arr.size();
        vector<vector<int>> dp(num_size, vector<int>(TYPE));
        dp[0][ODD] = (arr[0] & 1) ? 1 : 0;
        dp[0][EVEN] = (arr[0] & 1) ? 0 : 1;
        long sum = dp[0][ODD];
        for(int i = 1; i < num_size; i++){
            if(arr[i] & 1){
                dp[i][ODD] = dp[i-1][EVEN] + 1;
                dp[i][EVEN] = dp[i-1][ODD];
            }else{
                dp[i][ODD] = dp[i-1][ODD];
                dp[i][EVEN] = dp[i-1][EVEN] + 1; 
            }
            sum  += dp[i][ODD];
        }
        return sum % mod;
    }
    /* if the problem doesn't ask for sub-arrays, we can use this
     * method to calculate all the possible sums by adding items in
     * the input array without ordering limitations.
     * call add_target(0, 0, count, arr) in the main function
     */
    /*
    void add_target(int target, int sum, int& count, vector<int>& arr){
        if(target == arr.size()){
            if(sum % 2 == 1){
                count++;
            }
            return;
        }
        //if we don't choose target, pass the sum into the function
        add_target(target + 1, sum, count, arr);
        //if we choose target, add it to the sum then pass it
        add_target(target + 1, sum + arr[target], count, arr);
    }
    */
};
