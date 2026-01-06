#include <bits/stdc++.h>
using namespace std;

void Prims(vector<vector<int>>& g)
{
    // Prims algorithm implementation
}

void Dijkstras(vector<vector<int>>& g, int source)
{
    // Dijkstras algorithm implementation
}

// DFS Result structure to hold parent tree and finishing order
struct DFSResult {
    vector<int> parent;     // parent tree
    vector<int> order;      // finishing order of nodes (post-order)
};

DFSResult dfs(const vector<vector<int>>& g, int start)
{
    int n = g.size();
    DFSResult result;
    result.parent.resize(n, -1);
    stack<int> s;
    s.push(start);
    
    while (true)
    {
        if (s.empty())
        {
            for (int i = 0; i < n; i++)
            {
                if (result.parent[i] == -1)
                {
                    s.push(i);
                    result.parent[i] = i;
                    break;
                }
            }
        }

        if (s.empty()) break;

        int u = s.top();
        bool pushedChild = false;
        
        for (int x : g[u])
        {
            if (result.parent[x] == -1)
            {
                s.push(x);
                result.parent[x] = u;
                pushedChild = true;
                break;
            }
        }
        
        // If no child was pushed, we're done with this node
        if (!pushedChild)
        {
            result.order.push_back(u);  // Add to finishing order
            s.pop();
        }
    }

    return result;
}

void bfs(const vector<vector<int>>& g, int source)
{
    // BFS algorithm implementation
}

int main()
{
    return 0;
}
