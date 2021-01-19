/* solution 1: hashtbl (Similar to TwoSum problem)
 * Main idea: Instead of adding two numbers to see if it equals to a power of two,
 *            we iterate over the numbers in deliciousness[].
 *            For each number n, 
 *                  1. enumerate all the possible sums(power of two)
 *                  2. find the number m by (sum-n) and look-up m in the hashtbl
 *                      (m must be the best partner of n since m+n is a power of two)
 *                  3. if we find m in the hashtbl, then add the times of appearence of m to the ans
 *                      ans += map[m] //since m might appear 3 times, so we can generate 3 pairs of (n,m)
 *                  4. insert n into the hashtbl
 * worst case: deliciousness = [a,a,a,a,.....a], a = 2^20
 *             Hence, the biggest sum of a pair will be a+a=2a=2^21
 * time complexity: O(n)
 * space complexity: O(n)
 */
class Solution {
public:
    unordered_map<int, int> map;
    int countPairs(vector<int>& deliciousness) {
        int ans = 0;
        int mod = 1e9+7;
        for(auto num: deliciousness){
            int base = 1;
            /* note that: base == num if num is the power of two
             * Example: num=1, base=1, so base-num=0 --> pair(0,1) is a good meal
             */
            for(int i = 0; i <= 21; i++){
                if(base >= num && map[base-num]){
                    ans += map[base-num];
                    ans %= mod;
                }
                base = base<< 1;
            }
            map[num]++;
        }
        return ans;

        /* solution2: hashtbl
         * Main idea: Reorganize the deliciousness[] into a hashtbl (count the dup times of each number)
         *            Example: [1,1,1,3,3,3,7]--> hashtbl= [1:3], [3:3], [7:1]
         *            Iterate the items in the hashtbl:
         *              - Adding two numbers(n,m) to see if the sum equals to a power of two
         *              - Ignore the number,
         *                - if n or m is odd
         *                - if n and m are the same but the count of n is less than 1
         *                  (it means that n only appears once)
         *              - calculate the answers
         *                - for [a,b], [a,b] if b > 1, ans += b*(b-1)/2
         *                - for [a,b], [c,d] ans +=  b*d
         *              Example: 
         *                  for [1:3][3:3], 1+3=4=2^2, so ans = 3*3=9 possible pairs
         *                  for [1:3][1:3], 1+3=4=2^2, so ans = 3*2/2=3 (3 numbers choose 2 for a pair)
         *  How to know if a number is a power of two?
         *     1. count the number of bit 1 (a power of two only has one bit1)
         *          --> __builtin_popcount(num)
         *     2. bit operation: (n & (n-1)) == 0 && (n > 0)
         */
        /*
        unordered_map<int, int> summap;
        set<int> hashtbl;
        vector<vector<int>> multimap(1000, vector<int>(1000, 0));
        //reorganize input
        for(int i = 0; i < deliciousness.size(); i++)
            map[deliciousness[i]]++;
        //iterate over the input
        int ans = 0;
        for(auto it = map.begin(); it != map.end(); it++){
            for(auto it2 = it; it2 != map.end(); it2++){
                if(it == it2 && it->second <= 1){
                    continue;
                }else if((it2->first != 1) && ((it->first & 1) == 0) && ((it2->first & 1) == 1) ){
                    continue;
                }else if((it->first != 1) && ((it->first & 1) == 1) && ((it2->first & 1) == 0)){
                    continue;
                }
                int sum = it->first + it2->first;
                //case 1: self + self
                if(it == it2 && it->second > 1 && isGoodMeal(sum)){
                    if(summap[it->second])
                        ans += summap[it->second];
                    else{
                        summap[it->second] = it->second * (it->second -1) / 2;
                        ans += summap[it->second]; 
                    }
                }else if(isGoodMeal(sum)){
                    if (multimap[it->second][it2->second] == 0)
                       multimap[it->second][it2->second] = it->second * it2->second;
                    ans+=multimap[it->second][it2->second];
                    //ans+=it->second * it2->second;
                }
                if(ans > mod) ans %= mod;
            }
        }
        return ans;
        */
    }
    /*
    bool isGoodMeal(int sum){
        if(hashtbl.count(sum))
            return true;
        //if(__builtin_popcount(sum) != 1){
        if((sum > 1 && (sum & (sum-1)) == 0) || (sum == 1)){
            hashtbl.insert(sum);
            return true;
        }else{
            return false;
        }
    }*/
};
