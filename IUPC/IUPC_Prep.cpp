// ============================================
// IUPC COMPETITIVE PROGRAMMING TEMPLATE
// ============================================

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

// ==================== MAIN ====================
void solve() {
    // Your solution here
    
}

int main() {
    fastIO();
    // precompute_factorials(); // Uncomment if using nCr

    int t = 1;
    // cin >> t; // Uncomment for multiple test cases
    while (t--) {
        solve();
    }

    return 0;
}

// ==================== DEBUG ====================
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << x << endl
#define dbgv(v) cerr << #v << " = "; for(auto &x : v) cerr << x << " "; cerr << endl
#else
#define dbg(x)
#define dbgv(v)
#endif

// ==================== UTILITY FUNCTIONS ====================
template <typename T>
T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }

template <typename T>
T lcm(T a, T b) { return a / gcd(a, b) * b; }

template <typename T>
T power(T base, T exp, T mod = MOD) {
    T result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

ll modInverse(ll a, ll mod = MOD) { return power(a, mod - 2, mod); }

ll add(ll a, ll b, ll mod = MOD) { return ((a % mod) + (b % mod)) % mod; }
ll sub(ll a, ll b, ll mod = MOD) { return ((a % mod) - (b % mod) + mod) % mod; }
ll mul(ll a, ll b, ll mod = MOD) { return ((a % mod) * (b % mod)) % mod; }

//  Extended Euclidean Algorithm (for modular inverse when mod not prime)
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// ==================== SIEVE OF ERATOSTHENES ====================
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

// ==================== PRIME FACTORIZATION ====================
vector<pll> primeFactors(ll n) {
    vector<pll> factors;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ll cnt = 0;
            while (n % i == 0) { n /= i; cnt++; }
            factors.pb({i, cnt});
        }
    }
    if (n > 1) factors.pb({n, 1});
    return factors;
}

vector<int> build_spf(int N) {
    vector<int> spf(N, 0);
    for (int i = 2; i < N; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            for (int j = i; j < N; j += i) {
                if (spf[j] == 0)
                    spf[j] = i;
            }
        }
    }
    return spf;
}
//  Prime Factorization using SPF (O(log n) per query)
vector<int> get_prime_factors(int x, const vector<int> &spf) {
    vector<int> factors;
    while (x > 1) {
        factors.pb(spf[x]);
        x /= spf[x];
    }
    return factors;
}

// ==================== nCr with MOD ====================
const int MAXN = 2e5 + 5;
ll fact[MAXN], inv_fact[MAXN];

void precompute_factorials() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = mul(fact[i - 1], i);
    inv_fact[MAXN - 1] = modInverse(fact[MAXN - 1]);
    for (int i = MAXN - 2; i >= 0; i--)
        inv_fact[i] = mul(inv_fact[i + 1], i + 1);
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return mul(fact[n], mul(inv_fact[r], inv_fact[n - r]));
}

ll nPr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return mul(fact[n], inv_fact[n - r]);
}

//  Factorial & Inverse Factorial Precomputation (modular combinatorics)
vector<ll> build_fact(int N, ll mod) {
    vector<ll> fact(N + 1, 1);
    rep(i, 1, N + 1) fact[i] = (fact[i - 1] * i) % mod;
    return fact;
}
vector<ll> build_inv_fact(const vector<ll> &fact, ll mod) {
    int N = sz(fact) - 1;
    vector<ll> invFact(N + 1, 1);
    invFact[N] = modInverse(fact[N], mod);
    repr(i, N - 1, 0) invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    return invFact;
}
ll nCr_mod(ll n, ll r, const vector<ll> &fact, const vector<ll> &invFact, ll mod) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % mod * invFact[n - r] % mod;
}

//  Euler’s Totient Function (phi(n))
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

//  Divisor Count & Sum (O(sqrt n))
vector<int> get_divisors(int n) {
    vector<int> divisors;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.pb(i);
            if (i != n / i) divisors.pb(n / i);
        }
    }
    sort(all(divisors));
    return divisors;
}

// 1️⃣0️⃣ Chinese Remainder Theorem (CRT) for pairwise coprime moduli
// Returns (x, M) such that x % m[i] = r[i], M = product of moduli
pair<ll, ll> crt(const vector<ll> &r, const vector<ll> &m) {
    ll x = r[0], M = m[0];
    rep(i, 1, sz(r)) {
        ll a = x, b = M, c = r[i], d = m[i];
        ll s, t;
        ll g = ext_gcd(b, d, s, t);
        if ((c - a) % g != 0) return {-1, -1}; // no solution
        ll mod = b / g * d;
        ll tmp = ((c - a) / g * s) % (d / g);
        x = (a + b * tmp) % mod;
        if (x < 0) x += mod;
        M = mod;
    }
    return {x, M};
}

pair<long long, long long> crt_coprime(const vector<long long> &r, const vector<long long> &m) {
    int n = r.size();

    // Step 1: compute total modulus M
    long long M = 1;
    for (int i = 0; i < n; i++) {
        M *= m[i];
    }

    // Step 2: build the solution
    long long x = 0;
    for (int i = 0; i < n; i++) {
        long long Mi = M / m[i];                 // product of other moduli
        long long inv = modInverse(Mi, m[i]);  // inverse of Mi mod m[i]

        x += r[i] * Mi * inv;
        x %= M;
    }
    if (x < 0) x += M;

    return {x, M};
}

// ==================== DISJOINT SET UNION (DSU) ====================
struct DSU {
    vi parent, rank_, size_;
    int components;

    DSU(int n) {
        parent.resize(n + 1);
        rank_.resize(n + 1, 0);
        size_.resize(n + 1, 1);
        components = n;
        iota(all(parent), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        size_[px] += size_[py];
        if (rank_[px] == rank_[py]) rank_[px]++;
        components--;
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
    int getSize(int x) { return size_[find(x)]; }
    int getComponents() { return components; }
};

// ==================== SEGMENT TREE ====================
template <typename T>
struct SegmentTree {
    int n;
    vector<T> tree;
    T identity;
    function<T(T, T)> combine;

    SegmentTree(int n, T identity, function<T(T, T)> combine) 
        : n(n), identity(identity), combine(combine) {
        tree.assign(4 * n, identity);
    }

    void build(vector<T> &arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(2 * node, start, mid, idx, val);
            else
                update(2 * node + 1, mid + 1, end, idx, val);
            tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
        }
    }

    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return identity;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return combine(query(2 * node, start, mid, l, r),
                       query(2 * node + 1, mid + 1, end, l, r));
    }

    void update(int idx, T val) { update(1, 0, n - 1, idx, val); }
    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

// ==================== FENWICK TREE (BIT) ====================
template <typename T>
struct BIT {
    int n;
    vector<T> tree;

    BIT(int n) : n(n), tree(n + 1, 0) {}

    void update(int i, T delta) {
        for (++i; i <= n; i += i & (-i))
            tree[i] += delta;
    }

    T query(int i) {
        T sum = 0;
        for (++i; i > 0; i -= i & (-i))
            sum += tree[i];
        return sum;
    }

    T query(int l, int r) { return query(r) - (l ? query(l - 1) : 0); }
};

// ==================== SPARSE TABLE (RMQ) ====================
template <typename T>
struct SparseTable {
    vector<vector<T>> table;
    vector<int> log;
    function<T(T, T)> combine;

    SparseTable(vector<T> &arr, function<T(T, T)> combine) : combine(combine) {
        int n = arr.size();
        int k = __lg(n) + 1;
        table.assign(k, vector<T>(n));
        log.resize(n + 1);
        log[1] = 0;
        for (int i = 2; i <= n; i++)
            log[i] = log[i / 2] + 1;
        table[0] = arr;
        for (int j = 1; j < k; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                table[j][i] = combine(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
    }

    T query(int l, int r) {
        int j = log[r - l + 1];
        return combine(table[j][l], table[j][r - (1 << j) + 1]);
    }
};

// ==================== GRAPH ALGORITHMS ====================

// BFS
vi bfs(vvi &adj, int start) {
    int n = adj.size();
    vi dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

// DFS
void dfs(vvi &adj, int u, vector<bool> &visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(adj, v, visited);
        }
    }
}

// Dijkstra's Algorithm
vll dijkstra(vector<vpll> &adj, int start) {
    int n = adj.size();
    vll dist(n, INF);
    priority_queue<pll, vpll, greater<pll>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// Bellman-Ford Algorithm
pair<vll, bool> bellmanFord(int n, vector<tuple<int, int, ll>> &edges, int start) {
    vll dist(n, INF);
    dist[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (auto &[u, v, w] : edges) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    // Check for negative cycle
    for (auto &[u, v, w] : edges) {
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            return {dist, true}; // Negative cycle exists
        }
    }
    return {dist, false};
}

// Floyd-Warshall Algorithm
vvll floydWarshall(int n, vvll &dist) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}

// Topological Sort (Kahn's Algorithm)
vi topologicalSort(vvi &adj) {
    int n = adj.size();
    vi indegree(n, 0), result;
    for (int u = 0; u < n; u++)
        for (int v : adj[u])
            indegree[v]++;
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        result.pb(u);
        for (int v : adj[u])
            if (--indegree[v] == 0) q.push(v);
    }
    return (sz(result) == n) ? result : vi(); // Empty if cycle exists
}

// Kruskal's MST
ll kruskalMST(int n, vector<tuple<ll, int, int>> &edges) {
    sort(all(edges));
    DSU dsu(n);
    ll mstWeight = 0;
    for (auto &[w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            mstWeight += w;
        }
    }
    return mstWeight;
}

// LCA with Binary Lifting
struct LCA {
    int n, LOG;
    vvi parent, adj;
    vi depth;

    LCA(int n) : n(n), adj(n) {
        LOG = __lg(n) + 1;
        parent.assign(LOG, vi(n, -1));
        depth.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build(int root = 0) {
        dfs(root, -1, 0);
        for (int j = 1; j < LOG; j++)
            for (int i = 0; i < n; i++)
                if (parent[j - 1][i] != -1)
                    parent[j][i] = parent[j - 1][parent[j - 1][i]];
    }

    void dfs(int u, int p, int d) {
        parent[0][u] = p;
        depth[u] = d;
        for (int v : adj[u])
            if (v != p) dfs(v, u, d + 1);
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int j = 0; j < LOG; j++)
            if ((diff >> j) & 1) u = parent[j][u];
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; j--)
            if (parent[j][u] != parent[j][v]) {
                u = parent[j][u];
                v = parent[j][v];
            }
        return parent[0][u];
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};

// ==================== STRING ALGORITHMS ====================

// Z-Function
vi zFunction(string &s) {
    int n = s.size();
    vi z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

// KMP Failure Function
vi kmpFailure(string &s) {
    int n = s.size();
    vi fail(n, 0);
    for (int i = 1; i < n; i++) {
        int j = fail[i - 1];
        while (j > 0 && s[i] != s[j]) j = fail[j - 1];
        if (s[i] == s[j]) j++;
        fail[i] = j;
    }
    return fail;
}

// KMP Pattern Matching
vi kmpSearch(string &text, string &pattern) {
    string combined = pattern + "#" + text;
    vi z = kmpFailure(combined);
    vi matches;
    int m = pattern.size();
    for (int i = m + 1; i < sz(combined); i++)
        if (z[i] == m) matches.pb(i - 2 * m);
    return matches;
}

// String Hashing
struct StringHash {
    ll base, mod;
    vector<ll> hash_, pow_;

    StringHash(string &s, ll base = 31, ll mod = 1e9 + 7) : base(base), mod(mod) {
        int n = s.size();
        hash_.resize(n + 1);
        pow_.resize(n + 1);
        pow_[0] = 1;
        hash_[0] = 0;
        for (int i = 0; i < n; i++) {
            pow_[i + 1] = (pow_[i] * base) % mod;
            hash_[i + 1] = (hash_[i] * base + s[i] - 'a' + 1) % mod;
        }
    }

    ll getHash(int l, int r) { // 0-indexed, [l, r]
        return (hash_[r + 1] - hash_[l] * pow_[r - l + 1] % mod + mod) % mod;
    }
};

// ==================== GEOMETRY ====================
struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}
    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    Point operator*(ld k) { return Point(x * k, y * k); }
    ld dot(Point p) { return x * p.x + y * p.y; }
    ld cross(Point p) { return x * p.y - y * p.x; }
    ld norm() { return sqrt(x * x + y * y); }
    ld dist(Point p) { return (*this - p).norm(); }
};

// Convex Hull (Graham Scan)
vector<Point> convexHull(vector<Point> points) {
    int n = points.size();
    if (n < 3) return points;
    sort(all(points), [](Point &a, Point &b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    vector<Point> hull;
    // Build lower hull
    for (int i = 0; i < n; i++) {
        while (sz(hull) >= 2 && (hull.back() - hull[sz(hull) - 2]).cross(points[i] - hull.back()) <= 0)
            hull.pop_back();
        hull.pb(points[i]);
    }
    // Build upper hull
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (sz(hull) > lower_size && (hull.back() - hull[sz(hull) - 2]).cross(points[i] - hull.back()) <= 0)
            hull.pop_back();
        hull.pb(points[i]);
    }
    hull.pop_back();
    return hull;
}

// ==================== MISCELLANEOUS ====================

// Coordinate Compression
vi compress(vi &arr) {
    vi sorted_arr = arr;
    sort(all(sorted_arr));
    sorted_arr.erase(unique(all(sorted_arr)), sorted_arr.end());
    vi result(sz(arr));
    for (int i = 0; i < sz(arr); i++)
        result[i] = lower_bound(all(sorted_arr), arr[i]) - sorted_arr.begin();
    return result;
}

// Binary Search Helpers
template <typename T>
T binarySearchFirst(T lo, T hi, function<bool(T)> check) {
    while (lo < hi) {
        T mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

template <typename T>
T binarySearchLast(T lo, T hi, function<bool(T)> check) {
    while (lo < hi) {
        T mid = lo + (hi - lo + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

// Count Digits
int countDigits(ll n) { return n == 0 ? 1 : (int)log10(n) + 1; }

// Check if power of 2
bool isPowerOfTwo(ll n) { return n > 0 && (n & (n - 1)) == 0; }

// Count set bits
int countBits(ll n) { return __builtin_popcountll(n); }

static uint64_t splitmix64_state;

uint64_t splitmix64_next(void)
{
    uint64_t z;

    splitmix64_state += 0x9E3779B97F4A7C15ULL;
    z = splitmix64_state;

    z ^= (z >> 30);
    z *= 0xBF58476D1CE4E5B9ULL;

    z ^= (z >> 27);
    z *= 0x94D049BB133111EBULL;

    z ^= (z >> 31);
    return z;
}

struct SplitMix64Hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

/*
==================== QUICK REFERENCE ====================

INPUT/OUTPUT:
- Fast I/O: Already set up with fastIO()
- For large input: Use '\n' instead of endl

COMMON OPERATIONS:
- gcd(a, b), lcm(a, b)
- power(base, exp, mod)
- modInverse(a, mod)
- nCr(n, r), nPr(n, r) - call precompute_factorials() first

DATA STRUCTURES:
- DSU: DSU dsu(n); dsu.unite(a, b); dsu.find(x); dsu.connected(a, b)
- Segment Tree: SegmentTree<int> st(n, 0, [](int a, int b) { return a + b; });
- BIT: BIT<ll> bit(n); bit.update(i, delta); bit.query(l, r);
- Sparse Table: SparseTable<int> st(arr, [](int a, int b) { return min(a, b); });

GRAPH:
- BFS: vi dist = bfs(adj, start);
- Dijkstra: vll dist = dijkstra(adj, start);
- Topo Sort: vi order = topologicalSort(adj);
- MST: ll cost = kruskalMST(n, edges);
- LCA: LCA lca(n); lca.addEdge(u, v); lca.build(); lca.lca(u, v);

STRING:
- Z-Function: vi z = zFunction(s);
- KMP: vi matches = kmpSearch(text, pattern);
- Hashing: StringHash sh(s); sh.getHash(l, r);

GEOMETRY:
- Point operations: +, -, *, dot, cross, norm, dist
- Convex Hull: vector<Point> hull = convexHull(points);

NUMBER THEORY:
- Sieve: vector<bool> is_prime = sieve(n);
- Prime Factors: vector<pll> factors = primeFactors(n);

TIPS:
- Use 1LL * a * b to avoid overflow
- Use (a % MOD + MOD) % MOD for negative numbers
- Use __lg(n) for floor(log2(n))
- Use __builtin_popcount(n) for counting set bits
- 4 directions: dx={0,0,1,-1}, dy={1,-1,0,0}
- 8 directions: Include diagonals

==================== END REFERENCE ====================
*/
