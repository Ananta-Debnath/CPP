#include <bits/stdc++.h>
using namespace std;

// ==================== MACROS ====================
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>
#define vvll vector<vll>
#define vpii vector<pii>
#define vpll vector<pll>
#define mii map<int, int>
#define mll map<ll, ll>
#define si set<int>
#define sl set<ll>
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define repr(i, a, b) for (int i = (a); i >= (b); i--)
#define each(x, a) for (auto &x : a)
#define endl '\n'

// ==================== CONSTANTS ====================
const int MOD = 1e9 + 7;
const int MOD2 = 998244353;
const ll INF = 1e18;
const int INFI = 1e9;
const double PI = acos(-1.0);
const double EPS = 1e-9;
const int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

// ==================== FAST I/O ====================
void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

// ==================== DEBUG ====================
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << x << endl
#define dbgv(v) cerr << #v << " = "; for(auto &x : v) cerr << x << " "; cerr << endl
#else
#define dbg(x)
#define dbgv(v)
#endif


vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    return is_prime;
}

vi getPrimes(int n) {
    vector<bool> is_prime = sieve(n);
    vi primes;
    for (int i = 2; i <= n; i++)
        if (is_prime[i]) primes.pb(i);
    return primes;
}

// ==================== MAIN ====================
void solve() {
    // Your solution here
    int n;
    cin >> n;

    vi dp(n+1, INFI);
    dp[1] = -1;

    vi primes = getPrimes(n);
    each(x, primes) dp[x] = -1; 

    int c;
    rep(i, 0, n)
    {
        cin >> c;
        dp[c] = 1;
    }

    rep(i, 1, n+1)
    {
        if (dp[i] == -1)
        {
            dp[i] = INFI;
            continue;
        }

        for (int j = 2; j*j <= i; j++)
        {
            if (i % j == 0) dp[i] = min(dp[i], dp[j] + dp[i/j]);
        }
    }

    rep(i, 1, n+1)
    {
        cout << ((dp[i] >= INFI) ? -1 : dp[i]) << ' ';
    }
}

int main() {
    fastIO();
    // precompute_factorials(); // Uncomment if using nCr

    int t = 1;
    cin >> t; // Uncomment for multiple test cases
    while (t--) {
        solve();
    }

    return 0;
}


/*
1
8
3 2 2 3 7 3 6 7
*/