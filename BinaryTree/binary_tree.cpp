/* Implement some basic operations of a binary tree:
 *	- void Levelorder_Construct(stringstream& ss): construct a binary tree
 *	- void Insert_Levelorder(char ch): insert a node into a binary tree in an level order
 *	- TreeNode* leftmost(TreeNode* curr): find the leftmost node under current node
 *	- TreeNode* Inorder_Successor(TreeNode* curr): find the next successor
 *	- void Inorder_by_Parent(): inorder traverse the tree by finding its successor
 *	- TreeNode* rightmost(TreeNode* curr);
 *	- TreeNode* Inorder_Predecessor(TreeNode* curr);
 *	- void Inorder_Reverse();
 * Reference:
 * http://alrightchiu.github.io/SecondRound/binary-tree-traversalxun-fang.html
 */
#include <iostream>
#include <sstream>
#include <queue>
using namespace std;
struct TreeNode{
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	char data;
	TreeNode(): data('x'), left(nullptr), right(nullptr), parent(nullptr) {};
	TreeNode(char c): data(c), left(nullptr), right(nullptr), parent(nullptr) {};
};
class BinaryTree{
private:
	TreeNode* root;
public:
	BinaryTree(): root(nullptr) {};
	BinaryTree(const char* ch);
	void Levelorder_Construct(stringstream& ss);
	void Insert_Levelorder(char ch);
	TreeNode* leftmost(TreeNode* curr);
	TreeNode* Inorder_Successor(TreeNode* curr);
	TreeNode* rightmost(TreeNode* curr);
	TreeNode* Inorder_Predecessor(TreeNode* curr);
	void Inorder_by_Parent();
	void Inorder_Reverse();
};
BinaryTree::BinaryTree(const char* ch){
	stringstream ss;
	ss<<ch;
	root = new TreeNode();
	ss>>root->data;
	cout<<"construct tree: root= "<<root->data<<endl;
	Levelorder_Construct(ss);
}
void BinaryTree::Levelorder_Construct(stringstream& ss){
	queue<TreeNode*> q;
	TreeNode* curr = root;
	char data = 'x';
	while(ss>>data){
		if(data >= 'a' && data <= 'z'){
			TreeNode* child = new TreeNode(data);
			child->parent = curr;
			curr->left = child;
			q.push(child);
		}
		//operand priority ! > >>, so add ()
		if(!(ss>>data))
			break;
		if(data >= 'a' && data <= 'z'){
			TreeNode* child = new TreeNode(data);
			child->parent = curr;
			curr->right = child;
			q.push(child);
		}
		curr = q.front();
		q.pop();
	}
}
/* Insert the nodes in level order.
 */
void BinaryTree::Insert_Levelorder(char ch){
	queue<TreeNode*> q;
	TreeNode* curr = root;
	while(curr){
		if(curr->left){
			q.push(curr->left);
		}else{
			TreeNode* node = new TreeNode(ch);
			node->parent = curr;
			curr->left = node;
			break;
		}
		if(curr->right){
			q.push(curr->right);
		}else{
			TreeNode* node = new TreeNode(ch);
			node->parent = curr;
			curr->right = node;
			break;
		}
		curr = q.front();
		q.pop();
	}
}
TreeNode* BinaryTree::leftmost(TreeNode* curr){
	while(curr->left != nullptr)
		curr = curr->left;
	return curr;
}
TreeNode* BinaryTree::Inorder_Successor(TreeNode* curr){
	//if curr has a right child, find the leftmost node of its right subtree
	if(curr->right)
		return leftmost(curr->right);
	//if curr doesn't has a right child, seek its ancestor
	TreeNode* successor = curr->parent;
	while(successor && curr == successor->right){
		curr = successor;
		successor = curr->parent;
	}
	return successor;
}
TreeNode* BinaryTree::rightmost(TreeNode* curr){
	while(curr->right != nullptr)
		curr = curr->right;
	return curr;
}
TreeNode* BinaryTree::Inorder_Predecessor(TreeNode* curr){
	if(curr->left)
		return rightmost(curr->left);
	TreeNode* predecessor = curr->parent;
	while(predecessor && curr == predecessor->left){
		curr = predecessor;
		predecessor = curr->parent;
	}
	return predecessor;
}
void BinaryTree::Inorder_by_Parent(){
	//find the leftmost node of root
	TreeNode* curr = leftmost(root);
	//keep finding the successor of curr
	while(curr){
		cout<<curr->data<<" ";
		curr = Inorder_Successor(curr);
	}
	cout<<endl;
}

void BinaryTree::Inorder_Reverse(){
	TreeNode* curr = rightmost(root);
	while(curr){
		cout<<curr->data<<" ";
		curr = Inorder_Predecessor(curr);
	}
	cout<<endl;
}

int main(void){
	const char* data = "abcdefXXXghXi";
	cout<<"input: "<<data<<endl;
	BinaryTree bt(data);
	bt.Inorder_by_Parent();

	bt.Insert_Levelorder('k');
	bt.Insert_Levelorder('l');
	bt.Insert_Levelorder('m');
	bt.Insert_Levelorder('n');
	bt.Inorder_by_Parent();

	bt.Inorder_Reverse();
	return 0;
}
