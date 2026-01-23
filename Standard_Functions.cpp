#include <bits/stdc++.h>

using namespace std;


const long long INF = numeric_limits<long long>::max()/4;

class Edge
{
public:
    int u, v;
    long long w;
    Edge(int u = 0, int v = 0, long long w = 0) : u(u), v(v), w(w) {}
};

class DisjointSetUnion
{
private:
    vector<int> parent;
    vector<int> size;

public:
    DisjointSetUnion(int n = 0)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] == x) return x;
        else
        {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    void join(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return;

        if (size[rootX] < size[rootY])
        {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
        else
        {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};


template<typename T>
pair<vector<int>, unordered_map<T, int>> coordinate_compress(const vector<T>& v) {
    vector<T> sorted = v;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    unordered_map<T, int> mapping;
    for (int i = 0; i < (int)sorted.size(); ++i) mapping[sorted[i]] = i;
    vector<int> compressed;
    for (const T& x : v) compressed.push_back(mapping[x]);
    return {compressed, mapping};
}

// Coordinate Compression Use
// vector<int> arr = {100, 500, 100, 1000000, 500, 42};
//
// // Compress coordinates
// auto [compressed, mapping] = coordinate_compress(arr);
//
// // Now compressed = {1, 2, 1, 3, 2, 0}
// // mapping = {42:0, 100:1, 500:2, 1000000:3}
//
// // You can now use compressed as indices in a Fenwick Tree or segment tree of size 4 (not 1,000,000+)
// vector<int> bit(mapping.size(), 0);
// for (int idx : compressed) {
//     bit[idx]++; // count occurrences, for example
// }

// Convert adjacency list (vector<vector<int>>) to weighted adjacency list (vector<vector<pair<int, long long>>>)
vector<vector<pair<int, long long>>> toWeightedAdjList(const vector<vector<int>>& g, long long defaultWeight = 1) {
    int n = g.size();
    vector<vector<pair<int, long long>>> wg(n);
    for (int u = 0; u < n; ++u) {
        for (int v : g[u]) {
            wg[u].emplace_back(v, defaultWeight);
        }
    }
    return wg;
}

// Convert weighted adjacency list to adjacency list
vector<vector<int>> toAdjList(const vector<vector<pair<int, long long>>>& wg) {
    int n = wg.size();
    vector<vector<int>> g(n);
    for (int u = 0; u < n; ++u) {
        for (auto& p : wg[u]) {
            g[u].push_back(p.first);
        }
    }
    return g;
}

// Convert weighted adjacency list to edge list
vector<Edge> toEdgeList(const vector<vector<pair<int, long long>>>& wg) {
    int n = wg.size();
    vector<Edge> edges;
    for (int u = 0; u < n; ++u) {
        for (auto& p : wg[u]) {
            int v = p.first;
            long long w = p.second;
            edges.emplace_back(u, v, w);
        }
    }
    return edges;
}

// Convert edge list to weighted adjacency list
vector<vector<pair<int, long long>>> edgeListToWeightedAdjList(int n, const vector<Edge>& edges) {
    vector<vector<pair<int, long long>>> wg(n);
    for (const auto& e : edges) {
        wg[e.u].emplace_back(e.v, e.w);
    }
    return wg;
}

// Convert adjacency matrix to weighted adjacency list
vector<vector<pair<int, long long>>> adjMatToWeightedAdjList(const vector<vector<long long>>& mat) {
    int n = mat.size();
    vector<vector<pair<int, long long>>> wg(n);
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (mat[u][v] < INF)
                wg[u].emplace_back(v, mat[u][v]);
        }
    }
    return wg;
}

// Convert weighted adjacency list to adjacency matrix
vector<vector<long long>> weightedAdjListToAdjMat(const vector<vector<pair<int, long long>>>& wg, int n) {
    vector<vector<long long>> mat(n, vector<long long>(n, INF));
    for (int u = 0; u < n; ++u) {
        for (auto& p : wg[u]) {
            mat[u][p.first] = p.second;
        }
    }
    return mat;
}


// Print adjacency matrix
template<typename T>
void printAdjMat(const vector<vector<T>>& mat) {
    cout << "Adjacency Matrix:\n";
    for (const auto& row : mat) {
        for (const auto& val : row) {
            cout << val << ' ';
        }
        cout << '\n';
    }
}

// Print adjacency list (unweighted)
void printAdjList(const vector<vector<int>>& g) {
    cout << "Adjacency List:\n";
    for (size_t u = 0; u < g.size(); ++u) {
        cout << u << ": ";
        for (int v : g[u]) cout << v << ' ';
        cout << '\n';
    }
}

// Print adjacency list (weighted)
void printWeightedAdjList(const vector<vector<pair<int, long long>>>& g) {
    cout << "Weighted Adjacency List:\n";
    for (size_t u = 0; u < g.size(); ++u) {
        cout << u << ": ";
        for (auto [v, w] : g[u]) cout << "(" << v << ", " << w << ") ";
        cout << '\n';
    }
}


struct DFSResult {
    vector<int> parent;
    vector<int> order;
};

DFSResult dfs(const vector<vector<int>>& g, int start)
{
    int n = g.size();
    DFSResult res;
    res.parent.resize(n, -1);
    stack<int> s;
    s.push(start);
    while (true)
    {
        if (s.empty())
        {
            for (int i = 0; i < n; i++)
            {
                if (res.parent[i] == -1)
                {
                    s.push(i);
                    res.parent[i] = i;
                    break;
                }
            }
        }

        if (s.empty()) break;

        int u = s.top();
        for (int x : g[u])
        {
            if (res.parent[x] == -1)
            {
                s.push(x);
                res.parent[x] = u;
                break;
            }
        }
        if (s.top() == u)
        {
            res.order.push_back(u);
            s.pop();
        }
    }

    return res;
}

void printDFSResult(const DFSResult& res) {
    cout << "DFS Parent Array:\n";
    for (size_t i = 0; i < res.parent.size(); ++i)
        cout << "Node " << i << ": " << res.parent[i] << '\n';
    cout << "DFS Postorder (for Topo): ";
    for (auto x : res.order) cout << x << ' ';
    cout << '\n';
}

vector<int> topoSort(const vector<vector<int>>& g) {
    DFSResult res = dfs(g, 0); // or run dfs for all unvisited nodes if graph is not connected
    vector<int> topo = res.order;
    reverse(topo.begin(), topo.end());
    return topo;
}

void printTopoOrder(const vector<int>& order) {
    cout << "Topological Order: ";
    for (auto x : order) cout << x << ' ';
    cout << '\n';
}

struct BFSResult {
    vector<int> distance;   // shortest path length in edges
    vector<int> parent;     // shortest-path tree
};

BFSResult bfs(const vector<vector<int>>& g, int start)
{
    int n = g.size();
    BFSResult result;
    result.distance.resize(n, -1);
    result.parent.resize(n, -1);
    
    queue<int> q;
    q.push(start);
    // result.parent[start] = start;
    result.distance[start] = 0;
    while (!q.empty())
    {
        // for (int p : result.parent) cout << p << ' ';
        // cout << endl;

        int u = q.front();
        for (int x : g[u])
        {
            if (result.parent[x] == -1)
            {
                q.push(x);
                result.parent[x] = u;
                result.distance[x] = result.distance[u] + 1;
            }
        }
        q.pop();
    }

    return result;
}

void printBFSResult(const BFSResult& res) {
    cout << "BFS Distances:\n";
    for (size_t i = 0; i < res.distance.size(); ++i)
        cout << "Node " << i << ": " << res.distance[i] << '\n';
    cout << "BFS Parents:\n";
    for (size_t i = 0; i < res.parent.size(); ++i)
        cout << "Node " << i << ": " << res.parent[i] << '\n';
}

vector<int> connectedComponents(const vector<vector<int>>& g)
{
    int n = g.size();
    int compNum = 0;
    vector<int> componentId(n, -1);

    for (int i = 0; i < n; i++)
    {
        if (componentId[i] == -1)
        {
            BFSResult res = bfs(g, i);
            
            for (int j = 0; j < n; j++)
            {
                if (res.distance[j] != -1 && componentId[j] == -1)
                {
                    componentId[j] = compNum;
                }
            }
            compNum++;
        }
    }

    return componentId;
}

void printConnectedComponents(const vector<int>& components) {
    cout << "Connected Components:\n";
    for (size_t i = 0; i < components.size(); ++i)
        cout << "Node " << i << ": Component " << components[i] << '\n';
}

struct DijkstraResult {
    vector<long long> distance;
    vector<int> parent;
};

DijkstraResult dijkstra(int n, const vector<vector<pair<int, long long>>>& graph, int source)
{
    DijkstraResult res;
    for (int i = 0; i <= n; i++)
    {
        res.distance.push_back(INF);
        res.parent.push_back(-1);
    }
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    res.distance[source] = 0;
    res.parent[source] = -1;
    pq.emplace(0, source);

    while (!pq.empty())
    {
        pair<long long,int> top = pq.top();
        pq.pop();

        long long d = top.first;
        int u = top.second;

        if (d > res.distance[u]) continue;

        for (pair<int, long long> p : graph[u])
        {
            int v = p.first;
            long long w = p.second;

            if (res.distance[u] + w < res.distance[v])
            {
                res.distance[v] = res.distance[u] + w;
                res.parent[v] = u;
                pq.emplace(res.distance[v], v);
            }
        }
    }

    return res;
}

void printDijkstraResult(const DijkstraResult& res) {
    cout << "Dijkstra Distances:\n";
    for (size_t i = 0; i < res.distance.size(); ++i)
        cout << "Node " << i << ": " << res.distance[i] << '\n';
    cout << "Dijkstra Parents:\n";
    for (size_t i = 0; i < res.parent.size(); ++i)
        cout << "Node " << i << ": " << res.parent[i] << '\n';
}

struct BellmanFordResult {
    vector<long long> dist;
    vector<int> parent;
    bool hasNegativeCycle;
};

BellmanFordResult bellmanFord(int n, const vector<Edge>& edges, int source)
{
    BellmanFordResult res;
    res.hasNegativeCycle = false;
    for (int i = 0; i < n; i++)
    {
        res.dist.push_back(INF);
        res.parent.push_back(-1);
    }

    res.dist[source] = 0;
    bool changed;
    for (int i = 0; i < n; i++)
    {
        changed = false;
        for (Edge e : edges)
        {
            if (res.dist[e.u] != INF && res.dist[e.u] + e.w < res.dist[e.v])
            {
                res.dist[e.v] = res.dist[e.u] + e.w;
                res.parent[e.v] = e.u;
                changed = true;
            }
        }
        if (!changed) break;
    }

    res.hasNegativeCycle = changed;
    return res;
}

void printBellmanFordResult(const BellmanFordResult& res) {
    cout << "Bellman-Ford Distances:\n";
    for (size_t i = 0; i < res.dist.size(); ++i)
        cout << "Node " << i << ": " << res.dist[i] << '\n';
    cout << "Bellman-Ford Parents:\n";
    for (size_t i = 0; i < res.parent.size(); ++i)
        cout << "Node " << i << ": " << res.parent[i] << '\n';
    cout << "Has Negative Cycle: " << (res.hasNegativeCycle ? "Yes" : "No") << '\n';
}

vector<vector<long long>> floydWarshall(int n, const vector<vector<long long>>& adjMat)
{
    vector<vector<long long>> dist(adjMat);
    for (int k = 0; k < n; k++)
    {
        for (int x = 0; x < n; x++)
        {
            if (dist[x][k] < INF)
            {
                for (int y = 0; y < n; y++)
                {
                    if (dist[k][y] < INF) dist[x][y] = min(dist[x][y], dist[x][k] + dist[k][y]);
                }
            }
        }
    }
    return dist;
}

void printFloydWarshall(const vector<vector<long long>>& dist) {
    cout << "Floyd-Warshall Distance Matrix:\n";
    for (size_t i = 0; i < dist.size(); ++i) {
        for (size_t j = 0; j < dist[i].size(); ++j) {
            if (dist[i][j] >= INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << '\n';
    }
}

vector<Edge> prim(const vector<vector<pair<int, long long>>>& graph, int source = 0)
{
    vector<Edge> mst;
    int n = graph.size();
    // tuple <weight, from, to>
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq;
    vector<bool> visited(n, false);

    visited[source] = true;
    for (auto p : graph[source]) pq.emplace(p.second, source, p.first);

    while (!pq.empty())
    {
        auto [w, u, v] = pq.top();
        pq.pop();
        if (!visited[v])
        {
            visited[v] = true;
            mst.push_back(Edge(u, v, w));

            for (auto p : graph[v])
            {
                if (!visited[p.first]) pq.emplace(p.second, v, p.first);
            }
        }
    }

    return mst;
}

void printPrimResult(const vector<Edge>& mst) {
    long long totalWeight = 0;
    for (auto e : mst) totalWeight += e.w;

    cout << "Total Weight: " << totalWeight << '\n';
    cout << "Prim's MST Edges (u, v, w):\n";
    for (const auto& edge : mst) cout << edge.u << " - " << edge.v << " : " << edge.w << '\n';
}

vector<Edge> kruskal(int n, const vector<Edge>& graph)
{
    vector<Edge> mst;
    DisjointSetUnion dsu(n);

    vector<Edge> edges = graph;
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    for (auto e : edges)
    {
        if (dsu.find(e.u) != dsu.find(e.v))
        {
            mst.push_back(e);
            dsu.join(e.u, e.v);
        }
    }

    return mst;
}

void printKruskalResult(const vector<Edge>& mst) {
    long long totalWeight = 0;
    for (auto e : mst) totalWeight += e.w;

    cout << "Total Weight: " << totalWeight << '\n';
    cout << "Kruskal's MST Edges (u, v, w):\n";
    for (const auto& edge : mst) cout << edge.u << " - " << edge.v << " : " << edge.w << '\n';
}


// ----------------- MAIN FUNCTION connectedComponents -----------------
int main()
{
    // Create a graph with multiple connected components
    // Component 0: nodes {0, 1, 2}
    // Component 1: nodes {3, 4}
    // Component 2: node {5} (isolated)

    int n = 6;
    vector<vector<int>> graph(n);

    // Component 0: 0-1-2 triangle
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(0);
    graph[1].push_back(2);
    graph[2].push_back(0);
    graph[2].push_back(1);
    
    // Component 1: 3-4 edge
    graph[3].push_back(4);
    graph[4].push_back(3);
    
    // Node 5 is isolated (Component 2)
    
    // Find connected components
    vector<int> components = connectedComponents(graph);
    
    // Output results
    cout << "Node\tComponent ID\n";
    cout << "----\t------------\n";
    for (int i = 0; i < n; i++) {
        cout << i << "\t" << components[i] << "\n";
    }
    
    // Count number of components
    set<int> uniqueComponents(components.begin(), components.end());
    cout << "\nTotal components: " << uniqueComponents.size() << "\n";
    
    return 0;
}