/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
    /* solution:
     * we have to consider several cases:
     * 1. root with left and right child --> let left node points to right node
     * 2. root with only left child --> find the child of root's next node
     * 3. root with only right child --> find the child of root's next node
     *
     * time complexity: T(n) <= 2T(n/2) + O(n) = O(nlogn) <= O(n^2)
     *  --> a function call will call 2 function calls, and each call handle half nodes of the tree --> 2T(n/2)
     *  --> get_next_node() needs O(n) time (we'be been discussed below)
     * we can also use a loosly boundery to O(n^2) --> for n nodes, each node might cross over the width of the tree(n) --> n * n = n ^2
     * but O(nlogn) is more tighter and closer than it.
     */
public:
    Node* connect(Node* root) {
        if(root == NULL)
            return NULL;

        // in normal case, we'll let root's left node points to root's right node
        // but if root's right node is null, we have to find root's next node to point to
        if(root->left != NULL) {
            if (root->right != NULL)
                root->left->next = root->right;
            else
                root->left->next = get_next_node(root->next);
        }
        // we use get_next_node to get the child of root's next node
        if(root->right != NULL && root->next != NULL)
            root->right->next = get_next_node(root->next);
 
        // right subtree must be done before left subtree
        // because a left subtree's right node needs a right subtree's next node 
        // ex: [2,1,3,0,7,9,1,2,null,1,0,null,null,8,8,null,null,null,null,7]
        // if we do left part first,
        // the right child 0 of 7 cannot point to 8 because 7's next node 9 hasn't connected yet
        root->right = connect(root->right);
        root->left = connect(root->left);
        return root;
    }
private:
    /* Time complexity
     * worst case: we have to cross over the width of the tree to find the rightmost node
     * this can be loosely bounded to O(n)
     */
    Node* get_next_node(Node* root) {
        if (root == NULL)
            return NULL;
        if(root->left != NULL)
            return root->left;
        if(root->right != NULL)
            return root->right;
        // if this node doesn't has any child, then search for its next node until
        // we find a child node or until the next node is NULL
        // ex: [1,2,3,4,5,null,6,7,null,null,null,null,8]
        // in this case, we can let 7 points to 8
        return get_next_node(root->next);
    }
};
