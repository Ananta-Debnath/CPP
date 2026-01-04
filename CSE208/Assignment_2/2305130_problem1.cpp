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

void printMatrix(vector<vector<long long>> mat)
{
    for (vector<long long> row : mat)
    {
        for (long long x : row) cout << x << ' ';
        cout << '\n';
    }
}

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<long long>> adjMat(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) adjMat[i][i] = 0;

    long long a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        a--;
        b--;
        if (c < adjMat[a][b]) adjMat[a][b] = c;
        if (c < adjMat[b][a]) adjMat[b][a] = c;
    }

    // printMatrix(adjMat);
    vector<vector<long long>> dist = floydWarshall(n, adjMat);
    // printMatrix(dist);

    for (int i = 0; i < q; i++)
    {
        cin >> a >> b;
        a--;
        b--;

        if (dist[a][b] < INF) cout << dist[a][b];
        else cout << -1;
        cout << '\n';
        // cout << '\n';
    }
}