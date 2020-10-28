/* Question on backtobackswe.com: The most visited pages problem
 * let's thing about some points:
 *  - millions/billions of "visits" --> we need a structure to hold these data like heap, BST or hash tbl
 *  - topk() --> a special ordering structure
 *  - optimize for multiple calls in parallel
 *  - fits in RAM
 * So now we have 2 options
 * 1. Heap: build a min heap and push/pop the items to keep the heap in size k
 *     - time complexity = O(klogn)
 *     - space complexity = O(n)
 * 2. BST(Height-Balanced)
 *    We don't want an unbalanced tree because that might lead to a linear time not a log time.
 *    n is the count of distinct pages.
 *     - space : O(n)
 *     - Inorder Traversal Time: O(n)
 *     - topk time: O(logn+k) = O(k)
 *       we will reverse an inorder traversal (right/n/left) to get the top k items
 *       ex:  10      if k = 3, top 3 = [30,20,15]
 *           /  \     so for climb down 10->30 we need logn, for top k items we need O(k)
 *          0   20    
 *         / \  / \
 *       -5 5  15 30
 * Summary:
 *  In this problem, the input are unlimited, so we want to keep all the data in our database.
 *  Hence, we use BST w/hash table to solve it.
 *  Another way (heap) will be at 347_top_k_frequent_element_2.cpp because the input in leetcode
 *  is different(a vector) so it's better to use heap to solve it.
 */
struct NODE {
        int id;
        int count;
        NODE* left;
        NODE* right;
        NODE(int x): id(x), count(1),left(NULL), right(NULL) {};
};

    /* solution 1: BST w/ Hashmap
     *
     */
class Solution {
public:
    NODE* root = NULL;
    unordered_map<int, NODE*> map;
    /* Compare each node's count first. If counts are equal, then compare id.
     * Note) At first, if counts are equal, I put the node to the left side.
     *       i.e. if(target->count<=subtree->count) goto subtree->left
     *       So, I expected that the node which has a same count could keep on the left side.
     *       But the fact is that this rule could be broken.
     *       ex: [3:2]      If I have to remove [1:1], [5:2] must be placed at [1:1]'s location,
     *            /         since [5:2] is the smallest pair in [1:1] right subtree.
     *         [1:1]        In next iteration, if I have to remove [2:2], the process will fail,
     *          / \         because I expected that [2:2] would be in [5:2] left subtree,
     *       [4:1] [2:2]         [3:2]  so the process would keep looking into left subtree,
     *              /    -->      /      and cannot find [2:2] forever
     *           [5:2]         [5:2]
     *                          / \
     *                       [4:1][2:2]
     */ 
    int compare(NODE* target, NODE* subroot){
        if(target->count < subroot->count)
            return 1;
        else if(target->count > subroot->count)
            return 2;
        else{
            if(target->id < subroot->id)
                return 1;
            else if(target->id > subroot->id)
                return 2;
            else
                return 0;
        }
    }
    NODE* _addToBST(NODE* subroot, NODE* target){
        if(subroot == NULL)
            return target;
        if(compare(target, subroot) == 1)
            subroot->left = _addToBST(subroot->left, target);
        else if (compare(target, subroot) == 2)
            subroot->right = _addToBST(subroot->right, target);
        else
            cout<<"_addToBST fail"<<endl;
        return subroot;
    }
    void addToBST(NODE* target){
        if(root == NULL){
            root = target;
            return;
        }
        _addToBST(root, target);
    }
    void clearTheNode(NODE* node){
        if(node == NULL)
            return;
        node->left = NULL;
        node->right = NULL;
    }
    NODE* findMin(NODE* node){
        if(node == NULL)
            return NULL;
        if(node->left == NULL)
            return node;
        return findMin(node->left);
    }
    NODE* _removeFromBST(NODE* subroot, NODE* target){
        if(compare(target, subroot) == 1){
            subroot->left = _removeFromBST(subroot->left, target);
        }else if(compare(target, subroot) == 2){
            subroot->right = _removeFromBST(subroot->right, target);
        }else{
            if(subroot->left == NULL){
                NODE* childOfTarget = subroot->right;
                clearTheNode(subroot);
                return childOfTarget;
            }else if(subroot->right == NULL){
                NODE* childOfTarget = subroot->left;
                clearTheNode(subroot);
                return childOfTarget;
            }else{
                NODE* oldSubroot = subroot;
                NODE* newSubroot = findMin(subroot->right);
                subroot = newSubroot;
                newSubroot->right = _removeFromBST(oldSubroot->right, newSubroot);
                newSubroot->left = oldSubroot->left;
                clearTheNode(oldSubroot);
            }
        }
        return subroot;
    }
    void removeFromBST(NODE* target){
        //if only 1 node in the BST, we need to return NULL
        root = _removeFromBST(root, target);
    }
    void insert(int id){
        NODE* node;
        if(map.find(id) != map.end()){
            node = map.at(id);
            removeFromBST(node);
            node->count++;
        }else{
            node = new NODE(id);
            map.insert(pair<int, NODE*>(id, node));
        }
        addToBST(node);
    }
    void _findkmost(NODE* subroot, int& k, vector<int>& ans){
        if(subroot == NULL)
            return;
        _findkmost(subroot->right, k, ans);
        if(k != 0){
            ans.push_back(subroot->id);
            k--;
        }
        if(k == 0)
            return;
        _findkmost(subroot->left, k, ans);
    }
    void findkmost(int k, vector<int>& ans){
        _findkmost(root, k, ans);
    }
    void print(NODE* subroot){
        if(subroot == NULL)
            return;
        print(subroot->left);
        cout<<subroot->id<<",";
        print(subroot->right);
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> ans;
        //build a BST and create a hashmap that links to each node
        for(int i = 0; i < nums.size(); i++)
            insert(nums[i]);
        //print BST
        //print(root);
        //find the k most frequent elements
        findkmost(k, ans);
        return ans;
    }
};
