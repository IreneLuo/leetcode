class Solution {
  public:
  /*  time complexity =  O(n^2)
   *  space complexity = O(1)
   */
    int computeSalaryCap(vector<int>& salaries, int budget) {
       // 1. sort the input --> O(nlogn)
       sort(salaries.begin(), salaries.end());
       /* 2. calculate the cap
        *   ex: [100,200,300,400] budget=800
        *     1.             cap = 800 - (100+200+300) = 200
        *                    but 300 > cap which means the cap is wrong, so we calculate again
        *     2.         cap+cap = 800 - (100+200) = 500, so cap = 250
        *                and the rest of items are all < 250, so this cap is the answer!
        */
        int idxOfCap = salaries.size() - 1;
        while(idxOfCap > 0){ //O(n)
        int sum = 0;
          for(int i = 0; i < idxOfCap; i++) //O(n)
            sum += salaries[i];
          // see the description 2 above
          int cap = (budget - sum)/(salaries.size() - idxOfCap);
          if(salaries[idxOfCap-1] <= cap)
            return cap;
          idxOfCap--;
        }
        //if salaries[0] >= the cap we just calculated
        return budget/salaries.size();
    }
};
