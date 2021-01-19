class Solution {
public:
    /*
     * 1. if abs(num) % 7 >= 7 --> use A,B,C,D,E,F,G
     * 2. if abs(num) % 7 <= 6 --> use string "0"~"6"
     * 3. after getting remainder, reset num to num / 7,
     *    then go to step2 until num equals to zero.
     * 4. reverse result and append "-" if needed.
     * ex: num = 101           --> 100 % 7 = 3 --> result = 3
     *     num = 100 / 7 = 14  --> 14  % 7 = 0 --> result = 30
     *     num = 14  / 7 = 2   --> 2   % 7 = 2 --> result = 302
     *     num = 2   / 7 = 0   --> stop
     *     reverse result to 203 (since it's positive, so we don't append "-")
     */
    void calculate(int num, string *ans){
        if (num == 0)
            return;

        int x = num % 7;
        if (x >= 7)
            *ans +='A' + (x-7);
        else
            *ans +='0' + x;

        num /= 7;
        calculate(num, ans);
    }

    string convertToBase7(int num) {
        string ans;     
        if (num == 0) {
            ans = "0";
        }else {
            calculate(abs(num), &ans);
            reverse(ans.begin(), ans.end());
            if (num < 0)
                ans.insert(0, "-");
        }
        return ans;
    }
};
