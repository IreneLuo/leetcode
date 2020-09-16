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
        int carry_bit = 0;
        string ans;
        int temp;
        while (idx_a >= 0 || idx_b >= 0) {
            if (idx_a >= 0 && idx_b >= 0) {
                temp = (a[idx_a]-'0') + (b[idx_b]-'0') + carry_bit;
                idx_a--;
                idx_b--;
            } else if (idx_a >= 0) {
                temp = (a[idx_a]-'0') + carry_bit;
                idx_a--;
            } else if (idx_b >= 0){
                temp = (b[idx_b]-'0') + carry_bit;
                idx_b--;
            }                
            ans += to_string(temp % 2);
            carry_bit = temp / 2;

        }
        if (carry_bit)
            ans+=to_string(carry_bit);

        reverse(ans.begin(), ans.end());
        return ans;
        
}
