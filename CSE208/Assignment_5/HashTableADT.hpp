#ifndef HASHTABLEADT_HPP
#define HASHTABLEADT_HPP
#include <cstdint>
#include <utility>

template <typename Key, typename Value>
class HashTableADT
{
public:
    static constexpr uint64_t FNV_PRIME = 1099511628211ULL;
    static constexpr uint64_t FNV_OFFSET = 14695981039346656037ULL;
    static constexpr uint64_t P_BASE = 313;

    uint64_t hash_polynomial(const void* ptr, size_t len) const
    {
        const unsigned char* data = static_cast<const unsigned char*>(ptr);
        uint64_t hash = 0;
        
        // Horner's Method: hash = (hash * P + char)
        // This calculates the polynomial from left to right efficiently.
        for (size_t i = 0; i < len; ++i) {
            hash = hash * P_BASE + data[i];
        }

        return hash;
    }

    uint64_t hash_djb2(const void* ptr, size_t len) const
    {
        uint64_t hash = 5381;
        const unsigned char* p = static_cast<const unsigned char*>(ptr);

        for (size_t i = 0; i < len; ++i)
        {
            hash = ((hash << 5) + hash) + p[i]; // hash * 33 + c
        }
        return hash;
    }

    uint64_t fnv1a(const void* start_ptr, size_t length_in_bytes) const
    {
        uint64_t hash = FNV_OFFSET;
        const unsigned char* p = static_cast<const unsigned char*>(start_ptr);

        for (size_t i = 0; i < length_in_bytes; ++i) {
            hash ^= p[i];
            hash *= FNV_PRIME;
        }
        return hash;
    }
    
    std::pair<const void*, size_t> get_memory_view(const Key& key) const
    {
        // CASE A: Standard Contiguous Containers (std::vector, std::string)
        if constexpr (std::is_same_v<Key, std::string>) {
            return std::make_pair(key.data(), key.size());
        }
        
        // CASE B: C-Style Strings (const char*)
        else if constexpr (std::is_same_v<Key, const char*> || std::is_same_v<Key, char*>) {
            if (!key) return std::make_pair(nullptr, 0);
            size_t len = 0;
            while(key[len] != '\0') len++; 
            return std::make_pair(key, len);
        }

        // CASE C: std::vector of simple types
        else if constexpr (std::is_same_v<Key, std::vector<typename Key::value_type>> && 
                           std::is_trivially_copyable_v<typename Key::value_type>) {
            return std::make_pair(key.data(), key.size() * sizeof(typename Key::value_type));
        }
        
        // CASE D: Everything Else
        else {
            return std::make_pair(&key, sizeof(Key));
        }
    }

    uint64_t hash1(const Key& k) const
    {
        auto [ptr, len] = get_memory_view(k);
        uint64_t hash = hash_djb2(ptr, len);

        return hash;
    }


    uint64_t hash2(const Key& k) const
    {
        auto [ptr, len] = get_memory_view(k);
        uint64_t hash = fnv1a(ptr, len);
        return hash;
    }
    virtual ~HashTableADT() {}

    virtual int size() const = 0;

    virtual int getTableSize() const = 0;

    virtual int getCollisionCount() const = 0;

    virtual int getHitCount() const = 0;

    virtual void insert(const Key& k, const Value& v) = 0;

    virtual void remove(const Key& k) = 0;

    virtual void clear() = 0;

    virtual const Value* find(const Key& k) = 0; // non-const due to hit count
};

#endif