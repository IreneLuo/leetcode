#include <stack>
class Solution {
  public:
/* Problem: Compute Buildings With A Sunset View (not in Leetcode)
 * We are given an array buildings of integers.
 * Each item represents the height of a building
 * on a skyline from left to right.
 * Details:
 * 1. The sun sits on the far left
 * 2. A building is "blocked" from seeing the sun if there is a building
 *    to its left that is >= in height than itself
 *
 * Solution: 
 * We use a stack to save the history of building height from right to left
 * We compare the height of current building(A) with the height of buildings
 * to its right (B).
 * location: A,B1,B2.... --> so if A > B, A will block the view of B
 * If A < B, it means A won't block the view of B
 * --> push A into the stack
 * If A >= B, it means A will block the view of B
 * --> pop B, keep compare the next B with A until we find A < B or
 *     the stack becomes empty.
 * In this way, we will make sure that all the elements in the stack that
 * the item on the top won't block the item on the bottom
 */
    vector<int> getBuildingsWithAView(vector<int>& buildings) {
      stack<int> unblock_stack;
      vector<int> ans;

      if (buildings.size() == 0)
        return ans;

      for (int i = buildings.size() - 1; i >= 0; i--) {
        while(!unblock_stack.empty() &&
              buildings.at(i) >= buildings.at(unblock_stack.top())) {
          cout << "pop this block item " << unblock_stack.top()<<endl;
          unblock_stack.pop();
        }
        unblock_stack.push(i);
        cout << "stack push: " << unblock_stack.top()<<endl;
      }

    while(!unblock_stack.empty()) {
      int temp = unblock_stack.top();
      ans.push_back(temp);
      unblock_stack.pop();
    }
      return ans;
    }
};
