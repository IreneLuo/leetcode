class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
#if 0
        /* solution 1: 2-D dp
         * time complexity = O(n^2)
         * space complexity = O(n^2)
         * 
         * dp[i][j] = max distance at stations[i] with j stops
         *          = max(if stations[i] is j-th stop, if stations[i] is not j-th stop)
         *          = max(stations[i][1] + dp[i-1][j-1], dp[i-1][j])
         *                  |                               |-> max distance at stations[i-1] 
         *                  |                                   with j stops
         *                  |-> liters of gas at stations[i] + max distance at stations[i-1]
         *                      with j-1 stops
         * Note that we still need to consider:
         *      "can we reach the ith stations from (i-1)th station?"
         * so we check this before calculating dp[i][j]
         * Example: target=100, startFuel=50, stations=[[25,25], [50, 50]]
         *     stops   0  1  2
         *  stations----------- 
         *         0  50  x  x    --> start position cannot pass through any stop, so put
         * [25,25] 1  50 75  x        INT_MIN into those x position
         * [50, 50]2  50 100 125
         *               (1) (2)
         *  (1) dp[2,1] = max(dp[1,0]+st[1][1], dp[1,1]) = max(50+50, 75)=100
         *       - if station 2 is the stop, gas of station2 + station 1 with 0 stop
         *       - if station 2 isn't the stop, station 1 must be the stop
         *  (2) dp[2,2] = max(dp[1,1] + st[1][1], dp[1,2]) = max(75+50, INT_MIN)=125
         *       - if station 2 is the second stop, gas of station2 + station 1 with 1 stop
         *       - if station 2 is not the second stop, station 1 must pass through 2 stops
         *         however, it's impossible for station 1 to pass 2 stops, so we put INT_MIN.
         *   we choose the smallest amount of stops = 1#
         */
        if(startFuel >= target)
            return 0;
        int n = stations.size();
        vector<vector<long>> dp(n+1, vector<long>(n+1, INT_MIN));
        dp[0][0] = startFuel;
        int ans = INT_MAX;
        //iterate over the stations
        for(int i = 1; i < n+1; i++){
            //if we've passed j stops so far when we reach station i
            for(int j = 0; j <=i ; j++){
                if(i-1 >= 0 && j-1 >= 0 && dp[i-1][j-1] >= stations[i-1][0])
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1] + stations[i-1][1]);
                if(i-1 >= 0 && j >= 0 && dp[i-1][j] >= stations[i-1][0])
                    dp[i][j] = max(dp[i][j], dp[i-1][j]);
                if(dp[i][j] >= target)
                    ans = min(ans, j);
            }
        }
        return ans == INT_MAX ? -1 : ans;
#endif
        /* solution 2: 1-D dp
         * time complexity = O(n^2)
         * space complexity = O(n)
         *
         * Inorder to save more space, we let j in reverse order
         * and update the dp table from j=i to j=1
         *
         * Example: target=100, startFuel=50, stations=[[25,25], [50, 50]]
         *  stops(j)   0  1  2
         *         i ------------- 
         *            50 50 50    (i=1, j=1)
         * [25,25] 1  50 75 50    dp[1] = max(50, 50+25)
         * [50, 50]2  50 100 125  (i=2, j=2) --> if station 2 is the 2nd stop
         *                        dp[2] = max(50, 75+50)
         *                        (i=2, j=1)--> if station 2 is the first stop
         *                        dp[1] = max(75, 50+50)
         * At the end, dp[] = [50, 100, 125]
         *
         */
#if 0
        if(startFuel >= target)
            return 0;
        int n = stations.size();
        vector<long> dp(n+1, startFuel);
        int ans = INT_MAX;
        for(int i = 1; i < n+1; i++){
            for(int j = i; j >= 1; j--){
                if(dp[j-1] >= stations[i-1][0])
                    dp[j] = max(dp[j], dp[j-1] + stations[i-1][1]);
                if(dp[j] >= target)
                    ans = min(ans, j);
            }
        }
        return ans == INT_MAX ? -1 : ans;
#endif
        /* solution 3: max-heap
         * time complexity = O(nlogn)
         * space complexity = O(n) //items in queue
         *
         * 1. Use curr_distance to record "How far we've already been?'"
         * 2. Save all the stations that we passed by into the max-Heap
         * 3. While we cannot reach the next station,
         *     - we pick a station that has the largest amount of fuel and go to that station
         *     - after refueling, recalculate the distance we can reach, go to 2
         *
         * Example: target=100, startFuel=50, stations=[[25,25], [50, 50]]
         *           |---------|----------|-------------------|
         * station   0         25         50                 100
         *   fuel             +25        +50
         * curr dis  |--------------------|  (1) curr dis >= station 1's distance,
         * maxHeap   25                          --> push the fuel to the heap
         *
         * curr dis  |--------------------|  (2) curr dis >= station 2's distance,
         * maxHeap   25 50                       --> push the fuel to the heap
         *
         * curr dis  |--------------------|--------------------| (3) we passed by all stations
         * maxHeap   25                          --> we choose station 2 and go back to
         *                                           station 2 to refuel the gas 50+50
         *                                           now our curr dis == target
         *
         * Reference: HuaHua's video
         */
#if 1
        priority_queue<int> pq;
        int curr_distance = startFuel;
        int stops = 0;
        int i = 0;
        while(true){
            if(curr_distance >= target) return stops;
            while(i < stations.size() && curr_distance >= stations[i][0])
                pq.push(stations[i++][1]);
            if(pq.empty()) break;
            curr_distance += pq.top();
            pq.pop();
            ++stops;
        }
        return -1;
#endif
    }
};
