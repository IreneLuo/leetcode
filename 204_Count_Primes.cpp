class Solution {
public:
    /* Solution 1:
    *  1. check numbers from 1 ~ n-1 (take x for example)
    *  2. divide x by all prime numbers in ans(these prime numbers should be less than sqrt(n))
    *  3. if none of a remainder equals to zero, which means x is a prime number less than n
    *  4. time complexity = O(n * sqrt(n)) = O(n^1.5)
    *     space complexity = O(n)
    *  ex: n = 499979
    *         candidate will be from 1 ~ 499978
    *         square root of 499978 = 707
    *         1. for x from 1 to 499978
    *         2. if x % (any prime numbers less or equal to 707) == 0 --> x is not a prime number
    *            otherwise, x is a prime number and push it into ans 
    */
    int countPrimes(int n) {
/*
        // to store prime numbers
        vector<int> ans;
        
        // There is no any prime number when n = 0 or 1 or 2
        if (n <= 2)
            return 0;

        // the candidate will be started from 3, hence we push a minimum prime
        // number into ans to avoid an error when candidate % ans[0].
        ans.push_back(2);

        for (int candidate = 3 ;candidate < n; candidate++){
            bool is_prime = true;
            for (int i = 0; i < ans.size(); i++){
                // we only look for ans[i] that is less than sqrt of candidate
                // to speed up the process
                if (ans[i] > sqrt((double)candidate))
                    break;
    
                //candidate is not a prime number, so skip this candidate
                if (candidate % ans[i] == 0){
                    is_prime = false;
                    break;
                }
            }
            if (is_prime)
                ans.push_back(candidate);
        }
        return ans.size(); 
*/
/* Solution 2:
 * 1. Use an array to record each number is prime or not.
 * 2. Instead of finding out who is a prime number, we focus on
 *    finding those who are not prime numbers by notifying 
 *    multiples of 1, 2,...,until sqrt(n) to false.
 * 3. count the numbers of true in ans and return
 * 4. time complexity = O(sqrt(n)loglogn)
 *    space complexity = O(n)
 *    ref: https://leetcode.com/problems/count-primes/discuss/473021/Time-Complexity-O(log(log(n))-Explained
 *    ref: https://stackoverflow.com/questions/16472012/what-would-cause-an-algorithm-to-have-olog-log-n-complexity
 * ex: n = 10 --> ans[9] = [true, true,...,true]
 *     ans[0] & ans[1] are false, because both are not prime numbers
 *     2 * 2   3 * 2  --> those 5 cases show that they are not prime numbers,
 *     2 * 3   3 * 3      so we change these numbers' state to false.
 *     2 * 4              ans = [f, f, t, t, f, t, f, t, f, f]
 *
 */
        if (n == 0)
            return 0;
        vector<bool> ans(n, true);
        ans[0] = false;
        ans[1] = false;
        for (int i = 1; i <= sqrt(n-1); i++){ // O(sqrt(n))
            if (ans[i]){
                for (int j = 2; i*j <= n-1; j++) { // O(loglog(n))
                    ans[i*j] = false; 
                }
            }
        }
        return count(ans.begin(), ans.end(), true);
    }
};
