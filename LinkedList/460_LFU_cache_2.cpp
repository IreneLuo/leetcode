    /* solution 2: hashtable(unordered_map) + cache(unorder_map)
     * TODO: fail, fix it! and try if hashtbl is int, CacheNode
     */
struct CacheNode{
        int key;
        int val;
        int freq;
        list<int>:: const_iterator it;
        CacheNode(int k, int v, int f, 
                  list<int>:: const_iterator i): key(k), val(v), freq(f), it(i) {}
};

class LFUCache {
public:
    LFUCache(int capacity) {
        cacheCapacity = capacity;
        min_freq = 0;
    }
    
    int get(int key) {
        /* check the hashtbl.
         * if the key has ready existed,
         * touch this node and return the value
         * if cannot find the key, return -1
         */
        auto it = hashtbl.find(key);
        if(it == hashtbl.end())
            return -1;
        touch(it->second);
        return it->second->val;
    }
    
    void put(int key, int value) {
        if(cacheCapacity == 0)
            return;
        auto it = hashtbl.find(key);
        if(it != hashtbl.end()){
            it->second->val = value;
            touch(it->second);
            return;
        }
        /* if hashtbl is full
         * remove the last item in the min-freq list
         */
        if(hashtbl.size() == cacheCapacity){
            const int key_to_delete = cache[min_freq].back();
            hashtbl.erase(key_to_delete);
            cache[min_freq].pop_back();
        }
        /* create a new CacheNode and insert into the hashtbl and cache
         */
        int freq = 1;
        min_freq = freq;
        cache[freq].push_front(key);
        list<int>::const_iterator curr_it = cache[freq].cbegin();
        CacheNode* node = new CacheNode(key, value, freq, curr_it);
        hashtbl[key] = node;
    }
    void touch(CacheNode* node){
        //update the freq
        int old_freq =node->freq;
        int new_freq = node->freq + 1;
        //remove the entry(key) from the list(in cache)
        cache[old_freq].erase(node->it);
        //check min_freq
        if(cache[old_freq].empty() && old_freq == min_freq){
            cache.erase(old_freq);
            ++min_freq;
        }
        //insert the key to the front in the list of cache[new_freq]
        cache[new_freq].push_front(node->key);
        //update the it (to a new position of the key)
        node->it = cache[new_freq].cbegin();

    }
private:
    /* key -> CacheNode */
    unordered_map<int, CacheNode*> hashtbl;
    /* freq -> list(key) */
    unordered_map<int, list<int>> cache;
    int cacheCapacity;
    int min_freq;
};
/* fail case
["LFUCache","put","put","put","put","put","get","put","get","get","put","get","put","put","put","get","put","get","get","get","get","put","put","get","get","get","put","put","get","put","get","put","get","get","get","put","put","put","get","put","get","get","put","put","get","put","put","put","put","get","put","put","get","put","put","get","put","put","put","put","put","get","put","put","get","put","get","get","get","put","get","get","put","put","put","put","get","put","put","put","put","get","get","get","put","put","put","get","put","put","put","get","put","put","put","get","get","get","put","put","put","put","get","put","put","put","put","put","put","put"]
[[10],[10,13],[3,17],[6,11],[10,5],[9,10],[13],[2,19],[2],[3],[5,25],[8],[9,22],[5,5],[1,30],[11],[9,12],[7],[5],[8],[9],[4,30],[9,3],[9],[10],[10],[6,14],[3,1],[3],[10,11],[8],[2,14],[1],[5],[4],[11,4],[12,24],[5,18],[13],[7,23],[8],[12],[3,27],[2,12],[5],[2,9],[13,4],[8,18],[1,7],[6],[9,29],[8,21],[5],[6,30],[1,12],[10],[4,15],[7,22],[11,26],[8,17],[9,29],[5],[3,4],[11,30],[12],[4,29],[3],[9],[6],[3,4],[1],[10],[3,29],[10,28],[1,20],[11,13],[3],[3,12],[3,8],[10,9],[3,26],[8],[7],[5],[13,17],[2,27],[11,15],[12],[9,19],[2,15],[3,16],[1],[12,17],[9,1],[6,19],[4],[5],[5],[8,1],[11,7],[5,2],[9,28],[1],[2,2],[7,4],[4,22],[7,24],[9,26],[13,28],[11,26]]
*/
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
