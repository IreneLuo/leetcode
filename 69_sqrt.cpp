class Solution {
public:
    /* binary search
     * time complexity: O(logn)
     */
    int mySqrt(int x) {
        int left = 1;
        int right = x;
        int middle;
        int ans;

        if(x == 1 || x == 0)
            return x;

        // do not use left < right, it will get a wrong answer
        while(left <= right){
            middle = left + (right - left) / 2;
            // How to avoid signed integer overflow problem if x is INT_MAX:2147483647?
            // (1) use a long data type to avoid  
            // long middle_square = (long)middle * (long)middle;
            // if(middle_square <= x){
            // (2) instead of multiple, we let x divided by middle
            if(middle <= (x / middle)){
                ans = middle;
                left = middle + 1;
            }else{ //middle * middle > x
                right = middle - 1;
            }
        }
        return ans;
    }
};
