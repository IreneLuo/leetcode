class TrieNode{
public:
    char character;
    //we use an array pointer to know what are the other
    //words that we can read from here. Each element can point to
    //a TrieNode with a character
    TrieNode* adjacents[26];
    bool endsWord;
    //initialize
    TrieNode(char c){
        character = c;
        for(int i = 0; i < 26; i++)
            adjacents[i] = NULL;
        endsWord = false;
    }
};

class Trie {
public:
    TrieNode* root;
    /** Initialize your data structure here. */
    // the beginning of a Trie will start from root node with character #
    Trie() {
        root = new TrieNode('#');
    }
    
    /** Inserts a word into the trie. */
    // 1. set curr to root
    // 2. traverse each character in word
    //    find out this character is in adjacents[] or not
    //    if not, create a new node with this character and add it
    //    into adjacents[]
    void insert(string word) {
        TrieNode* curr = root;
        for(int i = 0; i < word.size(); i++){
            int idx = word[i] - 'a';
            if(curr->adjacents[idx] == NULL)
                curr->adjacents[idx] = new TrieNode(word[i]);
            curr = curr->adjacents[idx];
        }
        curr->endsWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* curr = root;
        for(int i = 0; i < word.size(); i++){
            int idx = word[i] - 'a';
            if(curr->adjacents[idx] == NULL)
                return false;
            curr = curr->adjacents[idx];
        }
        // if curr->endsWord is false, it means the input is just a prefix
        // not a word
        return curr->endsWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for(int i = 0; i < prefix.size(); i++){
            int idx = prefix[i] - 'a';
            if(curr->adjacents[idx] == NULL)
                return false;
            curr = curr->adjacents[idx];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
