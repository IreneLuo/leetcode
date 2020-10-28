    /* solution 2: Heap w/ hashmap
     * time complexity = O(nlogk)
     * space complexity = O(n) + O(nlogk) +O(klogk) = O(nlogk) if k < N
     *                    O(n) if n=k
     * time complexity = O(n+k)
     *  - a hash map for O(n)
     *  - a heap for O(k)
     */

/* We put k items into the heap
 * and use "count" to decide the order of those items
 */
class ITEM{
public:
        int id;
        int count;
        ITEM(int i,int c) {
            id = i;
            count = c;
        };
};
/* we customize our greater function for the heap
 * i1's count > i2's count means that the i1 will be at the bottom if the count of it is greater than i2
 * In this way, we can ensure that the smallest item will be on the top of the heap
 */
class mycompare{
public:
    bool operator() (ITEM* i1, ITEM* i2){
        return (i1->count > i2->count);
    }
};
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if(nums.size() == k)
            return nums;

        // 1. create a hash map <element, freq>: time complexity = O(n)
        unordered_map<int, int> map;
        for(int i = 0; i < nums.size(); i++){
            if(map.find(nums[i]) != map.end()){
                map[nums[i]] += 1;
            }else{
                map.insert(pair<int, int>(nums[i], 1));
            }
        }
        // 2. build a heap of size k using N elements: time complexity = O(nlogk)
        //    add the first k elements and start to push and pop until we go through n elements
        priority_queue<ITEM*, vector<ITEM*>, mycompare> pq;
        for(auto it = map.begin(); it != map.end(); it++){
            ITEM* item = new ITEM(it->first, it->second);
            // note that we must push an item then pop it if size > k to ensure that the smallest item will be pop out
            // O(k) in best case, O(log1+log2+...+logk) = O(klogk) in worst case
            pq.push(item);
            // O(logk) per step * (n-k) steps = O((n-k)*logk)=O(nlogk)
            if(pq.size() > k)
                pq.pop();
        }
        // 3. convert a heap into an output arraytime complexity = O(klogk)
        //    time complexity = k times * O(logk) per time = O(klogk)
        vector<int> ans;
        while(!pq.empty()){
            ans.push_back(pq.top()->id);
            pq.pop();
        }
        return ans;
    }
};
