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
            int* newArray = new int[capacity];
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

    // Destructor
    ~ArrayList()
    {
        delete[] array;
    }

    // Subscript operator overload
    T& operator[](int idx)
    {
        if (idx < 0 || idx >= length) throw std::runtime_error("Invalid index");

        else return array[idx];
    }

    T& get(int idx)
    {
        if (idx < 0 || idx >= length) throw std::runtime_error("Invalid index");

        else return array[idx];
    }

    void add(T value)
    {
        length++;
        if (length * 2 > capacity) resize(capacity * 2); // increase capacity
        array[length-1] = value;
    }

    void remove(T value)
    {
        for (int i = 0; i < length; i++)
        {
            if (array[i] == value)
            {
                length--;
                for (int j = i; j < length; j++)
                {
                    array[j] = array[j+1];
                }
                break;
            }
        }

        if (length * 4 < capacity && capacity > 3) resize(capacity / 2); // decrease capacity
    }

    bool contains(T value)
    {
        for (int i = 0; i < length; i++)
        {
            if (array[i] == value) return true;
        }
        return false;
    }

    T* begin()
    {
        return &array[0];
    }

    T* end()
    {
        return &array[length];
    }

    int size()
    {
        return length;
    }

    
};