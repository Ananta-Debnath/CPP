#include <bits/stdc++.h>
using namespace std;



vector<tuple<int, int, long long>> prim(const vector<vector<pair<int, long long>>>& graph, int source = 0)
{
    vector<tuple<int, int, long long>> res;
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
            res.push_back({u, v, w});

            for (auto p : graph[v])
            {
                if (!visited[p.first]) pq.emplace(p.second, v, p.first);
            }
        }
    }

    return res;
}

int main()
{
    bool fileInput = true;

    int testNo = 4;
    // Uncomment the next lines to read input from a file instead of standard input
    string inFile = "sampleio/input/test" + to_string(testNo) + ".txt";
    if (fileInput) freopen(inFile.c_str(), "r", stdin);
    
    int n, m;
    cin >> n >> m;

    // Construct graph
    vector<vector<pair<int, long long>>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int source = 0;
    cin >> source;

    auto res = prim(adj, source);
    long long totalWeight = 0;
    for (auto e : res) totalWeight += get<2>(e);

    cout << "Total Weight: " << totalWeight << '\n';
    cout << "Root Node: " << source << '\n';
    for (auto e : res) cout << get<0>(e) << ' ' << get<1>(e) << '\n';

    
    // Print contents of a file if it exists
    // if (fileInput) {
    //     string outFile = "sampleio/prims/out" + to_string(testNo) + ".txt";
    //     if (FILE* f = fopen(outFile.c_str(), "r")) {
    //         cout << "--- Contents of " << outFile << " ---\n";
    //         char buf[256];
    //         while (fgets(buf, sizeof(buf), f)) {
    //             cout << buf;
    //         }
    //         cout << "--- End of file ---\n";
    //         fclose(f);
    //     }
    // }
}