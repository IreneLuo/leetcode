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

/* solutioni 2: bit operation + memorization(cache)
 * time complexity = O(logn)
 * space complexity = O(1)
 */
class Solution {
public:
    unordered_map<uint32_t, uint32_t> cache;
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        int32_t pos = 24; //32-8
        while(pos >= 0){
            ans += reverseBytes(n & 0xff) << pos;
            pos -= 8;
            n >>= 8;
        }
        return ans;
    }
    uint32_t reverseBytes(uint32_t n){
        cout<<(n)<<" ";
        //memorization
        if(cache.find(n) != cache.end())
            return cache[n];

        //reverse the bits within this byte
        uint32_t ans = 0;
        uint32_t i = 0;
        uint32_t key = n;
        while(i < 8){
            ans = (ans << 1) | (n & 1);
            n >>= 1;
            ++i;
        }
        cache[key] = ans;
        return ans;
    }
};
