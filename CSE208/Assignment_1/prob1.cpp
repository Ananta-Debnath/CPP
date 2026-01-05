#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    // Construct graph
    vector<vector<pair<int, int>>> adj(n+1);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
    }

    vector<int> dist(n+1, INT_MAX), distC(n+1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[1] = distC[1] = 0;
    pq.emplace(0, 1);

    while (!pq.empty()) {
        pair<int,int> top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        for (pair<int, int> p : adj[u])
        {
            int v = p.first;
            int w = p.second;

            // Not using coupon
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;   
                pq.emplace(dist[v], v);
            }

            // Using coupon
            distC[v] = min({distC[v], distC[u] + w, dist[u] + (w/2)});
        }
    }

    cout << distC[n] << endl;

    return 0;
}