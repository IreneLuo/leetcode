class Solution {
    /* solution: binary search
     * similar: 34. find first and last position in sorted array
     * time complexity: O(logn)
     * space complexity: O(1)
     *
     * solution: Brute-Force
     * Use a for loop to check each character is bigger than target or not.
     * However, (worst case) if target > letters[n], then it will cost O(n)
     * time complexity : O(n)
     * space complexity: O(1)
     */
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int left = 0; 
        int right = letters.size();
        while(left < right){
            int mid = left + (right - left) / 2;
            if(target < letters[mid]){
                right = mid;
            }else{
                left = mid+1;
            }
        }
        //if target is bigger than letters[n], left = letters' size
        //so we have to wrap around it.
        left = (left % letters.size());
        return letters[left];
    }
};
