#include <iostream>
#include "AVLTree.hpp"
using namespace std;


void traverse(AVLTree<int, int>& avl, int order)
{
    switch(order)
    {
        case 1:
            for (const auto& p : avl.preOrderTraversal()) cout << p.first << " ";
            cout << "\n";
            break;

        case 2:
            for (const auto& p : avl.inOrderTraversal()) cout << p.first << " ";
            cout << "\n";
            break;

        case 3:
            for (const auto& p : avl.postOrderTraversal()) cout << p.first << " ";
            cout << "\n";
            break;

        case 4:
            for (const auto& p : avl.levelOrderTraversal()) cout << p.first << " ";
            cout << "\n";
            break;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << "\n";

    AVLTree<int, int> avl;

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
                success = avl.remove(x);
                cout << e << " " << x << " " << (success ? 1 : 0) << "\n";
                break;

            case 1:
                success = avl.insert(x, x);
                cout << e << " " << x << " " << (success ? 1 : 0) << "\n";
                break;

            case 2:
                traverse(avl, x);
                break;
        }
    }

    return 0;
}

/*
16 
1 9 
1 5 
1 10 
1 0 
1 6 
1 11 
1 -1 
1 2 
1 1 
1 1 
2 1 
2 2 
0 10 
0 10  
2 1  
2 2
*/