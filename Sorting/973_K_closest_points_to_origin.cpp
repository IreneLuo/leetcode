class Solution {
    /* solution: sorting
     * 1. Create a vector "distance" to store distance and index of each points
     * 2. Call sort() to sort all the distances
     * 3. Return the previous K points
     *
     *  P.S) for sort(), if (a.first < b.first) return true
     *                   if (a.first == b.first && a.second < b.second) return true
     *                   otherwise return false
     *  time complexity = O(nlogn) //sorting
     *  space complexity = O(n)
     *
     *  For a better solution, see HuaHua's video
     *  (must review the concept in this video!)
     */
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<pair<int, int>> distance(points.size());
        for(int i = 0; i < points.size(); i++){
            pair<int, int> p;
            p.first = points[i][0] * points[i][0] + points[i][1] * points[i][1];
            p.second = i;
            distance[i] = p;
        }
        vector<vector<int>> ans(K);
        sort(distance.begin(), distance.end());
        for(int i = 0; i < K; i++)
            ans[i] = points[distance[i].second];
        return ans;
    }
};
