#include <bits/stdc++.h>
using namespace std;


const double INF = numeric_limits<double>::max()/4;

class Edge
{
public:
    int u, v;
    double w;
    Edge(int u = 0, int v = 0, double w = 0) : u(u), v(v), w(w) {}
};


struct BellmanFordResult {
    vector<double> dist;
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

void printBellmanFordResult(const BellmanFordResult& res)
{
    cout << "Bellman-Ford Distances:\n";
    for (size_t i = 0; i < res.dist.size(); ++i)
        cout << "Node " << i << ": " << res.dist[i] << '\n';
    cout << "Bellman-Ford Parents:\n";
    for (size_t i = 0; i < res.parent.size(); ++i)
        cout << "Node " << i << ": " << res.parent[i] << '\n';
    cout << "Has Negative Cycle: " << (res.hasNegativeCycle ? "Yes" : "No") << '\n';
}



int main()
{
    int n;
    cin >> n;

    unordered_map<string, int> mp;
    string str;
    // getline(cin, str); // catch trailing spaces
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        mp[str] = i;

        // cout << str << '|' << '\n';
    }

    vector<Edge> edges;

    int m;
    cin >> m;
    // cin.ignore();

    int a, b;
    double c;
    for (int i = 0; i < m; i++)
    {
        string from, to;
        double rate;
        cin >> from >> rate >> to;
        
        a = mp[from];
        b = mp[to];
        edges.push_back(Edge(a, b, -log(rate)));
    }

    BellmanFordResult res = bellmanFord(n, edges, 0);
    for (int i =  1; i < n; i++)
    {
        if (res.hasNegativeCycle) break;
        if (res.parent[i] == -1) res = bellmanFord(n, edges, i);
    }
    // cout << '\n';
    // printBellmanFordResult(res);
    cout << '\n' << (res.hasNegativeCycle ? "YES" : "NO") << '\n';

    return 0;
}

/*
3 
USD 
AUD 
BDT 
3 
USD 1.5 AUD 
AUD 81.85 BDT 
BDT 0.0082 USD

3 
USD 
AUD 
BDT 
6 
USD 1.5 AUD 
USD 122.36 BDT 
AUD 81.85 BDT 
AUD 0.66 USD 
BDT 0.012 AUD 
BDT 0.0081 USD

4 
YEN
USD 
AUD 
BDT 
3 
USD 1.5 AUD 
AUD 81.85 BDT 
BDT 0.0082 USD
*/