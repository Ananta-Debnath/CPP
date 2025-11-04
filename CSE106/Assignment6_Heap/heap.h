#include <vector>


class Heap
{
private:
    int* array;
    int length;
    int capacity;

    void resize(int new_capacity)
    {
        if (new_capacity != capacity)
        {
            capacity = new_capacity;
            int* newArray = new int[capacity];
            for (int i = 0; i <= length; i++) newArray[i] = array[i];

            delete[] array;
            array = newArray;
        }
    }

    int parent(int idx) const
    {
        return idx / 2;
    }

    int left(int idx) const
    {
        return 2 * idx;
    }

    int right(int idx) const
    {
        return (2 * idx) + 1;
    }

    void maxHeapify(int idx)
    {
        int l = left(idx);
        int r = right(idx);
        int largest;

        if (l <= length && array[l] > array[idx]) largest = l;

        else largest = idx;

        if (r <= length && array[r] > array[largest]) largest = r;

        if (largest != idx)
        {
            int temp = array[idx];
            array[idx] = array[largest];
            array[largest] = temp;
            maxHeapify(largest);
        }
    }

    void buildMaxHeap()
    {
        for (int i = length/2; i > 0; i++) maxHeapify(i);
    }

public:
    Heap(int size = 2)
    {
        length = 0;
        capacity = size + 1;
        array = new int[capacity];
    }

    Heap(const std::vector<int>& v)
    {
        length = 0;
        capacity = v.size() + 1;
        array = new int[capacity];

        for (int x : v) insert(x); // Heapify from length / 2 to 1
    }

    ~Heap()
    {
        delete[] array;
    }

    void insert(int key)
    {
        length++;
        if (length + 1 >= capacity) resize(capacity*2);
        array[length] = key;
        
        int idx = length;
        int par = parent(idx);
        while (par != 0 && array[par] < array[idx])
        {
            int temp = array[idx];
            array[idx] = array[par];
            array[par] = temp;
            idx = par;
            par = parent(idx);
        }
    }

    void deleteKey()
    {
        if (length > 0)
        {
            array[1] = array[length--];
            maxHeapify(1);
            if (length * 4 < capacity && capacity > 10) resize(capacity / 2);
        }
    }

    int size() const
    {
        return length;
    }

    int getMax() const
    {
        if (length > 0) return array[1];

        else throw std::runtime_error("Heap is empty");
    }
};

void heapsort(std::vector<int>& v)
{
    Heap heap(v);
    v.clear();

    while (heap.size() != 0)
    {
        v.push_back(heap.getMax());
        heap.deleteKey();
    }
}