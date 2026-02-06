#include <bits/stdc++.h>
using namespace std;


void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int x = 2, y = 5;

    swap(x, y);

    cout << x << ' ' << y;
}