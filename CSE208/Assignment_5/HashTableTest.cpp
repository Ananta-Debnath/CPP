#include <iostream>
#include <set>
#include <iomanip>
#include "HashTableChain.hpp"
using namespace std;

char randomChar() {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return charset[rand() % (sizeof(charset) - 1)];
}

string randomString(int length) {
    string result;
    for (int i = 0; i < length; ++i) {
        result += randomChar();
    }
    return result;
}

int main()
{
    srand((unsigned)time(0));

    int n = 10000;
    set<string> strings;

    while (strings.size() < n) {
        strings.insert(randomString(10));
    }
    cout << "Generated " << strings.size() << " unique random strings." << endl;

    vector<HashTableADT<string, int>*> tables;
    tables.push_back(new HashTableChain<string, int>(1)); // Chain method hash1
    tables.push_back(new HashTableChain<string, int>(2)); // Chain method hash2

    for (auto& table : tables)
    {
        int inserted = 0;
        for (const auto& s : strings)
        {
            inserted++;
            table->insert(s, inserted);
        }
        cout << "Inserted " << inserted << " words into table." << endl;
    }

    int searchCount = 1000;
    for (auto& table : tables)
    {
        int searched = 0;
        for (const auto& s : strings)
        {
            table->find(s);
            searched++;
            if (searched == searchCount) break;
        }
        cout << "Searched " << searched << " words in table." << endl;
    }

    vector<string> tableNames = {"Chain Method Hash1", "Chain Method Hash2", 
                                 "Double Hashing Hash1", "Double Hashing Hash2", 
                                 "Custom Probing Hash1", "Custom Probing Hash2"};

    std::cout << "  HashFn | Collisions  | Avg Hits\n";
    std::cout << "-------------------------------------\n";
    for (size_t i = 0; i < tables.size(); ++i) {
        std::cout << std::setw(8) << tableNames[i] << " | "
                  << std::setw(12) << static_cast<double>(tables[i]->getCollisionCount()) / n << " | "
                  << std::setw(10) << std::fixed << std::setprecision(2) 
                  << static_cast<double>(tables[i]->getHitCount()) / searchCount << std::endl;
    }

    for (auto& table : tables) {
        delete table;
    }
    tables.clear();

    return 0;
}