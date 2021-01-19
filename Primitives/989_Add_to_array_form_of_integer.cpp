/* solution:
 * Add K with A[biggest idx] and move leftward to add others digits
 * time complexity = O(max(N, logk))
 * space complexity = O(max(N, logk))
 * Example: [1,2,3] + 912 
 *    step 1: [1,2,3+912] carry = 915, we leave 5 so carry = 91
 *         2: [1,2+91, 5] carry = 93, we leave 3, so carry = 9
 *         3: [1+9, 3, 5] carry = 10, we leave 0, so carry = 1
 *         4  [1,0,3,5] finished
 * 
 */
class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        int len = A.size();
        int carry = K;
        int i = len;
        vector<int> ans;
        while(--i >= 0 || carry > 0){
            if(i >= 0) carry += A[i];
            ans.push_back(carry % 10);
            carry /= 10;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
