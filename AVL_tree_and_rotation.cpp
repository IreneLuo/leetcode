#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct avlnode {
      int val;
      int height;
      int balanced;
      struct avlnode* left;
      struct avlnode* right;
      avlnode(int x, int h, int b): val(x), height(h), balanced(b), left(NULL), right(NULL) {}
};
struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
	TreeNode(int v): val(v), left(NULL), right(NULL) {}
};
class Solution {
  public:
    /* solution:
     * Note> A binary search tree which the balanced value of its left child and right child
     *       is smaller or equal to 1 is an AVL Tree
     *       A balanced value  = Height(left) - Height(right)
     * 1. create root node
     * 2. create each node in items
     *    a. call a recursive function to create left child and right child node
     *    b. calculate the height of itself (by using the height of children)
     *    c. calculate the balanced value of itself
     *    d. according to the balanced value decide to rotate the tree or not
     *       d.1> if balanced value > threshold, it means current tree is a left-heavy tree
     *            (1) if the balanced value(root's left child) >= 0 --> do a right rotate
     *            (2)                                          < 0 --> do a left-right rotate
     *
     *      case d.1.1) right rotate (3-2)       d.1.2) left-right rotate (1-2->3-2)
     *          3 (balance) = 1-(-1) = 2         3 (balance) = 1-(-1) = 2
     *         /                                /
     *       2 (balance) = 0-(-1) = 1          1 (balance) = (-1) - 0 = -1
     *      /                                  \                      
     *    1                                     2
     *
     *       d.2> if balanced value < -threshold, it means current tree is a right-heavy tree
     *            (1) if the balanced value(root's right child) <= 0 --> do a left rotate
     *            (2)                                           > 0 --> do a right-left rotate
     *
     *      case d.2.1) left rotate(1-2)        d.2.2)
     *         1 (balance) = -1 - 1 = -2          1 (balance) = -1 - 1 = -2
     *          \                                  \
     *           2 (balance) = (-1) - 0 = -1        3 (balance) = 0 - (-1) 1
     *            \                                /
     *             3                              2
     */

    TreeNode* insertAVL(vector<int>& items, int threshold) {
      if (items.size() == 0)
        return NULL;

      // create the first node
      struct avlnode* root = new struct avlnode(items.at(0), -1, 0);
      for(int i = 1; i < items.size(); i++)
        root = insert(root, items.at(i), threshold);

      return convert_avlnode_to_treenode(root);
    }

    int get_avl_height(struct avlnode* node){
	    if(node == NULL)
		    return -1;
	    return node->height;
    }

    enum ROTATE_TYPE{
		RIGHT,
		LEFT,
		LEFTRIGHT,
		RIGHTLEFT,
    };

    struct avlnode* insert(struct avlnode* root, int key, int threshold){
      if (root == NULL) {
          return new struct avlnode(key, 0, 0);
      }
      if(key <= root->val)
        root->left = insert(root->left, key, threshold);
      else
        root->right = insert(root->right, key, threshold);
 
      root->height = max(get_avl_height(root->left), get_avl_height(root->right)) + 1;
      root->balanced = get_avl_height(root->left) - get_avl_height(root->right);

      if (root->left != NULL){
        cout<<"root="<<root->val<<" insert a left node "<<root->left->val;
        cout<<", root(h,b) =  "<<root->height<<", "<<root->balanced<<endl;
      }
      if (root->right != NULL){
        cout<<"root="<<root->val<<" insert a right node "<<root->right->val;
        cout<<", root(h,b) =  "<<root->height<<", "<<root->balanced<<endl;
      }
 
      //left-heavy tree
      if(root->balanced > threshold){
        if(root->left->balanced >= 0)
          root = rotate(RIGHT, root);
        else
          root = rotate(LEFTRIGHT, root);
      }else if(root->balanced < -threshold){
        if(root->right->balanced <= 0)
          root = rotate(LEFT, root);
        else
          root = rotate(RIGHTLEFT, root);
      }
      return root;
    }

    struct avlnode* rotate(int type, struct avlnode* root){
      int type_to_int;
      struct avlnode* ans = NULL;
      struct avlnode* templeft = NULL;
      struct avlnode* tempright = NULL;
      
      cout << "--rotate "<<type<<endl;

      switch(type) {
        case RIGHT:
          templeft = root->left;
          root->left = templeft->right;
          templeft->right = root;
      	  root->height = max(get_avl_height(root->left), get_avl_height(root->right)) + 1;
      	  templeft->height = max(get_avl_height(templeft->left), get_avl_height(templeft->right)) + 1;
          ans = templeft;
          break;
        case LEFT:
          tempright = root->right;
          root->right = tempright->left;
          tempright->left = root;
      	  root->height = max(get_avl_height(root->left), get_avl_height(root->right)) + 1;
      	  tempright->height = max(get_avl_height(tempright->left), get_avl_height(tempright->right)) + 1;
          ans = tempright;
          break;
        case LEFTRIGHT:
          root->left = rotate(LEFT, root->left);
          ans = rotate(RIGHT, root);
	  break;
        case RIGHTLEFT:
          root->right = rotate(RIGHT, root->right);
          ans = rotate(LEFT, root);
          break;
        default:
          break;
      }
      return ans;
    }
 
    TreeNode* convert_avlnode_to_treenode(struct avlnode* avlroot){
      if(avlroot == NULL)
        return NULL;
      TreeNode* root = new TreeNode(avlroot->val);
      cout<<"node= "<<root->val<<endl;
      root->left = convert_avlnode_to_treenode(avlroot->left);
      root->right = convert_avlnode_to_treenode(avlroot->right);
      return root;
    }
};

int main(void){
	Solution sol;
	//int input_raw[] = {3,2,1};//case left
	//int input_raw[] = {1,2,3};//case right
	//int input_raw[] = {3,1,2};//case left-right
	int input_raw[] = {2,3,1};//case right-left
	
	int input_size = 3;
	//vector<int> input (input_raw, sizeof(input_raw)/sizeof(int));
	vector<int> input;
	for (int i = 0; i < input_size; i++)
		input.push_back(input_raw[i]);
	int threshold = 1;
	TreeNode* root = sol.insertAVL(input, threshold);
	return 0;
}
