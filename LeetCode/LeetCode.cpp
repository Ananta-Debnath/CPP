#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2)
    {
        for (int i = 0; i < nums1.size(); i++)
        {
            for (int j = 0; j < nums2.size(); j++)
            {
                if (nums1[i] == nums2[j])
                {
                    nums1[i] = j;
                    break;
                }
            }
        }

        long long count = 0;
        for (int i = 0; i < nums1.size() - 2; i++)
        {
            for (int j = i+1; j < nums1.size() - 1; j++)
            {
                if (nums1[i] < nums1[j])
                {
                    for (int k = j+1; k < nums1.size(); k++)
                    {
                        if (nums1[j] < nums1[k]) count++;
                    }
                }
            }
        }

        return count;
    }
};