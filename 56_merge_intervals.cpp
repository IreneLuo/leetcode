class Solution {
public:
    /* Solution:
     * Main idea: 
     *  1. Sort the intervals in non-decreasing order by their start times
     *     in order to guarantee that the intervals will start at the smallest start time.
     *  2. How to merge 2 intervals?
     *     For (a1,a2) and (b1,b2), which a1 < b1. Our goal is to find an interval= (start, end)
     *     Since a1 < b1-->start = a1.
     *     end = ?
     *     1. if a2 < b1 --> no overlap of these two intervals --> end = a2
     *     2. if a2 >= b1 --> there's an overlap, so we can drop b1
     *           if a2 > b2 --> (b1,b2) is an interval in (a1,a2) --> end = a2
     *           if a2 <= b2 --> end = b2
     *     3. now, we have (start, end)
     *  3. We use the way in step2 and iterate over the intervals to get the answers
     *
     *  time complexity: O(nlogn)
     *  space complexity: O(n)
     */
    
    //to-do: cannot use this function in sort()
    /*
    bool mycompare (vector<int> a, vector<int> b){
        return a[0] < b[0];
    }*/

    struct myclass {
        bool operator() (vector<int> a, vector<int> b) { return a[0] < b[0];}
    } myobject;

    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        if(intervals.size() <= 1)
            return intervals;

        vector<vector<int>> ans;
        // Sort the intervals in non-decreasing order by their start times --> time=O(nlogn)
        sort(intervals.begin(), intervals.end(), myobject);
        // iterate over the intervals and merge them --> time=O(n)
        // we use current to store a temp interval while comparing
        // ex: [[1,3],[2,6],[8,10],[15,18]]
        // current = [1,3] (a1=1, a2=3)
        vector<int> current = intervals[0];
        for(int i = 1; i < intervals.size(); i++){
            int start = intervals[i][0];
            int end = intervals[i][1];
            // a2 < start --> there's no overlap between (a1, a2) and (b1, b2)
            if(current[1] < start){
                ans.push_back(current);
                current = intervals[i];
            // a2 >= start --> there's an overlap between (a1, a2) and (b1, b2)
            // so compare a2 and end
            }else{ 
               current[1] = max(current[1], end);
            }
        }
        //remember to store the last current
        ans.push_back(current);
        return ans;
    }
};
