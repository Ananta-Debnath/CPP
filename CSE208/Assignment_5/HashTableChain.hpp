#include <iostream>
#include <forward_list>
#include <vector>
#include <cmath>
#include "HashTableADT.hpp"

template <typename Key, typename Value>
class HashTableChain : public HashTableADT<Key, Value>
{
private:
    // Static configuration variables for easy modification
    static const int INITIAL_SIZE = 13;
    const double LOAD_FACTOR_INSERTION_CUTOFF = 0.5;
    const double LOAD_FACTOR_DELETION_CUTOFF = 0.25;
    
    std::forward_list<std::pair<Key, Value>>* list;
    std::vector<int> length;
    int lengthIdx;
    int count;
    int hashFunction;
    int insertionsSinceRehash;
    int deletionsSinceRehash;
    int lastRehashCount;
    int collisionCount;
    int hitCount;

    bool isPrime(long long x) const {
        if (x < 2) return false;
        if (x == 2 || x == 3) return true;
        if (x % 2 == 0 || x % 3 == 0) return false;
        for (long long i = 5; i * i <= x; i += 6) {
            if (x % i == 0 || x % (i + 2) == 0) return false;
        }
        return true;
    }

    // Returns the smallest prime greater than n
    long long nextPrime(long long n) const
    {
        long long candidate = n + 1;
        while (!isPrime(candidate)) ++candidate;
        return candidate;
    }

    int hash1(int k) const {
        return static_cast<int>(k % length[lengthIdx]);
    }

    int hash2(int k) const {
        const double A = 0.6180339887; // (sqrt(5) - 1) / 2
        double f = fmod(k * A, 1.0);

        return static_cast<int>(floor(length[lengthIdx] * f));
    }

    int hash(const Key& k) const override
    {
        std::hash<Key> hasher;
        int key = std::abs(static_cast<int>(hasher(k)));

        if (hashFunction == 1) return hash1(key);
        else return hash2(key);
    }

    void rehash(int oldLength) override
    {
        int newLength = length[lengthIdx];
        // std::cout << "Rehashing to new size: " << newLength << std::endl;

        auto newList = new std::forward_list<std::pair<Key, Value>>[newLength];

        for (int i = 0; i < oldLength; i++) {
            for (const auto& pair : list[i]) {
                int idx = hash(pair.first);
                newList[idx].emplace_front(pair);
            }
        }
        // std::cout << "Rehashing complete. New size: " << newLength << std::endl;

        delete[] list;
        list = newList;
        insertionsSinceRehash = 0;
        deletionsSinceRehash = 0;
        lastRehashCount = count;
    }

public:
    HashTableChain(int hashFunction = 1, int initialSize = INITIAL_SIZE)
    {
        length.push_back(initialSize);
        lengthIdx = 0;
        count = 0;
        this->hashFunction = hashFunction;
        insertionsSinceRehash = 0;
        deletionsSinceRehash = 0;
        lastRehashCount = count;
        collisionCount = 0;
        hitCount = 0;
        list = new std::forward_list<std::pair<Key, Value>>[length[lengthIdx]];
    }

    HashTableChain(const HashTableChain& h)
    {
        length = h.length;
        lengthIdx = h.lengthIdx;
        count = h.count;
        hashFunction = h.hashFunction;
        insertionsSinceRehash = h.insertionsSinceRehash;
        deletionsSinceRehash = h.deletionsSinceRehash;
        lastRehashCount = h.lastRehashCount;
        collisionCount = h.collisionCount;
        hitCount = h.hitCount;
        
        list = new std::forward_list<std::pair<Key, Value>>[length[lengthIdx]];
        for (int i = 0; i < length[lengthIdx]; i++) {
            list[i] = h.list[i];
        }
    }

    const HashTableChain& operator=(const HashTableChain& h)
    {
        if (this == &h) return *this;

        delete[] list;

        length = h.length;
        lengthIdx = h.lengthIdx;
        count = h.count;
        hashFunction = h.hashFunction;
        insertionsSinceRehash = h.insertionsSinceRehash;
        deletionsSinceRehash = h.deletionsSinceRehash;
        lastRehashCount = h.lastRehashCount;
        collisionCount = h.collisionCount;
        hitCount = h.hitCount;
        
        list = new std::forward_list<std::pair<Key, Value>>[length[lengthIdx]];
        for (int i = 0; i < length[lengthIdx]; i++) {
            list[i] = h.list[i];
        }

        return *this;
    }

    ~HashTableChain()
    {
        delete[] list;
    }

    int size() const override
    {
        return count;
    }

    int getCollisionCount() const override
    {
        return collisionCount;
    }

    int getHitCount() const override
    {
        return hitCount;
    }

    void insert(const Key& k, const Value& v) override
    {
        // std::cout << "Inserting key: " << k << ", value: " << v << std::endl;
        int idx = hash(k);
        for (auto& pair : list[idx]) {
            if (pair.first == k) {
                pair.second = v;
                return;
            }
            collisionCount++;
        }
        list[idx].emplace_front(k, v);
        count++;
        insertionsSinceRehash++;
        // std::cout << "Inserted at index: " << idx << ", current count: " << count << std::endl;

        if ((static_cast<double>(count) / length[lengthIdx]) > LOAD_FACTOR_INSERTION_CUTOFF && insertionsSinceRehash > (lastRehashCount / 2)) {
            lengthIdx++;
            if (lengthIdx >= length.size()) {
                length.push_back(nextPrime(length.back() * 2));
            }
            rehash(length[lengthIdx-1]);
        }
    }

    void remove(const Key& k) override
    {
        int idx = hash(k);
        auto& chain = list[idx];
        auto prev = chain.before_begin();
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == k) {
                chain.erase_after(prev);
                count--;
                deletionsSinceRehash++;
                break;
            }
            ++prev;
        }

        if ((static_cast<double>(count) / length[lengthIdx]) < LOAD_FACTOR_DELETION_CUTOFF && deletionsSinceRehash > (lastRehashCount / 2)) {
            if (lengthIdx > 0)
            {
                rehash(length[lengthIdx--]);
            }
        }
    }

    void clear() override
    {
        delete[] list;

        lengthIdx = 0;
        count = 0;
        insertionsSinceRehash = 0;
        deletionsSinceRehash = 0;
        lastRehashCount = count;
        collisionCount = 0;
        hitCount = 0;
        list = new std::forward_list<std::pair<Key, Value>>[length[lengthIdx]];
    }

    const Value* find(const Key& k) override
    {
        int idx = hash(k);
        for (const auto& pair : list[idx]) {
            if (pair.first == k) {
                return &pair.second;
            }
            hitCount++;
        }
        return nullptr;
    }
};