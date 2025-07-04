#include <iostream>
#include <stdexcept>

template <typename T>
class ArrayList
{
private:
    T* array;
    int length;
    int capacity;

    void resize(int new_capacity)
    {
        if (new_capacity != capacity)
        {
            capacity = new_capacity;
            T* newArray = new T[capacity];
            for (int i = 0; i < length; i++) newArray[i] = array[i];

            delete[] array;
            array = newArray;
        }
    }

public:
    // Constructor
    ArrayList(int capacity = 2)
    {
        if (capacity < 1) throw std::runtime_error("Invalid Capacity");

        array = new T[capacity];
        length = 0;
        this->capacity = capacity;
    }

    ArrayList(const ArrayList<T>& arr)
    {
        length = arr.length;
        capacity = arr.capacity;
        array = new T[capacity];
        for (int i = 0; i < length; i++) array[i] = arr.array[i];
    }

    // Destructor
    ~ArrayList()
    {
        delete[] array;
    }

    // Assignment operator overload
    ArrayList<T>& operator=(const ArrayList<T>& arr)
    {
        if (this == &arr) return *this;

        delete[] array;
        length = arr.length;
        capacity = arr.capacity;
        array = new T[capacity];
        for (int i = 0; i < length; i++) array[i] = arr.array[i];
        return *this;
    }

    void add(T value)
    {
        length++;
        if (length * 2 > capacity) resize(capacity * 2); // increase capacity
        array[length-1] = value;
    }

    void removeAt(int idx)
    {
        if (idx >= 0 && idx < length)
        {
            length--;
            for (int i = idx; i < length; i++)
            {
                array[i] = array[i+1];
            }
            if (length * 4 < capacity && capacity > 3) resize(capacity / 2); // decrease capacity
        }
    }

    void remove(T value)
    {
        removeAt(indexOf(value));
    }

    bool contains(T value) const
    {
        for (int i = 0; i < length; i++)
        {
            if (array[i] == value) return true;
        }
        return false;
    }

    int indexOf(T value) const
    {
        for (int i = 0; i < length; i++)
        {
            if (array[i] == value) return i;
        }
        return -1;
    }
    
    T& get(int idx)
    {
        if (idx < 0 || idx >= length) throw std::runtime_error("Invalid index");

        else return array[idx];
    }

    T get(int idx) const
    {
        if (idx < 0 || idx >= length) throw std::runtime_error("Invalid index");

        else return array[idx];
    }

    T* begin() const
    {
        return &array[0];
    }

    T* end() const
    {
        return &array[length];
    }

    T* begin()
    {
        return &array[0];
    }

    T* end()
    {
        return &array[length];
    }

    int size() const
    {
        return length;
    }

    void clear()
    {
        delete[] array;
        length = 0;
        capacity = 2;
        array = new T[capacity];
    }
};