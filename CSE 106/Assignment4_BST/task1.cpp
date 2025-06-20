#include <iostream>
#include <fstream>
#include "listBST.hpp"

using namespace std;

/*
g++ -std=c++11 task1.cpp -o task1
./task1 in_task1.txt > myout_task1.txt
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

        if (c == 'I')
        {
            in_file >> val;
            if (bst->insert(val, val)) cout << "Key " << val << " inserted into BST, ";

            else cout << "Insertion failed! Key " << val << " already exists in BST, ";

            bst->print();
        }
        else if (c == 'D')
        {
            in_file >> val;
            if (bst->remove(val)) cout << "Key " << val << " removed from BST, ";

            else cout << "Removal failed! Key " << val << " not found in BST, ";

            bst->print();
        }
        else if (c == 'F')
        {
            in_file >> val;
            if (bst->find(val)) cout << "Key " << val << " found in BST." << endl;

            else cout << "Key " << val << " not found in BST." << endl;
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
            in_file >> str;
            int num;
            if (str[0] == 'M' && str[1] == 'a')
            {
                try
                {
                    num = bst->find_max();
                    cout << "Maximum value: " << num << endl;
                }
                catch(const exception& e)
                {
                    cerr << e.what() << '\n';
                }
                
            }

            else if (str[0] == 'M' && str[1] == 'i')
            {
                try
                {
                    num = bst->find_min();
                    cout << "Minimum value: " << num << endl;
                }
                catch(const exception& e)
                {
                    cerr << e.what() << '\n';
                }
                
            }

            else throw runtime_error("Input is unknown");
        }
        else if (c == 'T')
        {
            in_file >> str;
            if (str[0] == 'D' && str[1] == 'e') bst->print('D');
            
            else if (str[0] == 'I' && str[1] == 'n') bst->print('I');
            
            else if (str[0] == 'P' && str[1] == 'r') bst->print('P');
            
            else if (str[0] == 'P' && str[1] == 'o') bst->print('O');

            else throw runtime_error("Input is unknown");
        }
        else
        {
            throw runtime_error("Input is unknown");
        }

        // End your code here
    }
    in_file.close();
    delete bst;
    return 0;
}
