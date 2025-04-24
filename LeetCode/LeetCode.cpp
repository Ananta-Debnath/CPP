#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        int countCompleteSubarrays(vector<int>& nums) {
            unordered_map<int, int> freq_map;
            for (int num : nums) freq_map[num]++;

            int l = nums.size(), start, end;
            for (int i = 0; i < l; i++)
            {
                if (freq_map[nums[i]] == 1)
                {
                    start = i;
                    break;
                }
                freq_map[nums[i]]--;
            }

            for (int i = l-1; i > start; i--)
            {
                if (freq_map[nums[i]] == 1)
                {
                    end = l - i - 1;
                    break;
                }
                freq_map[nums[i]]--;
            }

            
        }
    };