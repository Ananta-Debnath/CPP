#include <iostream>
#include <fstream>
#include "listBST.hpp"

using namespace std;

/*
g++ -std=c++11 task1.cpp -o task1
./task1 in_task1.txt > task1.txt
*/

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 2;
    }
    char c, str[5];
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst) {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    while (in_file >> c) {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages

        // Start your code here

        int key;
        string in;
        if (c == 'I')
        {
            in_file >> key;
            if (bst->insert(key, key)) cout << "Key " << key << " inserted into BST, ";

            else cout << "Insertion failed! Key " << key << " already exists in BST, ";

            bst->print();
        }
        else if (c == 'D')
        {
            in_file >> key;
            if (bst->remove(key)) cout << "Key " << key << " removed from BST, ";

            else cout << "Removal failed! Key " << key << " not found in BST, ";

            bst->print();
        }
        else if (c == 'F')
        {
            in_file >> key;
            if (bst->find(key)) cout << "Key " << key << " found in BST." << endl;

            else cout << "Key " << key << " not found in BST." << endl;
        }
        else if (c == 'E')
        {
            if (bst->empty()) cout << "Empty" << endl;

            else cout << "Not empty" << endl;
        }
        else if (c == 'S')
        {
            cout << "Size: " << bst->size() << endl;
        }
        else if (c == 'C')
        {
            bst->clear();
            cout << "Cleared BST" << endl;
        }
        else if (c == 'M')
        {
            in_file >> in;
            if (in == "Max") cout << "Maximum value: " << bst->find_max() << endl;

            else if (in == "Min") cout << "Minimum value: " << bst->find_min() << endl;

            else throw runtime_error("Input " + in + " is unknown");
        }
        else if (c == 'T')
        {
            in_file >> in;
            if (in == "Default") bst->print('D');
            
            else if (in == "In") bst->print('I');
            
            else if (in == "Pre") bst->print('P');
            
            else if (in == "Post") bst->print('O');

            else throw runtime_error("Input " + in + " is unknown");
        }
        else
        {
            throw runtime_error("Input " + to_string(c) + " is unknown");
        }

        // End your code here
    }
    in_file.close();
    delete bst;
    return 0;
}
