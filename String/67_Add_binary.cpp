class Solution {
public:

    string addBinary(string a, string b) {
        /* Solution 1:
         * 1. transfer string a, b to int a, b
         * 2. a + b = ans
         * 3. transfer ans from base 10 -> 16 and transfer to string
         * Problem: length(a) and length(b) = 10000 --> a in base10 = 2 ^ 10000
         *          but max data type like int64 only can support 2 ^ 64
         */
        /* Solution 2:
         * 1. from i = length of a/b to 0
         *      set carray_bit = 0
         *      a[i] + b[i] + carry_bit = ans[i], set carry_bit = 1 if necessary
         * 2. add the last carry_bit and reverse ans 
         */
        int idx_a = a.size() - 1;
        int idx_b = b.size() - 1;
        int carry = 0;
        string ans;
        while (idx_a >= 0 || idx_b >= 0) {
            if (idx_a >= 0) {
                carry += (a[idx_a]-'0');
                idx_a--;
            }
            if (idx_b >= 0){
                carry += (b[idx_b]-'0');
                idx_b--;
            }                
            ans += to_string(carry % 2);
            carry /= 2;

        }
        if (carry)
            ans+=to_string(carry);

        reverse(ans.begin(), ans.end());
        return ans;
        
    }
};
