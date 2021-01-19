/* Implement a binary search tree
 * Reference:
 * http://alrightchiu.github.io/SecondRound/treeshu-introjian-jie.html
 * Delete(): 450. Delete Node in a BST
 * Insert(): 701. Insert into a Binary Search Tree
 */
#include <iostream>
using namespace std;
struct TreeNode{
	int key;
	int val;
	TreeNode* parent;
	TreeNode* left;
	TreeNode* right;
	TreeNode(): key(0), val(0), parent(nullptr), left(nullptr), right(nullptr){};
	TreeNode(int k, int v): key(k), val(v), parent(nullptr), left(nullptr), right(nullptr){};
};
class BinarySearchTree{
private:
	TreeNode* root;
	TreeNode* leftmost(TreeNode* curr);
	TreeNode* successor(TreeNode* curr);
public:
	BinarySearchTree(): root(nullptr){};
	TreeNode* search(int key);
	TreeNode* _insert(TreeNode* root, int key, int val);
	void insert(int key, int val);
	void _inorder_print(TreeNode* root);
	void inorder_print();
	TreeNode* get_the_smallest_node_in_right_subtree(TreeNode* root);
	TreeNode* _delete_node(TreeNode* root, int key);
	int delete_node(int key);
};
TreeNode* BinarySearchTree::leftmost(TreeNode* curr){
	TreeNode* p = curr;
	while(p->left)
		p = p->left;
	return p;
}
TreeNode* BinarySearchTree::successor(TreeNode* curr){
	if(curr->right)
		return leftmost(curr->right);
	TreeNode* successor = curr->parent;
	while(successor && curr == successor->right){
		curr = successor;
		successor = curr->parent;
	}
	return successor;
}
TreeNode* BinarySearchTree::search(int key){
	TreeNode* curr = root;
	while(curr){
		if(key < curr->val)
			curr = curr->left;
		else if(key > curr->val)
			curr = curr->right;
		else
			return curr;
	}
	return nullptr;
}
TreeNode* BinarySearchTree::_insert(TreeNode* root, int key, int val){
	if(!root)
		return new TreeNode(key, val);
	if(key < root->val){
		root->left = _insert(root->left, key, val);
		root->left->parent = root;
	}else{
		root->right = _insert(root->right, key, val);
		root->right->parent = root;
	}
	return root;
}
void BinarySearchTree::insert(int key, int val){
	//TODO: why I have to get the return answer from insert to print out root val?
	//_insert(root, key, val);
	root = _insert(root, key, val);
}
/* We use recursive function to implement inorder traversal.
 */
void BinarySearchTree::_inorder_print(TreeNode* root){
	if(root){
		_inorder_print(root->left);
		cout<<root->val<<" ";
		_inorder_print(root->right);
	}
}
void BinarySearchTree::inorder_print(){
	/* way1: inorder traversal */
	_inorder_print(root);
	cout<<" / ";
	/* way2: find successor */
	TreeNode* curr = leftmost(root);
	while(curr){
		cout<<curr->val<<" ";
		curr = successor(curr);
	}
}
TreeNode* BinarySearchTree::get_the_smallest_node_in_right_subtree(TreeNode* root) {
        if(root == NULL) return NULL;
        TreeNode* temp = root;
        while(temp->left != NULL)
            temp = temp->left;
        return temp;
}
TreeNode* BinarySearchTree::_delete_node(TreeNode* root, int key){
	if(!root) return nullptr;
	if(key < root->val){
		root->left = _delete_node(root->left, key);
	}else if(key > root->val){
		root->right = _delete_node(root->right, key);
	}else{
		if(!root->left){
			TreeNode* successor = root->right;
			delete(root);
			return successor;
		}else if(!root->right){
			TreeNode* successor = root->left;
			delete(root);
			return successor;
		}else{
			TreeNode* successor = get_the_smallest_node_in_right_subtree(root->right);
			root->key = successor->key;
			root->val = successor->val;
			root->right = _delete_node(root->right, successor->key);
			return root;
		}
	}
	return root;
}
int BinarySearchTree::delete_node(int key){
	if(!_delete_node(root, key)){
		cout<<"delete_node fail: "<<key<<endl;
		return 0;
	}
	return 1;
}
int main(void){
	BinarySearchTree bst;
	cout<<"Construct a binary search tree"<<endl;
	/*   20
	 *  /  \
	 * 10  40
	 *    /  \
	 *   30  60
	 *       /
	 *      50
	 */
	bst.insert(20, 20);
	bst.insert(10, 10);
	bst.insert(40, 40);
	bst.insert(30, 30);
	bst.insert(60, 60);
	bst.insert(50, 50);
	cout<<"Inorder print:";
	bst.inorder_print();
	cout<<endl;
	TreeNode* target = bst.search(50);
	cout<<"Search: "<<target->val<<endl;
	if(bst.delete_node(40)){
		cout<<"Inorder print:(delete 40)";
		bst.inorder_print();
		cout<<endl;
	}
	return 0;
}
