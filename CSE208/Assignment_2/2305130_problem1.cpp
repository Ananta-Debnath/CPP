#include <bits/stdc++.h>
using namespace std;


const long long INF = numeric_limits<long long>::max()/4;

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

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<long long>> adjMat(n, vector<long long>(n, INF));

    long long a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        a--;
        b--;
        adjMat[a][b] = c;
        adjMat[b][a] = c;
    }

    for (vector<long long> row : adjMat)
    {
        for (long long w : row) cout << w << ' ';
        cout << '\n';
    }

    vector<vector<long long>> dist = floydWarshall(n, adjMat);

    for (vector<long long> row : dist)
    {
        for (long long w : row) cout << w << ' ';
        cout << '\n';
    }

    for (int i = 0; i < q; i++)
    {
        cin >> a >> b;
        a--;
        b--;

        if (dist[a][b] < INF) cout << dist[a][b];
        else cout << -1;
        cout << "\n\n";
    }
}