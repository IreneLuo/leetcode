class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {

/* Solution 1: Find the first item whose price is less than or equal to itself.
 *           Time  complexity: O(n^2)
 *           Space complexity: O(1)
 *           Best  case: O(n)   [9,8,7,6,5]
 *           Worst case: O(n^2) [5,6,7,8,9]
 */
/*
        int pricesSize = prices.size();
        for (int i = 0; i < pricesSize; i++){
            for (int j = i+1; j < pricesSize; j++){
                if (prices[j] <= prices[i]){
                    prices[i] -= prices[j];
                    break;
                }
            }
        }
*/

/* Solution 2.1: Use "Monotonic Stack" to get the Next Small Number.
 *             If there's an item smaller than more than two items
 *             in the middle, then we can use this method to save time.
 *             
 *             Concept: 
 *             push the items until we find a smaller one,
 *             then pop the item in the stack to compare.
 *             
 *             time complexity: O(n) 1push+1pop
 *             space complexity: O(n)
 */       
        stack <int> s;
        for (int i = 0; i < prices.size(); i++){
             //if we access stack s before checking whether is's empty or not,
             // we'll get a runtime error 
            while (!s.empty() && (prices[s.top()] >= prices[i])){
                prices[s.top()] -= prices[i];
                s.pop();
            }
            s.push(i);
        }
    
/* solution 2.2: based on 2.1, but use pointers
        stack<int*> s;
        for (int &p:prices){          
            while (!s.empty() && (*s.top() >= p)){
                *s.top() -= p;
                s.pop();
            }
            s.push(&p);
        }
*/
        return prices;
    }
};
