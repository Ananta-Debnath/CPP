#include <bits/stdc++.h>
using namespace std;


int findMaxDiff(int* arr, int l, int& min)
{
    if (l < 1) return -1;

    if (l == 1)
    {
        if (min > *arr) min = *arr;
        return (*arr) - min;
    }

    int maxDiff = findMaxDiff(arr, l/2, min);
    int temp = findMaxDiff(&arr[l/2], l - (l/2), min);
    return (maxDiff < temp) ? temp : maxDiff;

}

int main()
{
    int arr[] = {5, 3, 1, 4, 2};

    int maxDiff = findMaxDiff(arr, sizeof(arr)/sizeof(int), arr[0]);
    cout << "Max difference = " << maxDiff << endl;

    return 0;
}