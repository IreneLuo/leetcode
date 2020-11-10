/* solution: bit-operation concept
 *  if the least bit is odd, we need 2 operations to handle next bit
 *    1. number - 1
 *    2. right shift 1
 *  if the least bit is even, we need only 1 operations to handle next bit
 *    right shift 1 (= num /2)
 *  ex: 0x10000 (16)
 *      1. 0x1000"0" --> even so >> 1 = 0x1000 (1 op)
 *      2. 0x100"0" --> even so >> 1 = 0x100 (1 op)
 *      3. 0x10"0" --> even so >> 1 = 0x10 (1 op)
 *      4. 0x1"0" --> even so >> 1 = 0x1 (1 op)
 *      5. 0x1 --> odd so -1 & >> 1 = 0x0 (2 ops)
 *      we only have to reduce n to 1 so step 5 should be eliminated lik this
 *      1 + 1 + 1+ 1 + 2 - 2 = 4
 *  ex: 0x111 (6)
 *      1. 0x11"1" --> odd so -1 & >> 1 = 0x11 (2 ops)
 *      2. 0x11 --> odd so -1 &>> 1 = 0x1 (2 ops)
 *      3. 0x1 --> odd so -1 & >> 1 = 0x0 (2 ops)
 *      the answer = 6 - 2 = 4
 *  time complexity = O(logn) --> logn = how many bits of number n
 *  space complexity = O(1)
 */
class Solution {
  public:
    int minimumStepsToReachOne(int input) {
      if(input == 1)
        return 0;
      int ops = 0;
      while(input){
        ops = (input & 1) + 1;
        input >> 1;
      }
      return ops-2;
    }
};
