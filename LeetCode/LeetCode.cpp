#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
            vector<int> idx;
            idx.push_back(0);
            int l = nums.size();
            for (int i = 0; i < l; i++)
            {
                if (nums[i] % modulo == k) idx.push_back(i);
            }
            idx.push_back(l-1);

            int l2 = idx.size();
            long long count = 0;
            long long d = 0;

            if (k == 0)
            {
                for (int i = 1; i < l2; i++)
                {
                    d = idx[i] - idx[i-1];
                    while (d--) count += d;
                }
                d = modulo;
            }

            for (int i = 1; i + k < l2; i++)
            {
                for (int j = d; i+j+k < l2; j += modulo)
                {
                    count += ((long long)(idx[i] - idx[i-1] + 1)) * ((long long)(idx[i+j+k] - idx[i+j+k-1] + 1));
                }
            }

            return count;
        }
    };