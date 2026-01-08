#include <bits/stdc++.h>
using namespace std;


const double INF = numeric_limits<double>::max()/4;

vector<vector<double>> modifiedFloydWarshall(int n, const vector<vector<double>>& adjMat)
{
    vector<vector<double>> dist(adjMat);
    for (int k = 0; k < n; k++)
    {
        for (int x = 0; x < n; x++)
        {
            if (dist[x][k] < INF)
            {
                for (int y = 0; y < n; y++)
                {
                    if (dist[k][y] < INF) dist[x][y] = max(dist[x][y], dist[x][k] * dist[k][y]); // * instead of +
                }
            }
        }
    }
    return dist;
}

void printMatrix(vector<vector<double>> mat)
{
    for (vector<double> row : mat)
    {
        for (double x : row) cout << x << ' ';
        cout << '\n';
    }
}

int main()
{
    int n;
    cin >> n;

    unordered_map<string, int> mp;
    string str;
    getline(cin, str); // catch trailing spaces
    for (int i = 0; i < n; i++)
    {
        getline(cin, str);

        // Trim trailing spaces
        str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char c) {
            return !isspace(c);
        }).base(), str.end());

        mp[str] = i;

        // cout << str << '|' << '\n';
    }

    vector<vector<double>> adjMat(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) adjMat[i][i] = 1;

    int m;
    cin >> m;
    cin.ignore();

    int a, b;
    double c;
    for (int i = 0; i < m; i++)
    {
        getline(cin, str, ' ');
        a = mp[str];

        cin >> c;
        cin.ignore();

        getline(cin, str);
        // Trim trailing spaces
        str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char c) {
            return !isspace(c);
        }).base(), str.end());
        b = mp[str];

        // cout << a << ' ' << b << ' ' << c << '\n';
        if (c > adjMat[a][b]) adjMat[a][b] = c;
    }
    // cout << '\n';
    // printMatrix(adjMat);
    // cout << '\n';

    vector<vector<double>> dist = modifiedFloydWarshall(n, adjMat);
    // printMatrix(dist);
    // cout << '\n';

    bool arbitrage = false;
    for (int i = 0; i < n; i++)
    {
        if (dist[i][i] > 1)
        {
            arbitrage = true;
            break;
        }
    }

    cout << '\n' << (arbitrage ? "YES" : "NO") << '\n';

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
*/