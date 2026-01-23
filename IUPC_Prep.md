# IUPC Template Quick Reference

## Macros
| Macro | Meaning | Macro | Meaning |
|-------|---------|-------|---------|
| `ll` | `long long` | `pb` | `push_back` |
| `pii/pll` | `pair<int/ll, int/ll>` | `ff/ss` | `first/second` |
| `vi/vll` | `vector<int/ll>` | `all(x)` | `begin(), end()` |
| `vvi/vpii` | `vector<vi>/vector<pii>` | `sz(x)` | `(int)size()` |
| `rep(i,a,b)` | `for(i=a; i<b; i++)` | `each(x,a)` | range-based for |

## Constants
| `MOD` = 1e9+7 | `MOD2` = 998244353 | `INF` = 1e18 | `INFI` = 1e9 |
|---------------|--------------------|--------------| -------------|
| `dx[8]`, `dy[8]` - direction arrays (4 cardinal + 4 diagonal) |

---

## Number Theory
| Function | What it does |
|----------|--------------|
| `gcd(a,b)`, `lcm(a,b)` | GCD, LCM |
| `power(base, exp, mod)` | Modular exponentiation |
| `modInverse(a, mod)` | Modular inverse (Fermat) |
| `add/sub/mul(a, b, mod)` | Modular arithmetic |
| `sieve(n)` | Returns `vector<bool>` of primes |
| `getPrimes(n)` | Returns `vector<int>` of primes |
| `primeFactors(n)` | Returns `vector<{prime, count}>` |
| `nCr(n,r)`, `nPr(n,r)` | Combinations/Permutations (call `precompute_factorials()` first) |

---

## Data Structures

| Structure | Init | Operations |
|-----------|------|------------|
| **DSU** | `DSU dsu(n)` | `unite(a,b)`, `find(x)`, `connected(a,b)`, `getSize(x)`, `getComponents()` |
| **Segment Tree** | `SegmentTree<T> st(n, identity, combine_func)` | `update(idx, val)`, `query(l, r)` |
| **BIT** | `BIT<T> bit(n)` | `update(i, delta)`, `query(i)`, `query(l, r)` |
| **Sparse Table** | `SparseTable<T> st(arr, combine_func)` | `query(l, r)` - O(1) |

---

## Graph Algorithms

| Function | Input | Returns |
|----------|-------|---------|
| `bfs(adj, start)` | `vvi adj` | `vi dist` (-1 if unreachable) |
| `dfs(adj, u, visited)` | `vvi adj`, `vector<bool>` | void |
| `dijkstra(adj, start)` | `vector<vpll> adj` | `vll dist` |
| `bellmanFord(n, edges, start)` | `vector<tuple<int,int,ll>>` | `{dist, hasNegCycle}` |
| `floydWarshall(n, dist)` | `vvll dist` | `vvll dist` |
| `topologicalSort(adj)` | `vvi adj` | `vi order` (empty if cycle) |
| `kruskalMST(n, edges)` | `vector<tuple<ll,int,int>>` | `ll mstWeight` |
| **LCA** | `LCA lca(n)` | `addEdge(u,v)`, `build(root)`, `lca(u,v)`, `dist(u,v)` |

---

## String Algorithms

| Function | Returns |
|----------|---------|
| `zFunction(s)` | `vi z` - longest prefix match at each position |
| `kmpFailure(s)` | `vi fail` - failure function |
| `kmpSearch(text, pattern)` | `vi` - all match positions |
| `StringHash sh(s)` | `sh.getHash(l, r)` - substring hash |

---

## Geometry

| `Point(x,y)` | `p1 + p2`, `p1 - p2`, `p * k` | `dot()`, `cross()` | `norm()`, `dist()` |
|--------------|------------------------------|--------------------|--------------------|
| `convexHull(points)` → returns `vector<Point>` |

---

## Utilities

| Function | What it does |
|----------|--------------|
| `compress(arr)` | Coordinate compression |
| `binarySearchFirst(lo, hi, check)` | First value where check is true |
| `binarySearchLast(lo, hi, check)` | Last value where check is true |
| `countDigits(n)` | Number of digits |
| `isPowerOfTwo(n)` | Check power of 2 |
| `countBits(n)` | Count set bits |

---

## Remember
- `fastIO()` at start
- `precompute_factorials()` before nCr/nPr
- `1LL * a * b` to avoid overflow
- `((a % MOD) + MOD) % MOD` for negative mod
