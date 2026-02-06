# 📋 IUPC Competitive Programming Template

A comprehensive C++ template for competitive programming contests.

---

## 📦 Table of Contents

1. [Macros & Shortcuts](#macros--shortcuts)
2. [Constants](#constants)
3. [Number Theory](#number-theory)
4. [Data Structures](#data-structures)
5. [Graph Algorithms](#graph-algorithms)
6. [String Algorithms](#string-algorithms)
7. [Geometry](#geometry)
8. [Utilities](#utilities)
9. [Quick Reference](#quick-reference)

---

## Macros & Shortcuts

| Macro | Expansion | Description |
|-------|-----------|-------------|
| `ll` | `long long` | 64-bit integer |
| `ull` | `unsigned long long` | Unsigned 64-bit integer |
| `ld` | `long double` | Extended precision float |
| `pii` | `pair<int, int>` | Integer pair |
| `pll` | `pair<ll, ll>` | Long long pair |
| `vi` | `vector<int>` | Integer vector |
| `vll` | `vector<ll>` | Long long vector |
| `vvi` | `vector<vi>` | 2D integer vector |
| `vpii` | `vector<pii>` | Vector of int pairs |
| `pb` | `push_back` | Add to vector |
| `eb` | `emplace_back` | Emplace to vector |
| `mp` | `make_pair` | Create pair |
| `ff` | `first` | Pair first element |
| `ss` | `second` | Pair second element |
| `all(x)` | `(x).begin(), (x).end()` | Full range |
| `rall(x)` | `(x).rbegin(), (x).rend()` | Reverse range |
| `sz(x)` | `(int)(x).size()` | Container size |
| `rep(i,a,b)` | `for(int i=a; i<b; i++)` | Forward loop |
| `repr(i,a,b)` | `for(int i=a; i>=b; i--)` | Reverse loop |
| `each(x,a)` | `for(auto &x : a)` | Range-based loop |

---

## Constants

| Constant | Value | Description |
|----------|-------|-------------|
| `MOD` | `1e9 + 7` | Primary modulo |
| `MOD2` | `998244353` | NTT-friendly modulo |
| `INF` | `1e18` | Long long infinity |
| `INFI` | `1e9` | Integer infinity |
| `PI` | `acos(-1.0)` | Pi constant |
| `EPS` | `1e-9` | Epsilon for float comparison |
| `dx[]` | `{0,0,1,-1,1,1,-1,-1}` | X directions (4 + diagonals) |
| `dy[]` | `{1,-1,0,0,1,-1,1,-1}` | Y directions (4 + diagonals) |

---

## Number Theory

### Basic Functions

```cpp
gcd(a, b)              // Greatest common divisor
lcm(a, b)              // Least common multiple
power(base, exp, mod)  // Modular exponentiation O(log n)
modInverse(a, mod)     // Modular inverse using Fermat's theorem
add(a, b, mod)         // Modular addition
sub(a, b, mod)         // Modular subtraction
mul(a, b, mod)         // Modular multiplication
```

### Sieve of Eratosthenes

```cpp
vector<bool> is_prime = sieve(n);     // O(n log log n)
vi primes = getPrimes(n);             // Get all primes up to n
```

### Prime Factorization

```cpp
vector<pll> factors = primeFactors(n);  // O(sqrt(n))
// Returns vector of {prime, count} pairs
```

### Combinatorics (nCr, nPr)

```cpp
// First call in main():
precompute_factorials();

// Then use:
ll combinations = nCr(n, r);    // n choose r
ll permutations = nPr(n, r);    // n permute r
```

---

## Data Structures

### DSU (Disjoint Set Union / Union-Find)

```cpp
DSU dsu(n);                    // Create DSU with n elements (1-indexed)
dsu.unite(a, b);               // Union two sets, returns true if merged
dsu.find(x);                   // Find root of x
dsu.connected(a, b);           // Check if a and b are in same set
dsu.getSize(x);                // Get size of set containing x
dsu.getComponents();           // Get number of connected components
```

**Time Complexity:** O(α(n)) per operation (nearly constant)

### Segment Tree

```cpp
// Sum segment tree
SegmentTree<int> st(n, 0, [](int a, int b) { return a + b; });

// Min segment tree
SegmentTree<int> st(n, INT_MAX, [](int a, int b) { return min(a, b); });

// Max segment tree
SegmentTree<int> st(n, INT_MIN, [](int a, int b) { return max(a, b); });

// Operations
st.update(idx, val);           // Point update
st.query(l, r);                // Range query [l, r]
```

**Time Complexity:** O(log n) per operation

### Fenwick Tree (Binary Indexed Tree)

```cpp
BIT<ll> bit(n);                // Create BIT of size n
bit.update(i, delta);          // Add delta to position i
bit.query(i);                  // Prefix sum [0, i]
bit.query(l, r);               // Range sum [l, r]
```

**Time Complexity:** O(log n) per operation

### Sparse Table (RMQ)

```cpp
// Min query sparse table
SparseTable<int> st(arr, [](int a, int b) { return min(a, b); });

// Max query sparse table
SparseTable<int> st(arr, [](int a, int b) { return max(a, b); });

st.query(l, r);                // Range query [l, r]
```

**Time Complexity:** O(n log n) build, O(1) query

---

## Graph Algorithms

### BFS (Breadth-First Search)

```cpp
vvi adj(n);                    // Adjacency list
vi dist = bfs(adj, start);     // Returns distances from start
// dist[v] = -1 if unreachable
```

**Time Complexity:** O(V + E)

### DFS (Depth-First Search)

```cpp
vvi adj(n);
vector<bool> visited(n, false);
dfs(adj, start, visited);
```

**Time Complexity:** O(V + E)

### Dijkstra's Algorithm

```cpp
vector<vpll> adj(n);           // adj[u] = {(v, weight), ...}
vll dist = dijkstra(adj, start);
// dist[v] = INF if unreachable
```

**Time Complexity:** O((V + E) log V)

### Bellman-Ford Algorithm

```cpp
vector<tuple<int, int, ll>> edges;  // {u, v, weight}
auto [dist, hasNegCycle] = bellmanFord(n, edges, start);
```

**Time Complexity:** O(V × E)

### Floyd-Warshall Algorithm

```cpp
vvll dist(n, vll(n, INF));     // Initialize distance matrix
// Set dist[i][i] = 0, dist[u][v] = weight
dist = floydWarshall(n, dist);
```

**Time Complexity:** O(V³)

### Topological Sort

```cpp
vvi adj(n);                    // Directed graph
vi order = topologicalSort(adj);
// Returns empty vector if cycle exists
```

**Time Complexity:** O(V + E)

### Kruskal's MST

```cpp
vector<tuple<ll, int, int>> edges;  // {weight, u, v}
ll mstWeight = kruskalMST(n, edges);
```

**Time Complexity:** O(E log E)

### LCA (Lowest Common Ancestor)

```cpp
LCA lca(n);                    // Create LCA structure
lca.addEdge(u, v);             // Add tree edges
lca.build(root);               // Build from root (default 0)
int ancestor = lca.lca(u, v);  // Find LCA
int distance = lca.dist(u, v); // Distance between u and v
```

**Time Complexity:** O(n log n) build, O(log n) query

---

## String Algorithms

### Z-Function

```cpp
vi z = zFunction(s);
// z[i] = length of longest substring starting at i 
// that matches prefix of s
```

**Time Complexity:** O(n)

### KMP Pattern Matching

```cpp
vi fail = kmpFailure(pattern);        // Failure function
vi matches = kmpSearch(text, pattern); // All match positions
```

**Time Complexity:** O(n + m)

### String Hashing

```cpp
StringHash sh(s);              // Build hash for string s
ll h = sh.getHash(l, r);       // Get hash of s[l..r] (0-indexed)
```

**Time Complexity:** O(n) build, O(1) query

---

## Geometry

### Point Structure

```cpp
Point p(x, y);                 // Create point
Point sum = p1 + p2;           // Vector addition
Point diff = p1 - p2;          // Vector subtraction
Point scaled = p * k;          // Scalar multiplication
ld dot = p1.dot(p2);           // Dot product
ld cross = p1.cross(p2);       // Cross product
ld length = p.norm();          // Vector magnitude
ld d = p1.dist(p2);            // Distance between points
```

### Convex Hull

```cpp
vector<Point> points;
vector<Point> hull = convexHull(points);
```

**Time Complexity:** O(n log n)

---

## Utilities

### Coordinate Compression

```cpp
vi arr = {100, 5, 200, 5, 100};
vi compressed = compress(arr);  // {1, 0, 2, 0, 1}
```

### Binary Search Helpers

```cpp
// Find first value where check(x) is true
T ans = binarySearchFirst(lo, hi, check);

// Find last value where check(x) is true
T ans = binarySearchLast(lo, hi, check);
```

### Bit Manipulation

```cpp
countDigits(n);                // Number of digits
isPowerOfTwo(n);               // Check if power of 2
countBits(n);                  // Count set bits (__builtin_popcountll)
__lg(n);                       // floor(log2(n))
```

---

## Quick Reference

### Input/Output
```cpp
fastIO();                      // Call at start of main()
// Use '\n' instead of endl for faster output
```

### Multiple Test Cases
```cpp
int t;
cin >> t;
while (t--) {
    solve();
}
```

### Avoid Overflow
```cpp
ll result = 1LL * a * b;       // Multiply ints safely
```

### Negative Modulo
```cpp
((a % MOD) + MOD) % MOD        // Handle negative numbers
```

### Direction Arrays
```cpp
// 4 directions (up, down, left, right)
for (int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
}

// 8 directions (including diagonals)
for (int i = 0; i < 8; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
}
```

---

## 🚀 Contest Tips

1. **Read problems carefully** - Don't miss constraints
2. **Check edge cases** - n=0, n=1, empty input
3. **Use appropriate data types** - `ll` for large numbers
4. **Debug with small inputs first**
5. **Don't forget to uncomment**:
   - `cin >> t;` for multiple test cases
   - `precompute_factorials();` for nCr/nPr

---

**Good luck! 🎯**
