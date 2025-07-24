#include <bits/stdc++.h>
using namespace std;


int globalAlignment(string str1, string str2, int matchScore, int mismatchPenalty, int gapPenalty)
{
    int l1 = str1.length();
    int l2 = str2.length();
    int** dp = new int*[l1+1];
    for (int i = 0; i <= l1; i++) dp[i] = new int[l2+1];

    for (int i = 0; i < l1; i++) dp[i][0] = i * gapPenalty;
    for (int i = 0; i < l2; i++) dp[0][i] = i * gapPenalty;

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

    // Constructing respective strings
    stack<char> seq1, seq2;
    int x = l1, y = l2;
    char gap = '-';

    while (!(x == 0 || y == 0))
    {
        if (dp[x][y] == dp[x][y-1] + gapPenalty)
        {
            seq1.push(gap);
            seq2.push(str2[y--]);
        }
        else if (dp[x][y] == dp[x-1][y] + gapPenalty)
        {
            seq1.push(str1[x--]);
            seq2.push(gap);
        }
        else
        {
            seq1.push(str1[x--]);
            seq2.push(str2[y--]);
        }
    }
    while (x >= 0) seq1.push(str1[x--]);
    while (y >= 0) seq2.push(str2[y--]);

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

    int ans = dp[l1][l2];
    for (int i = 0; i <= l1; i++) delete[] dp[i];
    delete[] dp;

    return ans;
}

int localLength(string str1, string str2, int matchScore)
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

                if (dp[i][j] > dp[x][y])
                {
                    x = i;
                    y = j;
                }
            }
            // else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            // cout << dp[i][j] << " ";
        }
        // cout << endl;
    }

    int score = dp[x][y];
    int l = score / matchScore;
    cout << "Local alignment: " << endl;
    for (int i = 0; i < l; i++) cout << str1[x - l + i];
    cout << endl;
    for (int i = 0; i < l; i++) cout << str2[y - l + i];
    cout << endl;

    for (int i = 0; i <= l1; i++) delete[] dp[i];
    delete[] dp;

    return score;
}

int main()
{
    string str1, str2;
    int matchScore, mismatchPenalty, gapPenalty;

    cout << "Enter first sequence: ";
    cin >> str1;
    cout << "Enter second sequence: ";
    cin >> str2;
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
    int localScore = localLength(str1, str2, matchScore);
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
2
-1
-1
*/