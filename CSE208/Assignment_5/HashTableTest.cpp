#include <iostream>
#include <set>
#include <iomanip>
#include "HashTableChain.hpp"
#include "HashTableDoubleHash.hpp"
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

    vector<pair<string, HashTableADT<string, int>*>> tables;
    tables.push_back({"Chain Method Hash1", new HashTableChain<string, int>(1)}); // Chain method hash1
    tables.push_back({"Chain Method Hash2", new HashTableChain<string, int>(2)}); // Chain method hash2
    tables.push_back({"Double Hashing Hash1", new HashTableDoubleHash<string, int>(1)}); // Double hashing hash1
    tables.push_back({"Double Hashing Hash2", new HashTableDoubleHash<string, int>(2)}); // Double hashing hash2

    for (auto& table : tables)
    {
        int inserted = 0;
        for (const auto& s : strings)
        {
            inserted++;
            table.second->insert(s, inserted);
        }
        cout << "Inserted " << inserted << " words into table." << endl;
    }

    int searchCount = 1000;
    for (auto& table : tables)
    {
        int searched = 0;
        for (const auto& s : strings)
        {
            table.second->find(s);
            searched++;
            if (searched == searchCount) break;
        }
        cout << "Searched " << searched << " words in table." << endl;
    }

    std::cout << "     HashFunction    |  Collisions  |   Avg Hits\n";
    std::cout << "------------------------------------------------\n";
    for (size_t i = 0; i < tables.size(); ++i) {
        std::cout << std::setw(20) << tables[i].first << " | "
                  << std::setw(12) << static_cast<double>(tables[i].second->getCollisionCount()) / n << " | "
                  << std::setw(10) << std::fixed << std::setprecision(2) 
                  << static_cast<double>(tables[i].second->getHitCount()) / searchCount << std::endl;
    }

    for (auto& table : tables) delete table.second;
    tables.clear();

    return 0;
}