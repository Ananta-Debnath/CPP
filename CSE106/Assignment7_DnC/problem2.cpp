#include <bits/stdc++.h>
using namespace std;


int seatAvailableInBench(int* bench, int seatCount)
{
    if (seatCount <= 0) return 0;

    int n = 0;

    if (seatCount == 1 && bench[0] == 0) n++;

    else
    {
        if (bench[0] == 0 && bench[1] != 2) n++; // First seat

        for (int i = 1; i < seatCount-1; i++)
        {
            if (bench[i] == 0 && bench[i-1] == 0 && bench[i+1] != 2) n++;
        }

        if (bench[seatCount-1] == 0 && bench[seatCount-2] == 0) n++; // Last seat
    }

    return n;
}

int main()
{
    int n, b, m;
    cin >> n >> b;
    if (n % b != 0) return 0;

    int* seats = new int[n];
    for (int i = 0; i < n; i++) cin >> seats[i];

    cin >> m;

    int seatPerBench = n / b;
    int available = 0;

    for (int i = 0; i < n; i += seatPerBench)
    {
        available += seatAvailableInBench(&seats[i], seatPerBench);
        if (m <= available) break;
    }

    if (m <= available) cout << "true" << endl;

    else cout << "false" << endl;

    delete[] seats;

    return 0;
}

/*
8 2
1 0 0 0 2 0 0 0
2

12 3
1 0 2 0 0 0 1 0 2 0 1 0
3
*/
