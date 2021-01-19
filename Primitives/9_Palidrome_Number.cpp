/* Concept:
   Each time we compare the first and the last digit.
   If match, then discard both digit to get a new x,
   and compare again until we meet the middle of x.
    ex: 12321 --> 232 --> 3 (finish) --> return true
        ^   ^     ^ ^
    ex; 1241 --> 24 (finish) --> return false
        ^  ^     ^^
*/ 
class Solution {
public:
    bool isPalindrome(int x) {

        if (x < 0) return false;

        // ex: x = 313 = 3.13 * 10^2 --> log10(313) = 2 + log10(3.13) = 2.xxx
        double logx_ans = log10(x);
        // we can get the length of x by adding 1 to log10(x)
        // note that log10(x) might retern a non-positive value
        int x_len = (logx_ans > 0) ? floor(logx_ans) + 1 : 0;
        int tail_mask = 10;
        int head_mask = (int)pow(10.0, (double)x_len-1);

        for (int i = 0; i < (x_len / 2); i++) {
            // retreive the first digit and the last digit and compare them
            int head = x / head_mask ;
            int tail = x % tail_mask;
            if (head != tail) 
                return false;
            // if the head equals to the tail, discarding both head and tail so 
            // we can get a new x
            x = (x % head_mask) / tail_mask;  
            // due to each time we get rid of 2 digits(head and tail)
            // so head_mask must be removed 2 digits too
            head_mask /= 100;
              
        }
        return true;
    }
};
