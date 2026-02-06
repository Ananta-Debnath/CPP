#include <iostream>
#include <forward_list>
#include <vector>

template <typename Key, typename Value>
class HashTable
{
private:
    std::forward_list<std::pair<Key, Value>>* list;
    std::vector<int> length;
    int lengthIdx;

    // Checks if x is a prime number
    bool isPrime(long long x) {
        if (x < 2) return false;
        if (x == 2 || x == 3) return true;
        if (x % 2 == 0 || x % 3 == 0) return false;
        for (long long i = 5; i * i <= x; i += 6) {
            if (x % i == 0 || x % (i + 2) == 0) return false;
        }
        return true;
    }

    // Returns the smallest prime greater than n
    long long nextPrime(long long n) {
        long long candidate = n + 1;
        while (!isPrime(candidate)) ++candidate;
        return candidate;
    }

public:
    HashTable()
    {
        length.push_back(13);
        lengthIdx = 0;
        list = new std::forward_list<int>(length[lengthIdx]);
    }

    
};