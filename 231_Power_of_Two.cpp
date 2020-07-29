class Solution {
public:
    bool isPowerOfTwo(int n) {
/* Method 1:
 * If n is a power of two, then the binary representation of n will be exactly
 * only 1 bit turned on. Hence, we just check if there's only 1 bit turned on
 * to check if n is a power of two.
 * ex: 8 = 0b1000 --> 1000 & 0111 = 0000 --> 8 is a power of two
 *     9 = 0b1001 --> 1001 & 1000 = 1000 --> 9 is not a power of two
 * Note that although this method can detect negative input,
 * but if n = -1247483648, (n-1) will overflow
 * so we use (n > 0) to detect all the negative case and zero case
 */
        return ((n > 0) && (n & (n-1)) == 0);

/* Method 2:
 * if n is a power of 2, then n % 2 equals to 0
 * so we check if it meets the criteria after we divide n by 2
 * 8->4->2->1 (true)
 * 6->3 (false)
        if (n <= 0)
            return false;

        while((n % 2) == 0)
            n /= 2;

        return (n == 1) ? true : false;
*/
/* Method 3:
 * If n is a power of 2, log2(n) shoud be a positive integer,
 * so we use log2(n) to check the answer.
 * formula: log2(n) = log10(n)/log10(2)
 * Note: when we use log(n) instead of log10(n) in the calculation,
 * we might get a negative value even n is a power of 2
 * ex: n = 536870912
 
        if (n <= 0)
            return false;
        double x = log10((double)n);
        double y = log10((double)2);
        double z = x/y;
        return (floor(z) == z) ? true : false;
 */
    }
};
