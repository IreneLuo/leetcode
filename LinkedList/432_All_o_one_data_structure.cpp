/* solution: hashtbl + linkedlist
 *
 *                         |-----struct Node --------|
 *   hashtbl:        list [value = 1, keys={leet, code}]<->[value = 2, keys={str}]
 *    [leet]: it -------------^                              ^
 *    [code]: it -------------^                              |
 *    [str]:  it ---------------------------------------------
 *    ....   ...
 *   In our hashtbl, we save the iterator that points to the node that store this key
 *   so we can access the node in constant time
 *   dec: O(1)
 *   inc: O(1)
 */
class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {
        
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        auto it = hashtbl.find(key);
        /* if the key doesn't exist, 
         *   - it there's no any keyset which value is 1, create a new node(value=1, key=key) and insert to the keyslist and hashtbl
         *   - if there's a keyset which value is 1, insert this key into that keyset
         */
        if(it == hashtbl.end()){
            if(keyslist.empty() || keyslist.front().value != 1)
                keyslist.push_front({1, {key}});
            else
                keyslist.front().keys.insert(key);
            hashtbl[key] = keyslist.begin();
            return;
        }
        /* if the key exists:
         *     - if the value of the next node in keyslist = current node's value + 1, insert key into the next node
         *     - otherwise, create a new node (value = current node's value + 1, key) in the keylists and delete current node
         */
        auto it_in_keyslist = it->second;
        auto next_it = next(it_in_keyslist);
        if(next_it == keyslist.end() || next_it->value != it_in_keyslist->value + 1)
            next_it = keyslist.insert(next_it, {it_in_keyslist->value + 1, {}});
        next_it->keys.insert(key);
        hashtbl[key] = next_it;
        it_in_keyslist->keys.erase(key);
        if(it_in_keyslist->keys.empty())
            keyslist.erase(it_in_keyslist);
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        /* if the key doesn't exist, 
         * return
         */
        auto it = hashtbl.find(key);
        if(it == hashtbl.end())
            return;
        /* if the key exists:
         *     - if the value of the prev node in keyslist = current node's value - 1, insert key into the prev node
         *     - otherwise, create a new node (value = current node's value - 1, key) in the keylists and delete current node
         */
        auto it_in_keyslist = it->second;
        if(it_in_keyslist->value > 1){
            auto prev_it = prev(it_in_keyslist);
            /* cannot use prev == keyslist.crend() */
             if(it_in_keyslist == keyslist.begin() || prev_it->value != it_in_keyslist->value - 1)
                 /* must insert at it_in_keyslist, not prev_it
                  * since insert() will insert new item before the position n (param1)
                  */
                prev_it = keyslist.insert(it_in_keyslist, {it_in_keyslist->value - 1, {}});
             prev_it->keys.insert(key);
             hashtbl[key] = prev_it;
        }else{
            hashtbl.erase(key);
        }
       
        it_in_keyslist->keys.erase(key);
        if(it_in_keyslist->keys.empty())
            keyslist.erase(it_in_keyslist);
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        /* 1. get the last node from the keylists (keyslist.back() returns an it)
         * 2. retrieve the keys from the node (.keys returns an unordered_set)
         * 3. get the first entry in the keys (.cbegin() returns an it)
         */
       return (keyslist.empty()) ? "" : *keyslist.back().keys.cbegin();
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
       return (keyslist.empty()) ? "" : *keyslist.front().keys.cbegin();
    }
private:
    struct Node{
        int value;
        unordered_set<string> keys;
    };
    list<Node> keyslist;
    unordered_map<string, list<Node>::iterator> hashtbl;
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
