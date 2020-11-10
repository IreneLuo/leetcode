using namespace std;
class Solution {
  private:
    int GAP_COST = 1;
    std::map<std::string, int> alignment_costs;

    // initialize alignment costs
    void init() {
      alignment_costs.insert(std::pair<std::string, int> ("AA", 0));
      alignment_costs.insert(std::pair<std::string, int> ("CC", 0));
      alignment_costs.insert(std::pair<std::string, int> ("GG", 0));
      alignment_costs.insert(std::pair<std::string, int> ("TT", 0));

      /*
        Costs arbitrarily chosen. Symmetry shouldn't guarantee same alignment cost because
        character 1 is from s1 and character 2 is from s2. So "AC" could theoretically cost
        more (or less) to align than "CA".
      */
      alignment_costs.insert(std::pair<std::string, int> ("AC", 1));
      alignment_costs.insert(std::pair<std::string, int> ("CA", 1));

      alignment_costs.insert(std::pair<std::string, int> ("AG", 2));
      alignment_costs.insert(std::pair<std::string, int> ("GA", 2));

      alignment_costs.insert(std::pair<std::string, int> ("AT", 4));
      alignment_costs.insert(std::pair<std::string, int> ("TA", 4));

      alignment_costs.insert(std::pair<std::string, int> ("CG", 3));
      alignment_costs.insert(std::pair<std::string, int> ("GC", 3));

      alignment_costs.insert(std::pair<std::string, int> ("CT", 5));
      alignment_costs.insert(std::pair<std::string, int> ("TC", 5));

      alignment_costs.insert(std::pair<std::string, int> ("GT", 1));
      alignment_costs.insert(std::pair<std::string, int> ("TG", 1));
    };

  public:
    Solution() {
      init();
    };

    /* solution
     * for characters s1[i] and s2[j], we suppose the minimum cost = opt(i,j)
     * Therefore opt(i, j) = min(
     *                  //map.at(s1[i]s2[j]) = alignment cost for s1[i], s2[j]
     *                  //opt(i-1, j-1) = the min cost for the rest of parts(the substrings exclude s1[i] & s2[j])
     *                  alignment cost = map.at(s1[i]s2[j]) + opt(i-1, j-1),
     *
     *                  //add a gap in s1 (so we compare a gap with s2[j])
     *                  //then we have to compare the rest parts: s1[0..i] and s2[0..j-1]
     *                  mismatch i cost = GAP_COST + opt(i, j-1),
     *
     *                  //add a gap in s2
     *                  //and we have to compare s1[0..i-1] and s2[0..j]
     *                  mismatch j cost = GAP_COST + opt(i-1, j),
     *                    )
     * ex: s1 = "ACG", s2 = "AACG"
     *   history tbl =  s2  " " A  A  C  G      1. tbl[0][0-4]/tbl[0-3][0] = GPT_COST * col because when s1 = " ",
     *                  s1  --------------      we can only put the gaps in s1
     *                 " " | 0  1  2  3  4      2. ex: tbl[1][1] = min(0,2,2)=0
     *                  A  | 1  0  1  2  3           - align = "AA"--> 0 + tbl[0][0] = 0
     *                  C  | 2  1  1  1  2           - mis1 =  1 + tbl[1][0] = 2
     *                  G  | 3  2  2  2  1             --> if s1=GAP s2=A, so the rest of s1 = A, s2="" = tbl[1][0]
     *      --> the ans = tbl[G][G] = 1              - mis2 =  1 + tbl[0][1] = 2
     *                                                 --> if s2=GAP s1=A, so the rest of s1 = "", s2=A = tbl[0][1]
     *
     *   How can we trace back to know the exact possible DNA sequence?
     *   s2  " " A  A  C  G 
     *   s1  --------------
     *   " " | [0]  1  2  3  4  --> (5)
     *    A  | 1 [0] [1]  2  3  --> (3,4)
     *    C  | 2  1  1 [1]  2  --> (2)
     *    G  | 3  2  2  2 [1]  --> (1) if we take the alignment penalty, the align cost = 0("GG") + tbl[i-1][j-1] = 1
     *                                 if we mismatch s1, add a gap in s2, the cost = 1(GAP) + tbl[i-1][j] = 3
     *                                 if we mismatch s2, add a gap in s1, the cost = 1(GAP) + tbl[i][j-1] = 3
     *                                 ==> 1 is the min so we go to tbl[i-1][j-1]
     *                                     s1=G s2=G
     *                             (2) align cost = 0("CC") + tbl[i-1][j-1] = 1
     *                                 if we mismatch s1, add a gap in s2, the cost = 1(GAP) + tbl[i-1][j] = 3
     *                                 if we mismatch s2, add a gap in s1, the cost = 1(GAP) + tbl[i][j-1] = 2
     *                                 ==> 1 is the min so we go to tbl[i-1][j-1]
     *                                     s1=CG s2=CG
     *                             (3) align cost = 0("AA") + tbl[i-1][j-1] = 1
     *                                 if we mismatch s1, add a gap in s2, the cost = 1(GAP) + tbl[i-1][j] = 3
     *                                 if we mismatch s2, add a gap in s1, the cost = 1(GAP) + tbl[i][j-1] = 1
     *                                 ==> we choose to add a gap in s1 so we go to tbl[i][j-1]
     *                                     s1=_CG s2=ACG
     *                             (4) align cost = 0("AA") + tbl[i-1][j-1] = 0
     *                                 if we mismatch s1, add a gap in s2, the cost = 1(GAP) + tbl[i-1][j] = 2
     *                                 if we mismatch s2, add a gap in s1, the cost = 1(GAP) + tbl[i][j-1] = 2
     *                                 ==> we choose to align AA so we go to tbl[i-1][j-1]
     *                                     s1=A_CG s2=AACG
     *                             (5) here's the end, so our s1 = A_CG, s2=AACG
     */
    int minCostAlignment(std::string s1, std::string s2) {
      int s1_len = s1.size();
      int s2_len = s2.size();
      int history[s1_len+1][s2_len+1];
      for(int row = 0; row <= s1_len; row++)
        history[row][0] = row * GAP_COST;
      for(int col = 0; col <= s2_len; col++)
        history[0][col] = col * GAP_COST;
      for(int row = 1; row <= s1_len; row++){
        for(int col = 1; col <= s2_len; col++){
          string pattern = s1.substr(row-1, 1) + s2.substr(col-1, 1);
          int alignCost = alignment_costs.at(pattern) + history[row-1][col-1];
          int mismatchS1Cost = GAP_COST + history[row][col-1];
          int mismatchS2Cost = GAP_COST + history[row-1][col];
          history[row][col] = min(alignCost, min(mismatchS1Cost, mismatchS2Cost));
        }
      }
      return history[s1_len][s2_len];
    };
};

