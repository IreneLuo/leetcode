/* 190. Reverse Bits
 * Each time, we check bit0 of n is equal to 1 or not by & operator
 * If yes, we shift a bit to the left and append 1
 * If no, we just shift a bit only
 * Then, shift bit0 to the right for the next iteration
 * ex: n = 0101
 *     0101 & 1 = 000"1" --> ans = (0 << 1) | 1 = 0001, n >> 1
 *     0010 & 1 = 000"0" --> ans = (ans << 1) = 0010, n >> 1
 *     0001 & 1 = 000"1" --> ans = (ans << 1) | 1 = 0101, n >> 1
 *     0000 & 1 = 000"0" --> ans = (ans << 1) = 1010
 */
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        int i = 0;
        // i will be less than 32 because uint32t has 32 bits (from 0-31)
        while(i < 32) {
            ans = ((n & 1) == 1) ? (ans << 1) | 1 : ans << 1;
            n = n >> 1;
            i++;
        }
        return ans;
    }
};
