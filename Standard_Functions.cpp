#include <bits/stdc++.h>

using namespace std;


const long long INF = numeric_limits<long long>::max()/4;

class Edge
{
public:
    int u, v, w;
    Edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
};


vector<int> dfs(const vector<vector<int>>& g, int start)
{
    int n = g.size();
    vector<int> parents(n, -1);
    stack<int> s;
    s.push(start);
    while (true)
    {
        if (s.empty())
        {
            for (int i = 0; i < n; i++)
            {
                if (parents[i] == -1)
                {
                    s.push(i);
                    parents[i] = i;
                    break;
                }
            }
        }

        if (s.empty()) break;

        int u = s.top();
        for (int x : g[u])
        {
            if (parents[x] == -1)
            {
                s.push(x);
                parents[x] = u;
                break;
            }
        }
        if (s.top() == u) s.pop();
    }

    return parents;
}

struct BFSResult {
    vector<int> distance;   // shortest path length in edges
    vector<int> parent;     // shortest-path tree
};

BFSResult bfs(const vector<vector<int>>& g, int start)
{
    int n = g.size();
    BFSResult result;
    for (int i = 0; i < n; i++)
    {
        result.distance.push_back(-1);
        result.parent.push_back(-1);
    }
    queue<int> q;
    q.push(start);
    // result.parent[start] = start;
    result.distance[start] = 0;
    while (!q.empty())
    {
        for (int p : result.parent) cout << p << ' ';
        cout << endl;

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

vector<int> connectedComponents(const vector<vector<int>>& g) // dunno where it got stuck
{
    int n = g.size();
    int compNum = 0;
    vector<int> componentId(n, -1);
    int connected = 0;

    for (int i = 0; i < n; i++)
    {
        BFSResult res;
        if (componentId[i] == -1) res = bfs(g, i);

        for (int i = 0; i < n; i++)
        {
            if (res.distance[i] != -1) componentId[i] = compNum;
        }
    }
    
    return componentId;
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

 
// ----------------- MAIN FUNCTION connectedComponents -----------------
int main() {
    // Example graph (undirected)
    int n = 6;
    vector<vector<int>> graph(n);
    graph[0] = {1};
    graph[1] = {0};
    graph[2] = {};
    graph[3] = {4};
    graph[4] = {3};
    graph[5] = {};

    // Compute connected components
    vector<int> componentId = connectedComponents(graph);

    // Output results
    cout << "Vertex\tComponentID\n";
    for (int v = 0; v < n; ++v) {
        cout << v << "\t" << componentId[v] << "\n";
    }

    return 0;
}