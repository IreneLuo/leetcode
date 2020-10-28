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
public:
    /* solution:
     * 1. if left child or right child is not null, then connect it
     * 2. if left child or right child is not null, return null
     * time complexity: O(n) //n calls, each call O(1) --> O(n)
     * space complexity: O(1)
     */
    Node* connect(Node* root) {
        if(root == NULL)
            return root;
        if(root->left != NULL)
            root->left->next = root->right;
        if(root->right != NULL && root->next != NULL)
            root->right->next = root->next->left;
        //keep connecting child node
        root->left = connect(root->left);
        root->right = connect(root->right);
        return root;
    }
};
