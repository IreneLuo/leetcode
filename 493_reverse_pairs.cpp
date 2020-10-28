class Solution {
public:
    /* Solution: QuickSort
     *
     */
    int reversePairs(vector<int>& nums) {
        return mergesort(nums, 0, nums.size()-1);
    }
    int mergesort(vector<int>& input, int start, int end){
      //the bottom case like one node only, ex: [1]
      if(start >= end)
        return 0;

      int mid = start + (end - start)/2;
      int inversion = 0;
      //split to left and right part
      inversion += mergesort(input, start, mid);
      inversion += mergesort(input, mid+1, end);

      int i = start;
      int j = mid + 1;
      //each time we compare one item in i with all the items in j.
      //when we find a j that input[i] > 2 * input[j] then we start j++ until the condition fails, then calculate the inversion
      // ex: [a,b,c] [d,e,f] --> we set i = 0, j = 3
      // if b > 2d then j+1 = 4
      // if b > 2e then j+1 = 5
      // if b < 2f then while loop stop, inversion = j - (mid + 1) = 5-(2+1) = 2
      for(i = start; i <= mid; i++){
          // signed integer overflow when 2 * 2147483647, so we use 2LL(longlong) to avoid this problem
          while(j <= end && (input[i] > 2LL * input[j]))
              j++;
          inversion += j - (mid + 1);
      }
      //merge the left and the right part
      merge(input, start, mid, end);
      return inversion;         
    }

    void merge(vector<int>& input, int start, int mid, int end){
      int i = start;
      int j = mid + 1;
      // store the items after comparing
      vector<int> temp;
      // compare the item in the left and the right part
      while(i <= mid && j <= end){
        if (input[i] > input[j])
            temp.push_back(input[j++]);
        else
            temp.push_back(input[i++]);
      }
      //push back the rest of left or right part
      //note that only one while will be executed here.
      while(i <= mid)
        temp.push_back(input[i++]);
      while(j <= end)
        temp.push_back(input[j++]);

      // update input to a sorted status
      for(int q = start; q <= end; q++)
        input[q] = temp[q - start];
    }
};
