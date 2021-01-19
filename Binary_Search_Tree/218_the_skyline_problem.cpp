class Solution {
    /* solution :
     * 
     * Concept:
     *   1. Each building has left, right points, we use these information
     *      to create "Events"
     *      Ex: Building 1 has {x1_left, height} and {x2_left, height} 2 points
     *          Events:{x1_left, h1, entering}, {x1_left, h1, leaving}
     *                   <x>  <height> <type>
     *   2. Sort the "Events" by x
     *   3. Use a data struct "DS" to record the height of those points
     *   4. If a new building is higher than previous top buidling,
     *           add this new building into the skyline
     *      If a building has already been added, remove it and look for the
     *      second highest building.
     *
     *      To implement this, we iterate over all the "Events"
     *      For e in Events:
     *          - if e is entering
     *              if (e.height > DS.max) add {e.x, e.height} into the ans
     *              insert (e.height) into the DS
     *          - if e is leaving
     *              remove (e.height) from the DS
     *              if(e.height > DS.max) add {DS.max}
     * Thinking:
     * What can we use to implement DS()?
     * DS must have those features: find max/insert/delete by key
     *             Heap                BST
     * find max:   O(1)              O(logn)
     * insert  : O(logn)             O(logn)
     * delete  : O(logn)/O(n)        O(logn)
     * for C++ : write by yourself   multiset
     *          (common heap cannot
     *          delete items by key)
     * Here I use BST. For another solution, review HuaHua's tutorial.
     */
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        typedef pair<int, int> events;
        vector<vector<int>> ans;
        vector<events> eventset;
        scanned_building_so_far.clear();
        //build eventset
        for(int i = 0; i < buildings.size(); i++){
            eventset.emplace_back(buildings[i][0], buildings[i][2]);
            eventset.emplace_back(buildings[i][1], -buildings[i][2]);
        }
        /* sort the eventset
         * (x1, h1) (x2,h2)
         * if x1==x2, h2 > h1 -->(x2,h2), (x1, h1)
         * if x1<x2 -->  (x1, h1), (x2,h2)
         * Why sorting?
         * To deal with edge cases like buildings that overlap with each other
         * Ex: For building with same x_left and x_height,
         *      - entering: check the highest one first
         *      - leaving: check the lowest one first
         */
        sort(eventset.begin(), eventset.end(),
             [](const events& e1, const events& e2){
                if(e1.first == e2.first) return e1.second > e2.second;
                return e1.first < e2.first;}
            );

        //iterate over all the events
        for(auto& e: eventset){
            int x = e.first;
            int h = abs(e.second);
            bool entering = (e.second) > 0;
            if(entering){
                if(h > get_heighest_so_far()){
                    vector<int> temp;
                    temp.push_back(x);
                    temp.push_back(h);
                    ans.emplace_back(temp);
                }
                scanned_building_so_far.insert(h);
            }else{
                scanned_building_so_far.erase(
                    scanned_building_so_far.equal_range(h).first);
                if(h > get_heighest_so_far()){
                    vector<int> temp;
                    temp.push_back(x);
                    temp.push_back(get_heighest_so_far());
                    ans.emplace_back(temp);
                }
            }
        }
        return ans;
    }
private:
    multiset<int> scanned_building_so_far;
    int get_heighest_so_far(){
        if (scanned_building_so_far.empty())
            return 0;
        else
            return *scanned_building_so_far.rbegin();
    }
};
