    /* solution 1: hashtable(unordered_map) + binary search tree(set)
     * 1. hashtbl: <key, CacheNode*> store a key and an address of CacheNOde in BST
     *    BST: a balanced binary tree to link all the CachNode in a legal capacity
     * 2. operations
     *    1. get()
     *       - cannot find the item in hashtbl, return -1
     *       - can find the item in hashtbl, return val
     *           - delete the item from BST
     *           - update freq and tick
     *           - insert to the BST
     *    2. put()
     *       - can find the item
     *           - delete the item from BST
     *           - update freq and tick
     *           - insert to the BST
     *       - check the size of the BST is full or not
     *           - if yes, remove the item with smallest freq or tick
     *       - cannot find the item
     *           - create a new CacheNode, update value, freq, tick
     *           - insert to the BST
     *(c is capacity)
     * time complexity = O(logc)
     *    - insert/remove from BST: logc
     * space complexity = O(c)
     */
struct CacheNode{
        int key;
        int val;
        int freq;
        int tick;
        CacheNode(int key_, int val_, int freq_, int tick_):
                                key(key_), val(val_), freq(freq_), tick(tick_) {}
};
//why cannot use method like HuaHua
class myless{
    public:
    //smaller will be evited first
        bool operator ()(const CacheNode* a, const CacheNode* b) const{
            if(a->freq < b->freq)  return true;
            if(a->freq == b->freq) return a->tick < b->tick;
            return false;
        }
};
class LFUCache {
public:
    LFUCache(int capacity) {
         cacheCapacity = capacity;
         globalTick = 0;
    }
    
    int get(int key) {
        //if this node cannot be found in hashtbl, return -1
        if(!hashtbl.count(key)) return -1;
        //if this node can be found, update the freq and tick of this node
        CacheNode* node = hashtbl[key];
        touch(node);
        node = hashtbl[key];
        return node->val;
    }
    
    void put(int key, int value) {
        if (cacheCapacity == 0) return;
        auto it = hashtbl.find(key);
        if(it != hashtbl.end()){
            it->second->val = value;
            touch(it->second);
            return;
        }
        if(hashtbl.size() == cacheCapacity){
            //remove the first node in cache
            //remember to add * before cbegin()
            CacheNode* rmnode = *cache.cbegin();
            hashtbl.erase(rmnode->key);
            cache.erase(rmnode);
        }
        CacheNode* node = new CacheNode(key, value, 1, ++globalTick);
        hashtbl[key] = node;
        cache.insert(node);
    }
    void touch(CacheNode* node){
        //erase this node in Cache
        cache.erase(node);
        ++node->freq;
        node->tick = ++globalTick;
        cache.insert(node);
    }
private:
    unordered_map<int, CacheNode*> hashtbl;
    set<CacheNode*, myless> cache;
    int cacheCapacity;
    int globalTick;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
