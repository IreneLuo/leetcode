/* LRUCache - Least Recently Used Cache
 * We use a double linked list and a hashtbl to implement this cache
 * Solueion 2: use std:list instead of implement a linkedlist
 * time complexity = O(1)
 * space complexity = O(capacity)
 */
class LRUCache {
    int maxCapacity;
    //key->it
    unordered_map<int, list<pair<int, int>>::iterator> hashTbl;
    //key, value -> key, value->...
    list<pair<int, int>> cache;
public:
    /* initialize LRUCache
     * 1. set maxCapacity
     */
    LRUCache(int capacity) {
        maxCapacity = capacity;
    }
    /* Get the value from LRUCache
     * We need to search the value by key in LRUCache
     *    a. if it exist, move it to the head and return the value
     *    b. if it doesn't exist, return -1
     */
    int get(int key) {
        auto it = hashTbl.find(key);
        if(it == hashTbl.end())
            return -1;
        //move the item to the front
        cache.splice(cache.begin(), cache, it->second);
        return it->second->second;
    }
    /* Put a new item in the LRUCache
     * We need to search the value first
     *    a. if it exists, update the value and move it to the head
     *    b. if it doesn't exist, create a node, insert it to the hashTbl and add it to the front
     * If totalItemsInCache > maxCapacity, remove the tail of the list and remove the item in the hashTbl
     */
    void put(int key, int value) {
        auto it = hashTbl.find(key);
        if(it != hashTbl.end()) {     
            it->second->second = value;
            //move the item to the front
            cache.splice(cache.begin(), cache, it->second);
            return;
        }
        if(cache.size() == maxCapacity){
            int key = cache.rbegin()->first;
            cache.pop_back();
            hashTbl.erase(key);
        }
        cache.push_front(pair<int, int>(key, value));
        hashTbl[key] = cache.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
