#include <iostream>
#include <set>
#include <iomanip>
#include "HashTableChain.hpp"
#include "HashTableDoubleHash.hpp"
#include "HashTableCustomHash.hpp"

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

    int wordLength = 10;
    // cin >> wordLength;

    int wordCount = 10000;
    set<string> strings;

    while (strings.size() < wordCount) {
        strings.insert(randomString(wordLength));
    }
    // cout << "Generated " << strings.size() << " unique random strings." << endl;

    vector<pair<string, HashTableADT<string, int>*>> tables;
    tables.push_back({"Chain Method", new HashTableChain<string, int>(1)}); // Chain method hash1
    tables.push_back({"Chain Method", new HashTableChain<string, int>(2)}); // Chain method hash2
    tables.push_back({"Double Hashing", new HashTableDoubleHash<string, int>(1)}); // Double hashing hash1
    tables.push_back({"Double Hashing", new HashTableDoubleHash<string, int>(2)}); // Double hashing hash2
    tables.push_back({"Custom Hashing", new HashTableCustomHash<string, int>(1, 1, 3)}); // Custom hashing hash1
    tables.push_back({"Custom Hashing", new HashTableCustomHash<string, int>(2, 1, 3)}); // Custom hashing hash2

    for (auto& table : tables)
    {
        int inserted = 0;
        for (const auto& s : strings)
        {
            inserted++;
            table.second->insert(s, inserted);
        }
        // cout << "Inserted " << inserted << " words into table." << endl;
    }

    int searchCount = 1000;
    set<string> searchStrings;
    while (searchStrings.size() < searchCount)
    {
        auto it = strings.begin();
        std::advance(it, rand() % strings.size());
        searchStrings.insert(*it);
    }

    for (auto& table : tables)
    {
        int searched = 0;
        for (const auto& s : searchStrings)
        {
            table.second->find(s);
            searched++;
            if (searched == searchCount) break;
        }
        // cout << "Searched " << searched << " words in table." << endl;
    }

    cout << "------------------------------------------------------------------------\n";
    cout << "|                  |          Hash1          |          Hash2          |\n";
    cout << "------------------------------------------------------------------------\n";
    cout << "|   HashFunction   | Collisions |  Avg Hits  | Collisions |  Avg Hits  |\n";
    cout << "------------------------------------------------------------------------\n";
    for (size_t i = 0; i < tables.size(); i+=2)
    {
        cout << "| " << setw(16) << tables[i].first << " | "
             << setw(10) << tables[i].second->getCollisionCount() << " | "
             << setw(10) << fixed << setprecision(3) 
             << static_cast<double>(tables[i].second->getHitCount()) / searchCount << " | "
             << setw(10) << tables[i+1].second->getCollisionCount() << " | "
             << setw(10) << fixed << setprecision(3) 
             << static_cast<double>(tables[i+1].second->getHitCount()) / searchCount << " | " << endl;
    }
    cout << "------------------------------------------------------------------------\n";

    for (auto& table : tables) delete table.second;
    tables.clear();

    return 0;
}