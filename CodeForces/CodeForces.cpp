#include <bits/stdc++.h>
using namespace std;
#define MOD 1000003


void solve()
{
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    int m = b[0] / a[0];
    for (int i = 1; i < n; i++)
    {
        if ((b[i] / a[i]) < m) m = b[i] / a[i];
    }
    int p = 1, ans = 0;
    while (m = m/2)
    {
        p *= 2;
        ans++;
    }

    for (int i = 0; i < n; i++) a[i] *= p;

    for (int i = 0; i < n; i++)
    {
        ans += b[i] - a[i];
        ans = ans % MOD;
    }

    cout << ans;
    cout << '\n';
    cout << '\n';
}
 
int main()
{
    int t;
    cin >> t;

    while(t--) solve();
}