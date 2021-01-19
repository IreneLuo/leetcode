class MyLinkedList {
public:
    /** Initialize your data structure here. */
    MyLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    //add by myself
    ~MyLinkedList(){
        while(head){
            Node* curr = head;
            head = head->next;
            delete curr;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if(index >= size || index < 0) return -1;

        Node* ptr = head;
        /*
        while(index >= 0){
            ptr = ptr->next;
            --index;
        }
        */
        while(index--)
            ptr = ptr->next;
        return ptr->val;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        /*
        Node node = new Node(val);
        node->next = head;
        head = node;
        */
        /* we shrink the code to this */
        /* if head is nullptr, this node will point to nullptr */
        head = new Node(val, head);
        /*
        ++size;
        if(size == 1)
        */
        if(++size == 1)
            tail = head;
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        Node* node = new Node(val);
        if(++size == 1){
            tail = head = node;    
        }else{
            tail->next = node;
            tail = node;
            
        }
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        Node* prev = head;
        if(index > size || index < 0) return;
        if(index == 0) return addAtHead(val);
        if(index == size) return addAtTail(val);

        --index;
        while(index--)
            prev = prev->next;
        /*
        Node* node = new Node(val);
        node->next = prev->next;
        prev->next = node;
        */
        prev->next = new Node(val, prev->next);
        ++size;
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if(index >= size || index < 0) return;
        /* dummy -> head
         *   ^
         *  prev
         */
        Node dummy(0, head);
        Node* prev = &dummy;
        for(int i = 0; i < index; i++)
            prev = prev->next;
        Node* curr = prev->next;
        prev->next = curr->next;
        //update the head and tail
        if(index == 0) head = head->next;
        if(index == size-1) tail = prev;
        delete curr;
        --size;
    }
 private:
    struct Node{
        int val;
        Node* next;
        Node(int v): Node(v, nullptr) {}
        Node(int v, Node* n): val(v), next(n) {}
    };
    Node* head;
    Node* tail;
    int size;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
