#include <iostream>
#include "RedBlackTree.hpp"
using namespace std;

int main()
{
    string INPUT_FILE = "input.txt";
    string OUTPUT_FILE = "output.txt";
    if (!INPUT_FILE.empty()) freopen(INPUT_FILE.c_str(), "r", stdin);
    if (!OUTPUT_FILE.empty()) freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    // cout << "\n";

    RedBlackTree<int, int> rbt;

    int n;
    cin >> n;
    cout << n << "\n";

    while (n--)
    {
        int e, x;
        cin >> e >> x;

        bool success;
        switch(e)
        {
            case 0:
                success = rbt.remove(x);
                cout << e << " " << x << " " << (success ? 1 : 0) << "\n";
                break;

            case 1:
                success = rbt.insert(x, x);
                cout << e << " " << x << " " << (success ? 1 : 0) << "\n";
                break;

            case 2:
                success = (rbt.get(x) != nullptr);
                cout << e << " " << x << " " << (success ? 1 : 0) << "\n";
                break;

            case 3:
                cout << e << " " << x << " " << rbt.getLowerCount(x) << "\n";
                break;
        }
    }

    return 0;
}

/*
11 
1 1 
1 2 
1 3 
1 1 
0 1 
0 4 
2 3 
2 5 
1 1 
3 3 
3 6
*/