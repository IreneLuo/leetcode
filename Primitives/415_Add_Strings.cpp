class Solution {
public:
    /* Solution:
     * We can carry out base 10 addition by hand, but remember to add
     * a carry bit.
     * ex: 95 + 7
     *     5+7 = 12 --> carry = 1 , ans = 2
     *     9+ carry = 10 --> carry = 1, ans = 20
     *     append the last carry bit --> ans = 201
     *     then use reverse() to reverse it --> ans = 102
     */
    string addStrings(string num1, string num2) {
        int i = num1.length();
        int j = num2.length();
        int carry = 0;
        string ans;
        while (i > 0 || j > 0){
            int sum = carry;
            if (i > 0)
                sum += (num1[--i] - '0');
            if (j > 0)
                sum += (num2[--j] - '0');
            ans += to_string(sum % 10);
            carry = sum / 10;
        };
        if (carry != 0)
            ans += to_string(carry);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
