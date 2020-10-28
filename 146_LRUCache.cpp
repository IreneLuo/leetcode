/* LRUCache - Least Recently Used Cache
 * We use a double linked list and a hashtbl to implement this cache
 * 1. Linked List
 *    we create a dummyHead and dummyTail to operate add,remove...function much more easier
 *    the list might look like:
 *                                   DH <-> A <-> B <-> C <-> D <-> DT
 *    According to the characteristics of a LRUCache,
 *    a. we put a new item after DH, so the oldest items will be pushed towards DT
 *    b. if the size is over maxCapacity, we remove the last node (the node before DT)
 *    c. When we access an item, we have to move this item to the front
 *       (the node which had been accessed most recently will be put at the front,
 *        and the node that seldom use will be push to the back)
 * 2. Hashtbl
 *    Linked List need O(n) time for searching/inserting/removing a node
 *    so we add a hash table to speed up the time to O(1)
 *    The hash table might look like:
 *    note that value in the tash table is the address of nodes in the linked list
 *     [key]    [value]         DH <-> A <-> B <-> C <-> D <-> DT
 *       0     0x12fa32fa -------------^     ^     |     ^
 *       1     0xfbbc7684 -------------------|     |     |
 *      ...       ...     --------------------------     |
 *       n     0xffffdaa8 --------------------------------
 *   
 */
class Node {
public:
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v){
        key = k;
        value = v;
        prev = NULL;
        next = NULL;
    }
};
class LRUCache {
    int maxCapacity;
    int totalItemsInCache;
    unordered_map<int, Node*> hashTbl;
    Node* dummyTail;
    Node* dummyHead;
public:
    /* initialize LRUCache
     * 1. set maxCapacity
     * 2. create dummy head, tail and link them together
     * 3. set totolItemsInCache = 0
     */
    LRUCache(int capacity) {
        maxCapacity = capacity;
        dummyHead = new Node(0, 0);
        dummyTail = new Node(0, 0);
        dummyHead->next = dummyTail;
        dummyHead->prev = NULL;
        dummyTail->next = NULL;
        dummyTail->prev = dummyHead;
        totalItemsInCache = 0;
    }
    /* Get the value from LRUCache
     * We need to search the value by key in LRUCache
     *    a. if it exist, move it to the head and return the value
     *    b. if it doesn't exist, return -1
     */
    int get(int key) {
        auto it = hashTbl.find(key);
        if(it == hashTbl.end()) {
            return -1;
        } else {
            move_to_the_head(it->second);
        }
        return it->second->value;
    }
    /* Put a new item in the LRUCache
     * We need to search the value first
     *    a. if it exists, update the value and move it to the head
     *    b. if it doesn't exist, create a node, insert it to the hashTbl and add it to the front
     * If totalItemsInCache > maxCapacity, remove the tail of the list and remove the item in the hashTbl
     */
    void put(int key, int value) {
        auto it = hashTbl.find(key);
        if(it == hashTbl.end()) {     
            Node* newnode = create_the_node(key, value);
            hashTbl.insert(pair<int, Node*>(key, newnode));
            if(totalItemsInCache > maxCapacity)
                remove_the_node(dummyTail->prev, 1);
        } else {
            it->second->value = value;
            move_to_the_head(it->second);
        }
    }
    /*
     * move a node to the head
     * 1. plug out the node from original position
     * 2. add it to the front
     */
    void move_to_the_head(Node* node) {
        remove_the_node(node, 0);
        add_to_the_front(node);
    }
    /*
     * insert a node to the head
     * ex:  insert A into DH <-> B
     */
    void add_to_the_front(Node* node) {
        dummyHead->next->prev = node; // A <- B
        node->next = dummyHead->next; // A <-> B
        dummyHead->next = node;       // DH -> A <-> B
        node->prev = dummyHead;       // DH <-> A <-> B
    }
    /* create a node
     *
     */
    Node* create_the_node(int key, int value) {
        Node* node = new Node(key, value);
        add_to_the_front(node);
        totalItemsInCache++;
        return node;
    }
    /*
     * remove a node, erase the item in hashTbl, update totalItemsInCache
     * ex: remove B from DH <-> A <-> B <-> DT
     * type = 1 means we have to remove it
     * type = 0 means we have to plug out it and maybe insert it to another position later
     */
    void remove_the_node(Node* node, int type) {
        node->prev->next = node->next; // DH <-> A -> DT
        node->next->prev = node->prev; // DH <-> A <-> DT
        if(type){
            hashTbl.erase(node->key);
            totalItemsInCache--;
            delete node;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
