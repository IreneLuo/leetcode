class Solution {
    /* solution : min-Heap + set
     * Goal:
     *   - find an server (server = i % k)
     *      - vector: O(1)
     *      - treeset: O(logk)
     *   - if this server is not available, check the next one
     *      - vector: O(k)
     *      - treeset: O(logk)
     *   ==> so we decide to use a treeset the track the servers
     *   ==> and we use a heap to track the server's progress(Has this
     *       server finished its work at this time?)
     *       key, value = release time(arrival+load), id
     * Implement:
     *   1. Initialize
     *         - push all the servers into the set
     *   2. Iterate over the arrival time of requests
     *         1. for time = t, release all the server in the heap that
     *            (server release time <= t) (add them to the set)
     *         2. use i%k to choose a server from the set
     *         3. recalculate the release time of this server and push it
     *            into the heap
     *         4. if there's no server in the set, drop this request
     *            since all servers are unavailable
     *
     * time complexity = O(nlogk)
     * space complexity = O(k)
     *
     * Example: k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3] 
     *
     *  request arrival load   pq                  set
     *                                          [1,2,3] //init
     *     0      1      5    [6,1]             [2,3]   //server 1 handle rq 0
     *     1      2      2    [4,2][6,1]        [3]     //server 2 handle rq 1
     *     2      3      3    [4,2][6,1][6,3]   []      //server 3 handle rq 2
     *     3      4      3    [7,2][6,1][6,3]   []      //note 1
     *     4      5      3    [7,2][6,1][6,3]   []      //arrival=5 > all the 
     *                                                  finished time in heap,
     *                                                  so drop it
     *                                                  (no one is available)
     *                                                    
     *   note 1) time=4, we know that server 2 has just finished its work 
     *           (pq.top.first=4), so we pop out [4,2] and push server 2 into
     *           the set. Now, we only have server 2 to handle request 3
     *           so we calculate the finished time = 4+3=7 for server 2 to
     *           finish request 3 and push it to the heap
     */
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        //a min-Heap
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> count(k);
        set<int> available_servers;
        //init O(k)
        for(int i = 0; i < k; i++)
            available_servers.insert(i);
        //iterate over the requests
        // for loop: O(n)
        // heaify: O(logk)
        for(int r = 0; r < arrival.size(); r++){
            int arrive = arrival[r];
            int cost = load[r];
            while(!pq.empty() && pq.top().first <= arrive){
                available_servers.insert(pq.top().second);
                pq.pop();
            }
            //if all servers are unavailable, drop the request
            if(available_servers.empty())
                continue;
            //find a server by using r % k
            //lower_bound() returns an idx of server that >= r % k
            //so this meets the requirement in this question
            //that if (r % k)-th server is busy choose the next one
            set<int>::iterator it = available_servers.lower_bound(r % k);
            if(it == available_servers.end())
                it = available_servers.begin();
            pq.emplace(arrive + cost, *it);
            count[*it]++;
            available_servers.erase(it);
        }
        //find the bussiest servers O(k)
        //max_element() returns the max item in this vector
        //but we still need to add * to reference it
        const int max = *max_element(begin(count), end(count));
        vector<int> ans;
        for(int i = 0; i < count.size(); i++){
            if(count[i] == max)
                ans.push_back(i);
        }
        return ans;
    }
};
