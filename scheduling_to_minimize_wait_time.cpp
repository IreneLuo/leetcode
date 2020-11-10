/* solution: greedy algorithm
 *  -> choose a best(minimum duration) answer in each iteration
 *  We sort the task info with duration
 *  and return the task id.
 *  ex: [3,1,2] --> taskset[2:1, 3:2, 1:3] (id:dur)
 *   when task2 is running, task 1,3 wait 1 + 1 unit time
 *   when task 3 is running, task 1 wait 2 unit time
 *   so total wait time  = 4
 *
 *  time complexity = O(nlogn) //sorting
 *  space complexity = O(n)
 */
class Solution {
  struct TASKINFO{
    int id;
    int dur;
    TASKINFO(int i, int d): id(i), dur(d){};
  };
  public:
    static bool myCompare(TASKINFO* a, TASKINFO* b){
      return a->dur < b->dur;
    }
    vector<int> minimizeWaitTime(vector<int>& tasks) {
      vector<TASKINFO*> taskset;
      vector<int> ans;
      for(int i = 0; i < tasks.size(); i++){
        TASKINFO* taskinfo = new TASKINFO(i+1, tasks[i]);
        taskset.push_back(taskinfo);
      }
      sort(taskset.begin(), taskset.end(), myCompare);
      for(auto& it: taskset){
        ans.push_back(it->id);
      }
      return ans;
    }
};
