#include <iostream>
#include <vector>
#include <cmath>
#include "HashTableADT.hpp"

template <typename Key, typename Value>
class HashTableCustomHash : public HashTableADT<Key, Value>
{
private:
    enum State
    {
        EMPTY, OCCUPIED, DELETED
    };
    // Static configuration variables for easy modification
    static const int INITIAL_SIZE = 13;
    const double LOAD_FACTOR_INSERTION_CUTOFF = 0.5;
    const double LOAD_FACTOR_DELETION_CUTOFF = 0.25;
    
    std::tuple<Key, Value, State>* list;
    std::vector<int> length;
    int lengthIdx;
    int count;
    int hashFunction;
    int insertionsSinceRehash;
    int deletionsSinceRehash;
    int lastRehashCount;
    int collisionCount;
    int hitCount;

    int R;
    int C1;
    int C2;

    bool isPrime(long long x) const
    {
        if (x < 2) return false;
        if (x == 2 || x == 3) return true;
        if (x % 2 == 0 || x % 3 == 0) return false;
        for (long long i = 5; i * i <= x; i += 6) {
            if (x % i == 0 || x % (i + 2) == 0) return false;
        }
        return true;
    }

    long long nextPrime(long long n) const
    {
        long long candidate = n + 1;
        while (!isPrime(candidate)) ++candidate;
        return candidate;
    }

    long long prevPrime(long long n) const
    {
        long long candidate = n - 1;
        while (candidate > 1 && !isPrime(candidate)) --candidate;
        return candidate;
    }

    int auxHash(uint64_t k) const
    {
        return R - (k % R);
    }

    uint64_t hash(const Key& k) const
    {
        if (hashFunction == 1) return this->hash1(k);
        else return this->hash2(k);
    }

    int customHash(const Key& k, int i) const
    {
        uint64_t h1 = hash(k);
        int h2 = auxHash(h1);

        h1 = h1 % length[lengthIdx];
        return (h1 + (C1 * i * h2) + (C2 * i * i)) % length[lengthIdx];
    }

    void rehash(int oldLength)
    {
        int newLength = length[lengthIdx];
        R = prevPrime(length[lengthIdx]);
        // std::cout << "Rehashing to new size: " << newLength << std::endl;

        auto newList = new std::tuple<Key, Value, State>[newLength];
        for (int i = 0; i < newLength; i++)
        {
            newList[i] = std::make_tuple(Key(), Value(), EMPTY);
        }

        for (int i = 0; i < oldLength; i++)
        {
            auto& [k, v, s] = list[i];
            if (s != OCCUPIED) continue;

            int idx = customHash(k, 0);
            int j = 0;
            for (j = 1; j < length[lengthIdx]; j++)
            {
                auto& [key, value, state] = newList[idx];
                if (state != OCCUPIED)
                {
                    key = k;
                    value = v;
                    state = OCCUPIED;
                    break;
                }
                else
                {
                    collisionCount++;
                    idx = customHash(k, j);
                }
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
    HashTableCustomHash(int hashFunction = 1, int c1 = 1, int c2 = 3, int initialSize = INITIAL_SIZE)
    {
        initialSize = nextPrime(initialSize-1);
        length.push_back(initialSize);
        lengthIdx = 0;
        count = 0;
        this->hashFunction = hashFunction;
        insertionsSinceRehash = 0;
        deletionsSinceRehash = 0;
        lastRehashCount = count;
        collisionCount = 0;
        hitCount = 0;
        R = prevPrime(length[lengthIdx]);
        C1 = c1;
        C2 = c2;
        list = new std::tuple<Key, Value, State>[length[lengthIdx]];
        for (int i = 0; i < length[lengthIdx]; i++)
        {
            list[i] = std::make_tuple(Key(), Value(), EMPTY);
        }
    }

    HashTableCustomHash(const HashTableCustomHash& h)
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
        R = h.R;
        C1 = h.C1;
        C2 = h.C2;
        
        list = new std::tuple<Key, Value, State>[length[lengthIdx]];
        for (int i = 0; i < length[lengthIdx]; i++)
        {
            list[i] = h.list[i];
        }
    }

    const HashTableCustomHash& operator=(const HashTableCustomHash& h)
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
        R = h.R;
        C1 = h.C1;
        C2 = h.C2;
        
        list = new std::tuple<Key, Value, State>[length[lengthIdx]];
        for (int i = 0; i < length[lengthIdx]; i++)
        {
            list[i] = h.list[i];
        }

        return *this;
    }

    ~HashTableCustomHash()
    {
        delete[] list;
    }

    int size() const override
    {
        return count;
    }

    int getTableSize() const override
    {
        return length[lengthIdx];
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
        int idx = customHash(k, 0);
        int i;
        for (i = 1; i < length[lengthIdx]; i++)
        {
            auto& [key, value, state] = list[idx];
            if (state != OCCUPIED)
            {
                key = k;
                value = v;
                state = OCCUPIED;
                break;
            }
            else if (key == k)
            {
                value = v;
                break;
            }
            else
            {
                collisionCount++;
                idx = customHash(k, i);
            }
        }
        count++;
        insertionsSinceRehash++;
        // std::cout << "Inserted at index: " << idx << ", current count: " << count << std::endl;

        if ((static_cast<double>(count) / length[lengthIdx]) > LOAD_FACTOR_INSERTION_CUTOFF && insertionsSinceRehash > (lastRehashCount / 2))
        {
            lengthIdx++;
            if (lengthIdx >= length.size())
            {
                length.push_back(nextPrime(length.back() * 2));
            }
            rehash(length[lengthIdx-1]);
        }
    }

    void remove(const Key& k) override
    {
        int idx = customHash(k, 0);
        for (int i = 1; i < length[lengthIdx]; i++)
        {
            auto& [key, value, state] = list[idx];
            if (state == EMPTY)
            {
                // std::cout << "Key not found for removal: " << k << std::endl;
                break; // Key not found
            }

            else if (state == OCCUPIED && key == k)
            {
                // std::cout << "Removing key: " << k << std::endl;
                state = DELETED;
                count--;
                deletionsSinceRehash++;
                break;
            }
            else
            {
                idx = customHash(k, i);
            }
        }

        if ((static_cast<double>(count) / length[lengthIdx]) < LOAD_FACTOR_DELETION_CUTOFF && deletionsSinceRehash > (lastRehashCount / 2))
        {
            if (lengthIdx > 0)
            {
                lengthIdx--;
                rehash(length[lengthIdx + 1]);
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
        R = prevPrime(length[lengthIdx]);

        list = new std::tuple<Key, Value, State>[length[lengthIdx]];
        for (int i = 0; i < length[lengthIdx]; i++)
        {
            list[i] = std::make_tuple(Key(), Value(), EMPTY);
        }
    }

    const Value* find(const Key& k) override
    {
        int idx = customHash(k, 0);

        for (int i = 1; i < length[lengthIdx]; i++)
        {
            auto& [key, value, state] = list[idx];
            hitCount++;
            if (state == EMPTY) break; // Key not found

            else if (state == OCCUPIED && key == k)
            {
                return &value;
            }
            else
            {
                idx = customHash(k, i);
            }
        }
        return nullptr;
    }
};