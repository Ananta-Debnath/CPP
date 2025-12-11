#include<bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int u, v, w;
    Edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);

    int sum = 0;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = Edge(u, v, w);
        if (w > 0) sum += w;
    }
    
    vector<int> dist(n+1, sum), par(n+1);
    dist[1] = 0;

    int idx;
    for (int i = 0; i < n; i++)
    {
        idx = -1;
        for (Edge e : edges)
        {
            if ((dist[e.u] + e.w) < dist[e.v])
            {
                dist[e.v] = dist[e.u] + e.w;
                par[e.v] = e.u;
                idx = e.v;
            }
        }
        // for (int d : dist) cout << d << ' ';
        // cout << endl;
    }

    if (idx != -1)
    {
        for (int i = 0; i < n; i++) idx = par[idx];

        int org = idx = par[idx];
        stack<int> s;
        do 
        {
            s.push(idx);
            idx = par[idx];
        } while (idx != org);

        while (!s.empty())
        {
            cout << s.top() << ' ';
            s.pop();
        }
    }
    else cout << -1 << endl;

    return 0;
}