class Solution {
    /* solution: greedy algorithm
     * Choose the smallest one to be the start
     * and using start and k to get the expected rest of numbers (start+1, start+2,..start+k-1)
     * time complexity = O(nlogn) //building MST --> map
     * space complexity = O(n)
     *
     * reference: https://zxi.mytechroad.com/blog/greedy/leetcode-1296-divide-array-in-sets-of-k-consecutive-numbers/
     * for hash method, see huahua's video
     */
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        map<int, int> freq;
        //add/update a node in the tree is O(nlogn)
        for(auto& it: nums)
            freq[it]++;

        //retieve the item from freq table one by one
        //so time = O(n)
        while(freq.size()){ //if there's any item in freq tree
            auto it = freq.begin(); //get the start number, O(1)
            int num = it->first;
            //by using k and start number, we can check that are the rest of target numbers
            //in the freq tree
            for(int i = 0; i < k; i++){
                /* Method 1: O(logn) --> the while loop outside will cost O(nlogn)
                 * it = freq.find(num+i);
                 * if(it==freq.end())
                 *  return false;
                 */
                /* Method 2: O(1) --> the while loop outside will cost O(n)*/
                if(it->first != num + i)
                    return false;
                //
                else{
                    it->second--;
                    if(it->second == 0)
                        freq.erase(it);
                }
                /* Method 2: O(n) */
                it++;
            }
        }
        return true;
    }
};
