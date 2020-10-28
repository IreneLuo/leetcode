// similar to leetcode 395
class Solution {
  public:
    int longestSubstringWithAtMostKDistinctCharacters(string s, int k) {
      int left = 0;
      int right = -1;
      int distinct_char = 0;
      int ans = 0;
      unordered_map<char, int> map;
      int N = s.size();
      
      if(s.size() == 0)
        return 0;

      //note> cannot use s.size() directly, so we store it as N
      while(right < N - 1){
        right++;
        map[s[right]-'a']++; 
        cout<<"count++"<<s[right]<<endl;
  
        if(map[s[right]-'a'] == 1)
          distinct_char++;
  
        // we have to remove all the characters in the front of string
        // until the distinct_char == k
        while(distinct_char > k){
          map[s[left]-'a']--;
          if(map[s[left]-'a'] == 0)
            distinct_char--;
          left++;
        }
        ans = max(ans, right-left+1);
      }
      return ans;
    }
};
