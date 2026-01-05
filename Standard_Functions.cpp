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