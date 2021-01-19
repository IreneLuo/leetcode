/* solution: Heap/Hashtable
 *  1. Build a hashtable to collect the freq of each string
 *  2. Push all items in hashtable to the min-Heap
 *     (the less freq item will be on the top)
 *  3. We only keep k items in min-Heap, so once the size
 *     of min-Heap > k, we pop out the top item
 *     ==> In this way, the top k freq words will be
 *         stored in min-Heap
 *  4. Retrieve the items from min-Heap
 *     (the items are in ascending order)
 *  5. Reverse the items to descending order
 *
 *  time complexity = O(nlogk)
 *  space complexity = O(n)
 */
typedef pair<string, int> entry;
struct mycompare{
    bool operator()(const entry& e1, const entry& e2){
        if(e1.second == e2.second) return e1.first<e2.first;
        return e1.second > e2.second;
    }
};
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        // build a hashtbl: O(n)
        unordered_map<string, int> tbl;
        for(auto& w: words)
            ++tbl[w];
        // push the items in the hashtbl into the min-Heap
        // O(nlogk)
        priority_queue<entry, vector<entry>, mycompare> pq;
        for(auto& t: tbl){
            pq.push(t);
            if(pq.size() > k)
                pq.pop();
        }
        //retrieve the items in min-Heap
        //O(n)
        vector<string> ans;
        while(!pq.empty()){
            ans.push_back(pq.top().first);
            pq.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
