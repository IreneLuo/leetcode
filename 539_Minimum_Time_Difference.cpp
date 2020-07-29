class Solution {
public:
/* Solution:
 * We create a bitset<1440> to store the status of each timepoint.
 * Each timepoint reprensents an index of this bitset. It just like
 * we've already sorted them in an array.
 * Then we just calculate the interval of each item and get the minimum.
 * ex: 00:00 = 0 min    --> bitset[0]=true
 *     23:59 = 1439 min --> bitset[1439]=true
 *     14:58 = 898 min  --> bitset[898]=true
 *  
 *                    diff=1
 *      v-------------------------------|
 *     [0] --------- [898] --------- [1439]
 *          diff=898       diff=541   
 *
 *     --> min diff = 1
 */
#define time_calculate(x) (stoi(x[i].substr(0, 2)) * 60 + stoi(x[i].substr(3,2)))
#define MAX_MINS_PER_DAY  (24 * 60)

    int findMinDifference(vector<string>& timePoints) {
        bitset<MAX_MINS_PER_DAY> bit_time;

        for (int i = 0; i < timePoints.size(); i++){
            int time = time_calculate(timePoints);
            // if bit_time[time] is true, it means this item has already existed
            // so the smallerest difference will be zero
            if (bit_time[time])
                return 0;
            else
                bit_time[time] = true;
        }
        
        // maximum difference will be 00:01 ~ 12:01 = 12hr = 720mins;
        int min_diff = 12 * 60;
        int prev = -1;
        int start = -1;
        for (int i = 0; i < MAX_MINS_PER_DAY; i++){
            if (bit_time[i]){
                if (start < 0)
                    start = i;
                else
                    min_diff = min(min_diff, i - prev);
                prev = i;
            }         
        }
        // wrap-around check (last one - first one)
        return min(min_diff, start + (24 * 60) - prev);
    }
};
