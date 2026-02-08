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

    int hash1(int k) const
    {
        return static_cast<int>(k % length[lengthIdx]);
    }

    int hash2(int k) const
    {
        const double A = 0.6180339887; // (sqrt(5) - 1) / 2
        double f = fmod(k * A, 1.0);

        return static_cast<int>(floor(length[lengthIdx] * f));
    }

    int auxHash(int k) const
    {
        return R - (k % R);
    }

    int hash(int k) const
    {
        if (hashFunction == 1) return hash1(k);
        else return hash2(k);
    }

    int customHash(const Key& k, int i) const
    {
        std::hash<Key> hasher;
        int key = std::abs(static_cast<int>(hasher(k)));

        int h1 = hash(key);
        int h2 = auxHash(key);
        return (h1 + (C1 * i * h2) + (C2 * i * i)) % length[lengthIdx];
    }

    void rehash(int oldLength)
    {
        int newLength = length[lengthIdx];
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
            while (true)
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
                    j++;
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
        R = prevPrime(length[lengthIdx]);
    }

public:
    HashTableCustomHash(int hashFunction = 1, int c1 = 1, int c2 = 3, int initialSize = INITIAL_SIZE)
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
        int i = 0;
        while (true)
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
                i++;
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
        int i = 0;
        while (true)
        {
            auto& [key, value, state] = list[idx];
            if (state == EMPTY) break; // Key not found

            else if (state == OCCUPIED && key == k)
            {
                state = DELETED;
                count--;
                deletionsSinceRehash++;
                break;
            }
            else
            {
                i++;
                idx = customHash(k, i);
            }
        }

        if ((static_cast<double>(count) / length[lengthIdx]) < LOAD_FACTOR_DELETION_CUTOFF && deletionsSinceRehash > (lastRehashCount / 2))
        {
            if (lengthIdx > 0) rehash(length[lengthIdx--]);
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
        int i = 0;
        while (true)
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
                i++;
                idx = customHash(k, i);
            }
        }
        return nullptr;
    }
};