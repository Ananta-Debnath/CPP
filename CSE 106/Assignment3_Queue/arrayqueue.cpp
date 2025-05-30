#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    // TODO: Allocate memory for the array with the specified initial capacity

    front_idx = rear_idx = 0;
    capacity = initial_capacity;
    data = new int[capacity];
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array

    free(data);
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue

    if (size() >= capacity - 1) resize(capacity * 2);

    data[rear_idx] = item;
    rear_idx = (rear_idx + 1) % capacity;
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the front of the queue
    // TODO: Update front index
    // TODO: Return the dequeued element

    if (empty())
    {
        cout << "Queue is empty!" << endl;
        return -1;
    }
    else
    {
        int item = data[front_idx];
        front_idx = (front_idx + 1) % capacity;

        if (capacity >= 4 * size() && capacity / 2 >= 10) resize(capacity / 2);
        return item;
    }
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)

    front_idx = rear_idx = 0;
    resize(10);
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue

    if (rear_idx >= front_idx) return rear_idx - front_idx;

    else return capacity + rear_idx - front_idx;
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the front of the queue without removing it

    if (empty())
    {
        cout << "Queue is empty!" << endl;
        return -1;
    }
    else
    {
        return data[front_idx];
    }
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the back of the queue without removing it

    if (empty())
    {
        cout << "Queue is empty!" << endl;
        return -1;
    }
    else
    {
        return data[(rear_idx + capacity - 1) % capacity];
    }
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)

    return front_idx == rear_idx;
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|

    string str = "<";
    if (!empty())
    {
        str += to_string(data[front_idx]);
        int l = size();
        for (int i = 1; i < l; i++)
        {
            str += ", " + to_string(data[(front_idx + i) % capacity]);
        }
    }
    str += "|\n";
    return str;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    // TODO: Update front and rear indices

    int* newData = new int[new_capacity];
    int l = size();
    for (int i = 0; i < l; i++)
    {
        newData[i] = data[(front_idx + i) % capacity];
    }
    
    delete data;
    capacity = new_capacity;
    data = newData;
    front_idx = 0;
    rear_idx = l;
}

int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue

    return capacity;
}