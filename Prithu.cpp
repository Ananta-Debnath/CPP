#include <stdint.h>

static uint64_t splitmix64_state;

uint64_t splitmix64_next(void)
{
    uint64_t z;

    splitmix64_state += 0x9E3779B97F4A7C15ULL;
    z = splitmix64_state;

    z ^= (z >> 30);
    z *= 0xBF58476D1CE4E5B9ULL;

    z ^= (z >> 27);
    z *= 0x94D049BB133111EBULL;

    z ^= (z >> 31);
    return z;
}

struct SplitMix64Hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


unordered_map<long long, int, SplitMix64Hash> mp;