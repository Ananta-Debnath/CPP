#include <iostream>
#include <vector>


class Heap
{
private:
    int* array;
    int length;
    int capacity;

    void heapify();

public:
    Heap(int size = 2);

    Heap(vector<int>& v);

    void insert(int n);

    void deleteKey();

    int size() const;

    int getMax() const;
};

// void heapsort(vector<int>& v);