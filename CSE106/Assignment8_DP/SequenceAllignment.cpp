#include <bits/stdc++.h>
using namespace std;


void showStringFromDP(int** dp, string str1, string str2, int x, int y, int gapPenalty, bool local)
{
    // Constructing respective strings
    stack<char> seq1, seq2;
    char gap = '-';

    while (!(x == 0 || y == 0))
    {
        if (local && dp[x][y] < 0) break;
        
        if (dp[x][y] == dp[x][y-1] + gapPenalty)
        {
            seq1.push(gap);
            seq2.push(str2[--y]);
        }
        else if (dp[x][y] == dp[x-1][y] + gapPenalty)
        {
            seq1.push(str1[--x]);
            seq2.push(gap);
        }
        else
        {
            seq1.push(str1[--x]);
            seq2.push(str2[--y]);
        }
    }

    if (!local)
    {
        while (x > 0)
        {
            seq1.push(str1[--x]);
            seq2.push(gap);
        }
        while (y > 0)
        {
            seq1.push(gap);
            seq2.push(str2[--y]);
    }
    }

    while (!seq1.empty())
    {
        cout << seq1.top();
        seq1.pop();
    }
    cout << endl;
    while (!seq2.empty())
    {
        cout << seq2.top();
        seq2.pop();
    }
    cout << endl;
}

int globalAlignment(string str1, string str2, int matchScore, int mismatchPenalty, int gapPenalty)
{
    int l1 = str1.length();
    int l2 = str2.length();
    int** dp = new int*[l1+1];
    for (int i = 0; i <= l1; i++) dp[i] = new int[l2+1];

    for (int i = 0; i <= l1; i++) dp[i][0] = i * gapPenalty;
    for (int i = 0; i <= l2; i++) dp[0][i] = i * gapPenalty;

    for (int i = 1; i <= l1; i++)
    {
        for (int j = 1; j <= l2; j++)
        {
            if (str1[i-1] == str2[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + matchScore;
            }
            else
            {
                dp[i][j] = max({dp[i-1][j-1] + mismatchPenalty, dp[i-1][j] + gapPenalty, dp[i][j-1] + gapPenalty});
            }
            // if (dp[i][j] >= 0) cout << "+";
            // cout << dp[i][j] << " ";
        }
        // cout << endl;
    }

    cout << "Global Alignment: " << endl;
    showStringFromDP(dp, str1, str2, l1, l2, gapPenalty, false);

    int ans = dp[l1][l2];
    for (int i = 0; i <= l1; i++) delete[] dp[i];
    delete[] dp;

    return ans;
}

int localLength(string str1, string str2, int matchScore, int mismatchPenalty, int gapPenalty)
{
    int l1 = str1.length();
    int l2 = str2.length();
    int** dp = new int*[l1+1];
    for (int i = 0; i <= l1; i++) dp[i] = new int[l2+1]();

    int x = 0, y = 0;
    for (int i = 1; i <= l1; i++)
    {
        for (int j = 1; j <= l2; j++)
        {
            if (str1[i-1] == str2[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + matchScore;
                if (dp[i-1][j-1] == -1) dp[i][j]++;

                if (dp[i][j] >= dp[x][y])
                {
                    x = i;
                    y = j;
                }
            }
            else
            {
                dp[i][j] = max({dp[i-1][j-1] + mismatchPenalty, dp[i-1][j] + gapPenalty, dp[i][j-1] + gapPenalty, -1});
            }
            // cout << dp[i][j] << " ";
        }
        // cout << endl;
    }

    int score = dp[x][y];
    cout << "Local alignment: " << endl;
    showStringFromDP(dp, str1, str2, x, y, gapPenalty, true);

    for (int i = 0; i <= l1; i++) delete[] dp[i];
    delete[] dp;

    return score;
}

int main()
{
    string str1, str2;
    int matchScore, mismatchPenalty, gapPenalty;

    cout << "Enter first sequence: ";
    // cin >> str1;
    getline(cin, str1);
    for (int i = 0; i < str1.length(); i++) str1[i] = toupper(str1[i]);
    cout << "Enter second sequence: ";
    // cin >> str2;
    getline(cin, str2);
    for (int i = 0; i < str2.length(); i++) str2[i] = toupper(str2[i]);
    cout << "Enter match score: ";
    cin >> matchScore;
    cout << "Enter mismatch penalty: ";
    cin >> mismatchPenalty;
    cout << "Enter gap penalty: ";
    cin >> gapPenalty;

    cout << endl;
    int globalScore = globalAlignment(str1, str2, matchScore, mismatchPenalty, gapPenalty);
    cout << "Maximum score: " << globalScore << endl;

    cout << endl;
    int localScore = localLength(str1, str2, matchScore, mismatchPenalty, gapPenalty);
    cout << "Maximum score: " << localScore << endl;
}

/*
AGACTAGTTAC
CGAAGTT
1
-1
-2

AASASAS
ASHJHGHQSDSD
1
-1
-2

AGTACG
GTTCAG
2
-1
-2
*/