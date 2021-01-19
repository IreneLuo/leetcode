class Solution {
    /* solution: hash + sort
     *  1. build a hashtbl key-val = char-count
     *  2. sort the string by comparing the count in the hashtbl
     * time complexity = O(nlogn)
     *   - access hashtbl = O(1)
     *   - sorting: O(nlogn)
     * space complexity = O(n)
     */
public:
/*  error: invalid use of non-static data member 'map'
    unordered_map<char, int> map;
    struct mycompare{
        bool operator()(char a, char b){
            return (map[a] > map[b]) || (map[a] == map[b] && a > b);
        }
    };
*/
/*
    string frequencySort(string s) {
        unordered_map<char, int> map;
        for(auto ch: s) ++map[ch];
        sort(s.begin(), s.end(), [&map](char a, char b){
            return (map[a] > map[b]) || (map[a] == map[b] && a > b);
        });
        return s;
    }
*/
    /* solution: hash + sort (faster than solution 1)
     *  1. use vector instead of unordered_map for the hashtbl
     *  2. sort the vector(freq-char) inseatd of sorting the input
     * time complexity = O(nlogn)
     * space complexity = O(n)
     *
     * Comparison of each container: see HuaHua's video
     * https://www.youtube.com/watch?v=qdpBD0LFgN0&list=PLLuMmzMTgVK49Hph4vV8DAzGZpj4azwmz&index=33
     */
    string frequencySort(string s) {
        //since the ascii code of the biggest alphabet is 127,
        //so we use 128 as size of map
        vector<int> map(128, 0);
        //count the frequency of each character in the string
        for(auto ch: s) ++map[ch];
        //collect the freq and char of those characters that appear in the string
        vector<pair<int, char>> sorted_map;
        for(int i = 0; i < 128; i++)
            if(map[i] > 0) sorted_map.emplace_back(map[i], i);
        //sort the vector by rbegin() and rend()
        //the vector will be sorted in descendent order
        sort(sorted_map.rbegin(), sorted_map.rend());
        string ans;
        //fill it->first times of item it->second
        //ex: append(3, 'c') --> append ccc
        for(auto it: sorted_map)
            ans.append(it.first, it.second);
        return ans;
    }
};
