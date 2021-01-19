class Solution {
    /* Solution: dp + bottom up
     * We use an array min_path[] to save min_path, and collect the answer
     * from bottom to the top
     *  - min_path[i]: a min path from bottom to current level of element i
     * 
     *    i   we sotre j, k in the min_path
     *   / \  so i can choose a the smaller one(ex: j)
     *  j   k and get a new min_path = j + i
     *
     * Example: [[-1],[2,3],[1,-1,-3]]
     *      triangle      min_path[3]
     *         -1         -1           --> 3.min_path[0] = min(1,0) + -1 = -1
     *        2  3         1  0        --> 2.min_path[0] = min(1,-1) + 2 = 1
     *      1 -1 -3        1 -1 -3     -->   min_path[1] = min(-1,-3)+ 3 = 0
     *                                 --> 1.initialize to triangle[bottom]
     * time complexity = O(n)
     * space complexity = O(n)
     */
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int height = triangle.size();
        //initialize the elements in min_path to values in the bottom triangle
        int min_path[height];
        for(int i = 0; i < height; i++)
            min_path[i] = triangle[height-1][i];
        //start at the level (height - 2)
        //since we've already put the bottom level(height-1) into min_path
        for(int i = height - 2; i >= 0; i--){
            for(int j = 0; j <= i; j++){
                //get the smallest path in the next level(left or right)
                int min_child = min(min_path[j], min_path[j+1]);
                //update min_path from bottom level to current level
                min_path[j] = min_child + triangle[i][j];
            }
        }
        return min_path[0];
    }
};
