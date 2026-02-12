#include <iostream>
#include <random>
#include "2305130_1/RedBlackTree.hpp"
#include "2305130_2/AVLTree.hpp"
using namespace std;


int main()
{
    srand(time(0));
    cout << "Testing Red-Black Tree and AVL Tree with 1000 random operations each...\n";

    RedBlackTree<int, int> rbt;
    AVLTree<int, int> avl;
    cout << "Trees initialized.\n";

    int n = 1000;
    
    int insertions1 = 0, insertions2 = 0;
    for (int i = 1; i <= n; ++i)
    {
        int k = rand() % 1000000 + 1;
        if (i % 100 == 0) cout << "Inserting: " << k << "\n";
        insertions1 += (rbt.insert(k, i) ? 1 : 0);
        insertions2 += (avl.insert(k, i) ? 1 : 0);
    }
    cout << "Red-Black Tree Insertions: " << insertions1 << "\n";
    cout << "AVL Tree Insertions: " << insertions2 << "\n";

    int searches1 = 0, searches2 = 0;
    for (int i = 1; i <= n; ++i)
    {
        int k = rand() % 1000000 + 1;
        if (i % 100 == 0) cout << "Searching: " << k << "\n";
        searches1 += (rbt.get(k) != nullptr) ? 1 : 0;
        searches2 += (avl.get(k) != nullptr) ? 1 : 0;
    }
    cout << "Red-Black Tree Searches: " << searches1 << "\n";
    cout << "AVL Tree Searches: " << searches2 << "\n";

    int deletions1 = 0, deletions2 = 0;
    for (int i = 1; i <= n; ++i)
    {
        int k = rand() % 1000000 + 1;
        if (i % 100 == 0) cout << "Deleting: " << k << "\n";
        deletions1 += (rbt.remove(k) ? 1 : 0);
        deletions2 += (avl.remove(k) ? 1 : 0);
    }
    cout << "Red-Black Tree Deletions: " << deletions1 << "\n";
    cout << "AVL Tree Deletions: " << deletions2 << "\n";
}