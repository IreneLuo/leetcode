class Solution {
public:
    /* solution: linear search
     * 1. set ptr_a points to nums1, ptr_b points to nums2
     * 2. compare the value that both pointers points to.
     * 3. if value(ptr_a) == value(ptr_b), insert the value to the map
     *    if value(ptr_a) < value(ptr_b), ptr_a++ (since increase the ptr_a might find a value that equals to ptr_b)
     *    if value(ptr_a) > value(ptr_b), ptr_b++
     * 4. keep comparing until ptr_a or ptr_b meets the end of vector
     * Note) How can we ensure that the values won't repeat?
     * 1. use a map<key, value>, like a hash table
     * 2. use a temp value to record previous value that we put into the answer list
     * Note) other ways? (not including sorting the inputs)
     * 1. Brute Force: O(m*n)
     * 2. Binary Search: O(min(m,n)log(max(m,n)))
     *    ex: if n < m then O(nlogm)
     *        we use the input which is the longer one as a binary tree
     *        and traverse the input which is the shorter one.
     *        Search each item in n, check if it exists in the binary tree of m
     */
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {

        int ptr_a = 0;
        int ptr_b = 0;
        int prev_match;
        vector<int> ans;

        if(nums1.size() == 0 || nums2.size() == 0)
            return ans;
        
        // sort the vector first
        // time complexity: O(nlogn)
        // http://www.cplusplus.com/reference/algorithm/sort/?kw=sort
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        // time complexity = O(m+n), which m = nums1.size(), n = nums2.size()
        while(ptr_a < nums1.size() && ptr_b < nums2.size()){
            if(nums1[ptr_a] == nums2[ptr_b]){
                if(ans.size() == 0 || nums1[ptr_a] != prev_match){
                    ans.push_back(nums1[ptr_a]);
                    prev_match = nums1[ptr_a];
                }
                ptr_a++;
                ptr_b++;
            }else if(nums1[ptr_a] < nums2[ptr_b]){
                ptr_a++;
            }else{
                ptr_b++; 
            }
        }
        return ans;
    }
};
