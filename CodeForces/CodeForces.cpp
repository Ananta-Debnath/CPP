#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

class Item
{
public:
    int v;
    int w;

    double value()
    {
        return v / (double)w;
    }

    bool operator < (Item item)
    {
        return value() > item.value();
    }
};
 
int main()
{
    int n, c;
    cin >> n >> c;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) cin >> items[i].w;
    for (int i = 0; i < n; i++) cin >> items[i].v;

    sort(items.begin(), items.end());

    long long ans = 0;
    for (Item item : items)
    {
        if (item.w < c)
        {
            ans += item.v;
            ans = ans % MOD;
            c -= item.w;
        }
    }


    cout << ans;
    cout << '\n';
    cout << '\n';
}