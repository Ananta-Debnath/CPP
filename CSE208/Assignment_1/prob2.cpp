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

    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        edges.push_back(Edge(u, v, w));
    }
    
    vector<int> d(n+1, INT_MAX), d_n(n+1, INT_MAX), par(n+1);
    d_n[1] = 0;

    for (int i = 0; i < n; i++)
    {
        for (Edge e : edges)
        {
            d = d_n;
            if (d[e.u] + e.w < d[e.v])
            {
                d_n[e.v] = d[e.u] + e.w;
                par[e.v] = e.u;
            }
        }
    }

    int idx = -1;
    for (int i = 0; i < n; i++)
    {
        if (d[i] != d_n[i])
        {
            idx = i;
            break;
        }
    }

    if (idx != -1)
    {
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