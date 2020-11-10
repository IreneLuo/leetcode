class Solution {
    /* Solution: greedy method
     *  We calculate the number of valid intervals by comparing
     *  the former's end and the latter's start. So the number of intervals
     *  that we have to remove = total - the number of valid intervals.
     *
     *  ex: (1,3)
     *         (2,5)        --> 3 > 2 --> overlapped
     *               (6,7)  --> 5 < 6 --> non-overlapped
     *      So the answer is 1 = 3 - 2((1,3) & (6,7) are valid)
     *  time complexity = O(nlogn) //sorting
     *  space complexity = O(1)
     *  
     *  Note that if we don't define myCompare() as static, an error will occur:
     *  error: reference to non-static member function must be called
     *  what the difference between:
     *         function pointer/member function pointer/static member function pointer?
     */
    
public:
    static bool myCompare(vector<int> a, vector<int> b){
        return a[1] < b[1];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(intervals.size() <= 1)
            return 0;

        sort(intervals.begin(), intervals.end(), myCompare);
        int endOfLastInterval = intervals[0][1];
        int cntOfValidInterval = 1;
        
        for(int i = 1; i < intervals.size(); i++){
            int start = intervals[i][0];
            int end = intervals[i][1];
            if(start >= endOfLastInterval){
                endOfLastInterval = end;
                cntOfValidInterval++;
            }
        }
        return intervals.size() - cntOfValidInterval;
    }
};
