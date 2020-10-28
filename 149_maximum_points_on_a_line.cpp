struct POINT_STA{
    int maxCountSoFar;
    int dupSoFar;
    int horizontalSoFar;
    int verticalSoFar;
    POINT_STA(int m, int d, int h, int v) : maxCountSoFar(m), dupSoFar(d), horizontalSoFar(h), verticalSoFar(v) {}
};
class Solution {
public:
    /* Solution: using hash table and enumeration
     * 1. We can simplify the problem by searching the maximum number
     *    of points on a line passing through the point i.
     * 2. for each point i, pair i with other points and find the slope, then put the slope and the count
     *    of the number of points into the hash table.
     * 3. Keep comparing the count and save the maximum count until we try all the pairs(with this point i)
     * p.s> How do we deal with the slope? we don't calcuate it, but use string like "deltaY/deltaX" instead
     *    to avoid floating points problems.
     *    Note that we have to deal with the edge cases like
     *    - horizontal points: y1 = y2
     *    - vertical points: x1 = x2
     *    - duplicates points
     *
     * test cases: 
     * [[2,3],[3,3],[-5,3]]
     * [[1,1],[2,2],[3,3]]
     * [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
     * [[0,0],[1,1],[0,0]]
     * [[1,1],[1,1],[1,1]]
     * [[4,0],[4,-1],[4,5]]
     */
    vector<vector<int>> input_points;
    unordered_map<string, int> hashtbl;
    int horizontal = 0;
    int vertical = 0;

    enum POINTSTYPE{
        SAME,
        HORIZONTAL,
        VERTICAL,
        GENERAL,
    };

    int check_points_position(int idxA, int idxB){
        if((input_points[idxB][0] == input_points[idxA][0]) &&
            (input_points[idxB][1] == input_points[idxA][1])){
            return SAME;
        }else if(input_points[idxB][1] == input_points[idxA][1]){
            return HORIZONTAL;
        }else if(input_points[idxB][0] == input_points[idxA][0]){
            return VERTICAL;
        }else{
            return GENERAL;
        }
    }
    /* get the count number in the hashtable and compare with maxCountSoFar, return the bigger one
     * Note that:
     *  1. if point A and point b are the same, then dupSoFar++ (it means that 1 point is as same as point i)
     *  2. if point A and point b are horizontal, then horizontal++ (it means that 1 point is horizon with point i)
     *  3. if point A and point b are vertical, then vertical++
     *  4. otherwise, we get the slope string and find the count number of that slope
     */
    pair<int, int> get_the_count_by_slope(int idxA, int idxB, int maxCountSoFar, int dupSoFar){
        int points_pos = check_points_position(idxA, idxB);
        int deltaX, deltaY;
        if(points_pos == SAME){
            dupSoFar++;
        }else if(points_pos == HORIZONTAL){
            horizontal++;
            maxCountSoFar = max(maxCountSoFar, horizontal);
        }else if(points_pos == VERTICAL){ 
            vertical++;
            maxCountSoFar = max(maxCountSoFar, vertical);
        }else{
            deltaX = input_points[idxB][0] - input_points[idxA][0];
            deltaY = input_points[idxB][1] - input_points[idxA][1];
            int gcd = __gcd(deltaX, deltaY);
            deltaX = deltaX / gcd; // divided by gcd to ensure that deltaX is the minimum value
            deltaY = deltaY / gcd;
            string slope = to_string(deltaY) + "/" + to_string(deltaX); //use "deltaY/deltaY" as a key
            hashtbl[slope] = hashtbl[slope] + 1; //get the count number and increase 1
            maxCountSoFar = max(maxCountSoFar, hashtbl[slope]);
        }         

        return pair<int, int>(maxCountSoFar, dupSoFar);
    }
    /* searching the maximum number of points on a line passing through the point i */
    int search_max_num_of_points_on_this_point(int idxOfPoint){
        // clear all the important factors for a new loop
        int maxCountSoFar = 0;
        int dupSoFar = 0;
        horizontal = 0;
        vertical = 0;
        hashtbl.clear();
        // ex: we have point A, B, C, D, E
        // in this loop, we deal with (A,B), (A, C), (A, D), (A, E)
        for(int i = idxOfPoint + 1; i < input_points.size(); i++){
            pair ret = get_the_count_by_slope(idxOfPoint, i, maxCountSoFar, dupSoFar);
            maxCountSoFar = get<0>(ret);
            dupSoFar = get<1>(ret);
        }
        // add 1 to increase point i itself
        // add dupSoFar with maxCountSoFar because dup points belongs to any slope
        return maxCountSoFar + dupSoFar + 1;
    }
    int maxPoints(vector<vector<int>>& points) {
            if(points.size() < 3){
                return points.size();
            }
            int maxCount = 1; //at least 1 point on a line
            input_points = points;
            for(int i = 0; i < points.size() - 1; i++)
                maxCount = max(search_max_num_of_points_on_this_point(i), maxCount);
            return maxCount;
    }
};
