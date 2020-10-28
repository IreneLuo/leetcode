class Solution {
public:
    /* solution: use boundery check
     * check if rec1 is higher/lower/to the left/to the right of rec2
     * if yes, then two rectangle don't overlap
     *
     */
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        
        bool ans = true;
        // 1. see if rec1 is higher than rec2 (use the lowest x in rec1 and the highest X in rec2)
        if(rec1[1] >= rec2[3])
            ans = false;
        // 2. see if rec1 is lower than rec1
        else if(rec1[3] <= rec2[1])
            ans = false;
        // 3. see if rec1 is to the left of rec2
        else if(rec1[2] <= rec2[0])
            ans = false;
        // 4. see if rec1 is to the right of rec1
        else if(rec1[0] >= rec2[2])
            ans = false;

        return ans;
    }
};
