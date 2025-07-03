#include <iostream>
#include "BST.hpp"
#include "listBST.hpp"
using namespace std;


int randkey()
{
    return rand() % 100;
}

int main()
{
    srand(static_cast<unsigned>(time(0)));
    freopen("output.txt", "w", stdout);

    BST<int, int>* bst = new ListBST<int, int>();
    int key, val;

    cout << "Initializing..." << endl;
    for (int i = 0; i < 20; i++)
    {
        key = randkey();
        if (!bst->insert(key, rand() % 10)) cout << key << " already exists" << endl;

    }
    bst->print();
    cout << "Size: " << bst->size() << endl;
    cout << endl;

    cout << "Max: " << bst->find_max() << endl;
    cout << "Min: " << bst->find_min() << endl;
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        key = randkey();
        if (bst->find(key)) cout << key << " found" << endl;
        else cout << key << " not found" << endl;
    }
    cout << endl;

    cout << "Key - Value" << endl;
    for (int i = 0; i < 10; i++)
    {
        try
        {
            key = randkey();
            val = bst->get(key);
            cout << key << " - " << val << endl;
        }
        catch(const exception& e)
        {
            cerr << e.what() << endl;
        }
    }
    cerr << endl;
    cout << endl;

    cout << "Updating value through key" << endl;
    for (int i = 0; i < 10; i++)
    {
        try
        {
            key = randkey();
            bst->update(key, randkey());
            cout << "Updated " << key << endl;
        }
        catch(const exception& e)
        {
            cerr << e.what() << endl;
        }
    }
    cerr << endl;
    bst->print();
    cout << endl;

    cout << "CLearing..." << endl;
    bst->clear();
    bst->print();
    cout << "isEmpty: " << bst->empty() << endl;
    cout << endl;

    cout << "Reinitializing..." << endl;
    for (int i = 0; i < 20; i++)
    {
        key = randkey();
        if (!bst->insert(key, rand() % 10)) cout << key << " already exists" << endl;
    }
    bst->print();
    cout << endl;

    cout << "Max: " << bst->find_max() << endl;
    cout << "Min: " << bst->find_min() << endl;
    cout << endl;

    cout << "Size: " << bst->size() << endl;
    cout << "isEmpty: " << bst->empty() << endl;
    cout << endl;

    cout << "Removing key-value pair" << endl;
    for (int i = 0; i < 10; i++)
    {
        key = randkey();
        cout << "Key " << key << " - ";
        if (bst->remove(key))
        {
            cout << "Removed" << endl;
            bst->print();
        }

        else cout << "Not found" << endl;
    }
    bst->print();
    cout << "Size: " << bst->size() << endl;
    cout << endl;

    cout << "Max: " << bst->find_max() << endl;
    cout << "Min: " << bst->find_min() << endl;
    cout << endl;

    bst->print('D');
    bst->print('i');
    bst->print('p');
    bst->print('O');
    cout << endl;
}