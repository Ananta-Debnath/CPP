#include <bits/stdc++.h>
using namespace std;


bool isPossible(const vector<int>& workloads, int workload, int employeeCount)
{
    int sum = 0;

    for (int x : workloads)
    {
        sum += x;
        if (sum > workload)
        {
            sum = x;
            employeeCount--;
            if (employeeCount == 0) return false;
        }
    }
    return (employeeCount > 0);
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> workloads;
    int start = 0, end = 0;
    int temp;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        workloads.push_back(temp);

        end += temp; // total
        if (temp > start) start = temp; // min possible workload
    }

    int m, res;
    if (workloads.size() < k) res = -1;

    else
    {
        while (start <= end)
        {
            m = (start + end)/2;

            if(isPossible(workloads, m, k))
            {
                res = m;
                end = m - 1;
            }

            else start = m + 1;
        }
    }
    cout << res << endl;

    return 0;
}