#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


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

int main()
{
    bool fileInput = true;

    int testNo = 10;
    // Uncomment the next lines to read input from a file instead of standard input
    string inFile = "sampleio/input/test" + to_string(testNo) + ".txt";
    if (fileInput) freopen(inFile.c_str(), "r", stdin);
    
    int n, m;
    cin >> n >> m;

    // Construct graph
    vector<Edge> graph;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.push_back(Edge(u, v, w));
    }

    int source = 0;
    cin >> source;

    auto mst = kruskal(n, graph);
    long long totalWeight = 0;
    for (auto e : mst) totalWeight += e.w;

    cout << "Total Weight: " << totalWeight << '\n';
    for (auto e : mst) cout << e.u << ' ' << e.v << '\n';


    // Print contents of a file if it exists
    // if (fileInput)
    // {
    //     string outFile = "sampleio/kruskals/out" + to_string(testNo) + ".txt";
    //     if (FILE* f = fopen(outFile.c_str(), "r"))
    //     {
    //         cout << "--- Contents of " << outFile << " ---\n";
    //         char buf[256];
    //         while (fgets(buf, sizeof(buf), f)) {
    //             cout << buf;
    //         }
    //         cout << "--- End of file ---\n";
    //         fclose(f);
    //     }
    // }

    return 0;
}
