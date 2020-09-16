/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* get_last_node_in_list(Node* head) {
        if (head == NULL)
            return NULL;

        Node* ptr = head;
        while(ptr->next != NULL)
            ptr = ptr->next;

        return ptr;
    }

    Node* flatten(Node* head) {
        /* solution:
         * 1. traverse over the list until we find a node(curr) which has a child
         * 2. save the node(next_to_curr) next to curr
         * 3. set curr=child, traverse the next-level list from child(step 1)
         * 4. if we traverse over the list (curr==NULL), return the head
         *    (childhead) of this list
         * 5. set curr->next = childhead, curr->child = NULL
         * 6. find the childlist's tail(childtail)
         *    set childtail->next = next_to_curr
         *    set next_to_curr->prev = childtail
         */
        if (head == NULL)
            return NULL;

        Node* curr = head;
        Node* next_to_curr;
        while(curr != NULL) {
            Node* childhead;
            Node* childtail;
            next_to_curr = curr->next;
            if(curr->child) {
                childhead = flatten(curr->child);
                curr->next = childhead;
                curr->child = NULL;
                childhead->prev = curr; //remember to set childhead's prev
                if(next_to_curr != NULL) {
                    childtail = get_last_node_in_list(childhead);
                    childtail->next = next_to_curr;
                    next_to_curr->prev = childtail;
                }
            }
            curr = curr->next;
        }
        return head;
    }
};
