class MapSum {
public:
    /** Initialize your data structure here. */
    MapSum() {
        
    }
    /* solution 1:
     * we create two hashtbl.
     * 1 for key-value, 1 for prefix-sum
     * Insert():
     *   - a new key: insert key-value to hashtbl 1
     *                find all matched prefix and add value to all entries in hashtbl 2
     *   - an key that already exists: change value in hashtbl 1
     *                                 find all matched prefix and change the value to all entries in hashtbl 2
     * time complexity = O(mn)
     *   - m = numbers of key
     *   - n = length of a key
     * space complexity = O(mn)
     *   - m = numbers of key
     *   - n = length of a key
     *
     * Worst case: all the keys don't have same prefix
     *   ab, cd, ef, gh
     *  prefix = a, ab, c, cd, e, ef, g, gh
     *  --> total = 2*4 = 8 entries in hashtbl
     */
    //better to move to private area
/*
    unordered_map<string, int> nums;
    unordered_map<string, int> sums;
    void insert(string key, int val) {
        int diff = val;
        if(nums.count(key))
            diff = val - nums[key];        
        //we must insert or modify this entry after count()
        nums[key] = val;
        //note that i can be equal to length
        //since a key can be a prefix as well
        for(int i = 1; i <= key.length(); i++){
            sums[key.substr(0, i)] += diff;
        }
    }
    int sum(string prefix) {
        return sums[prefix];
    }
*/
    /* solution 2: Trie + hashtbl
     * we use a hashtbl for storing key-val
     * and use a trie to store the prefix-sum
     * A Trie node contains:
     *   - a vector that represents all possible digit of a prefix
     *   - a sum
     *  [a] [b] [c] ... [z]    --> first layer: a-z nodes
     *         /...\
     *     [a] [b] [c] ... [z] --> second layer: we have a-z nodes under c
     *
     * We simplify the Trie like this:
     * insert: ["apple", 3]["app", 2]["ape", 1]
     *   sum: ["ap"]
     *
     *              [a] 3+2+1
     *             /
     *           [p] 3+2+1
     *          /   \
     *       [p] 3+2 [e] 1
     *       /
     *     [l] 3
     *     /
     *  [e] 3
     *
     * So for sum() operation, we just traverse the node and return the sum
     *
     */
    struct Trie{
        vector<Trie*> children;
        int sum;
        Trie(){
            children = vector<Trie*>(26, nullptr);
            sum = 0;
        }
        ~Trie(){
            for(auto i:children)
                if(i) delete(i);
            children.clear();
        }
    };
    unordered_map<string, int> nums;
    Trie root;
    void insert(string key, int val) {
        /* if key does not exist, diff = val - 0
         * if key exist, diff = val
         */
        int diff = val - nums[key];
        nums[key] = val;
        Trie* t = &root;
        for(auto ch: key){
            int idx = ch-'a';
            if(!t->children[idx])
                t->children[idx] = new Trie();
             t->children[idx]->sum += diff;
             t = t->children[idx];
        }
    }
    int sum(string prefix) {
        Trie* t = &root;
        for(const auto ch: prefix){
            if(!t->children[ch-'a']) return 0;
            t = t->children[ch-'a'];
        }
        return t->sum;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
