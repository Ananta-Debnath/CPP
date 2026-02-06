template <typename Key, typename Value>
class HashTableADT
{
protected:
    virtual int hash(const Key& k) const = 0;

    virtual void rehash(int newSize) = 0;

public:

    virtual ~HashTableADT() {}

    virtual int size() const = 0;

    virtual int getCollisionCount() const = 0;

    virtual int getHitCount() const = 0;

    virtual void insert(const Key& k, const Value& v) = 0;

    virtual void remove(const Key& k) = 0;

    virtual void clear() = 0;

    virtual const Value* find(const Key& k) = 0; // non-const due to hit count
};