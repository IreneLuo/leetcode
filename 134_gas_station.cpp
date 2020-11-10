class Solution {
    /* solution: greedy algorithm
     * Try each station as a start station until we find a valid start station
     * that the gas in that station can suppor the cost of our car to reach the next station
     *
     * time complexity = O(n)
     * space complexity = O(1)
     */
public:
    int get_sum(vector<int>& v){
        int ans = 0;
        for(auto it: v)
            ans+=it;
        return ans;
    }
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // check if there's any possible path.
        // if the amount of total gas isn't enough to the cost, then there's no any possible answer
        if(get_sum(gas) < get_sum(cost))
            return -1;

        //heuristic method: explore and learn in each iteration
        //find a start station that the gas is enough to reach the next station
        int gas_in_my_car = 0;
        int station = 0;
        for(int i = 0; i < gas.size(); i++){
            //calculate the gas in my car when I reach the next station
            gas_in_my_car = gas_in_my_car + gas[i] - cost[i];
            //if gas in my car will be negative, then this station cannot be the start
            //so reset the get_in_my_car and try the next station as the start
            if(gas_in_my_car < 0){
                gas_in_my_car = 0;
                station = i + 1;
            }
        }
        return station;
    }
};
