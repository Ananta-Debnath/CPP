#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
using namespace std;

/*
g++ -std=c++11 task2.cpp -o task2
./task2 in_task2.txt > task2.txt
*/

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 1;
    }

    BST<string, int> *bst1 = new ListBST<string, int>(); // Phil's words
    if (!bst1) {
        cerr << "Memory allocation failed\n";
        return 2;
    }
    BST<string, int> *bst2 = new ListBST<string, int>(); // Claire's words
    if (!bst2) {
        cerr << "Memory allocation failed\n";
        delete bst1; // Clean up previously allocated memory
        return 3;
    }

    int n;
    string key;
    in_file >> n;
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Phil's words
        // Start your code here

        in_file >> key;
        if (!bst1->insert(key, 1)) bst1->update(key, bst1->get(key) + 1);

        // End your code here
    }
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Claire's words
        // Start your code here

        in_file >> key;
        if (!bst2->insert(key, 1)) bst2->update(key, bst2->get(key) + 1);

        // End your code here
    }

    // TODO: Implement the logic to print the initial state of both hands
    // Start your code here

    cout << "Phil's words:" << endl;
    bst1->print('I');
    cout << endl;

    cout << "Claire's words:" << endl;
    bst2->print('I');
    // cout << endl;

    // End your code here
    cout << "\nGame starts!\n\n";
    cout << "==============================\n";

    while (true) {
        string word;
        in_file >> word;
        
        // TODO: Implement the logic to process the game turn and print both hands after each turn
        // Start your code here

        // Phil
        if (bst1->find(word))
        {
            bst1->update(word, bst1->get(word) - 1);
            if (bst1->get(word) == 0) bst1->remove(word);
            
            cout << "Phil has " << word << "!" << endl;
        }

        // Claire
        if (bst2->find(word))
        {
            bst2->update(word, bst2->get(word) - 1);
            if (bst2->get(word) == 0) bst2->remove(word);
            
            cout << "Claire has " << word << "!" << endl;
        }


        // Wining condition
        if (bst1->empty() && bst2->empty())
        {
            cout << "Draw!" << endl;
            break;
        }
        else if (bst1->empty())
        {
            cout << "Phil wins!" << endl;
            break;
        }
        else if (bst1->empty())
        {
            cout << "Claire wins!" << endl;
            break;
        }


        // Show remaining words
        cout << endl;

        cout << "Phil's remaining words:" << endl;
        bst1->print('I');
        cout << endl;

        cout << "Claire's remaining words:" << endl;
        bst2->print('I');
        cout << endl;

        // End your code here
        cout << "==============================\n";
    }

    in_file.close();
    delete bst1;
    delete bst2;
    return 0;
}