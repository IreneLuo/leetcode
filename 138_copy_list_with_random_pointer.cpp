/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        /* solution 1 : copy a list of nodes
         * 1. pass 1: 
         *     a. create a node at once, clone the value only
         *     b. add<original node, clone node> into the hashmap
         * 2. pass 2: 
         *     a. clone the next and the random ptr by using hashmap
         *
         */
        if (head == NULL)
            return NULL;
/*
        unordered_map<Node*, Node*> map;
        Node* ptr;
        ptr = head;
        while(ptr != NULL) {
            map.insert(make_pair(ptr, new Node(ptr->val)));
            ptr = ptr->next;
        }

        ptr = head;
        while(ptr != NULL) {
            map.at(ptr)->next = (ptr->next != NULL) ? map.at(ptr->next) : NULL;
            map.at(ptr)->random =(ptr->random != NULL) ? map.at(ptr->random) : NULL;
            ptr = ptr->next;
        }
        return map.at(head);
*/

        /* Solution 2: use ptr to save more space
         * 1. first pass: (Interate over each node by ptr)
         *    a. create a ptr "next" and set to ptr->next
         *    b. create a new node "copy" and clone the value
         *    c. ptr->next = copy
         *    d. copy->next = next
         * 2. second pass: (random ptr)
         *    a. ptr->next->random(our copy node) = ptr->random->next
         * 3. third pass: (restore orginal list)
         *    a. ptr = head and create a dummyhead node(DH)
         *       and create a ptr "copy"= DH
         *    b. copy->next = ptr->next
         *       copy = copy->next; (so we keep the copy)
         *       ptr->next = copy->next; (restore the original node's next)    
         */
        Node* ptr;
        Node* next;

        ptr = head;
        while(ptr != NULL) {
            next = ptr->next;
            ptr->next = new Node(ptr->val);
            ptr->next->next = next;
            ptr = next; // not ptr = ptr->next!
        }

        ptr = head;
        while(ptr != NULL) {
            // if ptr->random is NULL, we cannot asign ptr->random->next to it!
            ptr->next->random = (ptr->random != NULL) ? ptr->random->next : NULL;
            ptr = ptr->next->next; // not ptr = ptr->next
        }

        ptr = head;
        Node DummyHead(-1);
        Node* copy = &DummyHead;
        while(ptr != NULL) {
            copy->next = ptr->next;
            ptr->next = copy->next->next;
            copy = copy->next;
            ptr = ptr->next;
        }
        return DummyHead.next;
    }
};
