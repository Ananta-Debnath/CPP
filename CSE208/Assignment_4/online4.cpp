#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;


const long long INF = numeric_limits<long long>::max()/4;

class Edge
{
public:
    int u, v;
    long long w;
    Edge(int u = 0, int v = 0, long long w = 0) : u(u), v(v), w(w) {}
};

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

struct BFSResult {
    vector<int> distance;
    vector<int> parent;
};

BFSResult bfs(const vector<vector<long long>>& g, int start)
{
    int n = g.size();
    BFSResult result;
    result.distance.resize(n, -1);
    result.parent.resize(n, -1);
    
    queue<int> q;
    q.push(start);
    result.parent[start] = start;
    result.distance[start] = 0;
    while (!q.empty())
    {
        // for (int p : result.parent) cout << p << ' ';
        // cout << endl;

        int u = q.front();
        for (int i = 0; i < n; i++)
        {
            if (g[u][i] > 0 && result.parent[i] == -1)
            {
                q.push(i);
                result.parent[i] = u;
                result.distance[i] = result.distance[u] + 1;
            }
        }
        q.pop();
    }

    return result;
}

struct MaxFlowResult
{
    long long maxFlow;
    vector<Edge> flow;
    vector<vector<long long>> rg;
};

MaxFlowResult edmondsKarpFordFulkerson(int n, const vector<vector<long long>>& graph, int s, int t)
{
    vector<vector<long long>> g = graph;
    MaxFlowResult res;
    res.maxFlow = 0;

    // printAdjMat(g, "Capacity Graph");
    // cout << '\n';

    while (true)
    {
        BFSResult path = bfs(g, s);

        if (path.parent[t] == -1) break;

        long long minFlow = INT_MAX;
        int node = t;
        while (node != s)
        {
            int par = path.parent[node];
            minFlow = min(minFlow, g[par][node]);
            node = par;
        }
        res.maxFlow += minFlow;
        // cout << minFlow << '\n';

        node = t;
        while (node != s)
        {
            int par = path.parent[node];
            // cout << par << ' ' << node << '\n';

            g[par][node] -= minFlow;
            g[node][par] += minFlow;

            node = par;
        }
        // printAdjMat(g, "Capacity Graph");
        // cout << '\n';
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] >= 0)
            {
                int flow = graph[i][j] - g[i][j];
                // f = max(0, f);
                res.flow.push_back(Edge(i, j, flow));
            }
        }
    }
    res.rg = g;

    return res;
}


int main()
{
    int n, m;
    cin >> n >> m;

    // Construct graph
    vector<vector<long long>> adjMat((2*n)+1, vector<long long>((2*n)+1, -1));
    for (int i = 1; i <= n; i++) adjMat[i][i+n] = 1;
    adjMat[1][n+1] = INF; // Source Indestructable

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v;
        adjMat[u+n][v] = 1;

        // printAdjMat(adjMat);
    }

    int s, t;
    // cin >> s >> t;
    s = 1;
    t = n;

    auto res = edmondsKarpFordFulkerson((2*n)+1, adjMat, s, t);

    cout << res.maxFlow << '\n';
    // for (auto e : res.flow)
    // {
    //     cout << e.u << ' ' << e.v << ' ';
    //     cout << e.w << '/' << adjMat[e.u][e.v] << '\n';
    // }

    return 0;
}