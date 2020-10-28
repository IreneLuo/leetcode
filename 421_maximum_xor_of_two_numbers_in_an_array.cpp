        /* Solution 2: using Trie
         * 1. define a Trie and a TrieNode structure.
         *    (We use a series of TrieNodes to save all the input values.
         *    Each TrieNodes represents bit 0 or bit 1)
         * 2. traverse the input values(num)
         *    2.1. insert num into the Trie
         *      a. transfer the num into a bitset
         *      b. create a TrieNode for each bit and connect them with each other
         *    2.2  find the complement value(we call the comp) in the Trie, and calculate the maxXOR
         *      If we find the complement value, we can obtain (the comp ^ the num) = maxXOR.
         *      What is the complement value? We can get it by reversing every bit in the num.
         *      ex: the num = 0001--> the comp = 1110 --> the maxXOR = 0001 ^ 1110 = 1111
         *      a. for each bit of the num, we reverse it and find that if it exists in the Trie as a TrieNode
         *      b. if yes, we calculate the maxXOR by using 1 << 31-i, which i is the idx of this bit
         *      c. then we jump to the next TrieNode and go to step a. to deal with the next bit
         *    2.3 return a maxXOR and compare with the ans
         *         
         * time complexity: 2 * O(n) = O(n)
         *  - insert: log(h) * n times(the number of input is n) = nlogh = O(n)
         *            Here h = 32(tree height) since there're only 32 bits for a bitset,
         *            so we can consider it as a constant
         *            that is, each insert only spending O(1) time
         *  - search max: log(k) * n times = nlogk = O(n)
         * space complexity: O(n)
         *  - we have n values, each value can have max h(32) nodes in the Trie
         *    so n*h = n*32 = O(n)
         *
         */
class Trie {
public:
    class TrieNode {
    public:
        bool end;
        TrieNode* next[2];

        TrieNode() {
            end = false;
            next[0] = NULL;
            next[1] = NULL;
        }  
    };
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(int value) {
        TrieNode* ptr = root;
        string val_str = bitset<32>(value).to_string();
        // ex: value = 2 --> val_str = 0000...0010
        // for each bit, we create a TrieNode in the Trie
        for(int i = 0; i < val_str.size(); i++) {
            int b = val_str[i] - '0';
            if (!ptr->next[b])
                ptr->next[b] = new TrieNode();
            ptr = ptr->next[b];
        }
        // after inserting all the nodes, we set the end to true
        ptr->end = true;
    }

    int maxXOR(int value) {
        TrieNode* ptr = root;
        string val_str = bitset<32>(value).to_string();
        // ex: value = 2 --> val_str = 0000...0010
        // for each bit, we find a reverse bit and see if it exists in the Trie
        // bit 28 = 0 -->rev_b = 1 --> if find in the Trie --> ans += 1 << (31-28)
        // bit 29 = 0 -->rev_b = 1 --> if find in the Trie --> ans += 1 << (31-29)
        // bit 30 = 1 -->rev_b = 0 --> if find in the Trie --> ans += 1 << (31-30)
        // bit 31 = 0 -->rev_b = 1 --> if find in the Trie --> ans += 1 << (31-31)
        // ans will be 0x1111 = 0010 ^ 1101
        // once we find out all the rev_b in the Trie, we could calculate the maxXOR
        // so our mission is finding out those rev_b!
        int maxXOR = 0;
        for(int i = 0; i < val_str.size(); i++) {
            int b = val_str[i] - '0';
            int rev_b = b ^ 1;
            if (ptr->next[rev_b]) {
                maxXOR += 1 << (31 - i);
                ptr = ptr->next[rev_b];
            } else {
                ptr = ptr->next[b];
            }
        }
        return maxXOR;
    }
};
class Solution {

public:
    int findMaximumXOR(vector<int>& nums) {
        Trie bitTrie;
        int ans = 0;
        for(auto& val : nums) {
            bitTrie.insert(val);
            ans = max(ans, bitTrie.maxXOR(val));
        }
        return ans;
    }
};
