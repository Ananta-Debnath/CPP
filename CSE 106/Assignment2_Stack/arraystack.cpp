#include "stack.h"
#include <iostream>

// Constructor implementation
ArrayStack::ArrayStack(int initial_capacity) {
    // TODO: Initialize data members (data, capacity, current_size)
    // TODO: Allocate memory for the array with the specified initial capacity
    data = new int[initial_capacity];
    capacity = initial_capacity;
    current_size = 0;
}

// Destructor implementation
ArrayStack::~ArrayStack() {
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Push implementation
void ArrayStack::push(int item) {
    // TODO: Check if the array is 50% full (current_size >= capacity/2)
    // TODO: If 50% full, resize the array to double its current capacity
    // TODO: Add the new element to the top of the stack and increment current_size
    current_size++;
    if (current_size >= capacity/2) resize(capacity*2);
    data[current_size-1] = item;
}

// Pop implementation
int ArrayStack::pop() {
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the top of the stack
    // TODO: If the array is less than 25% full, resize it to half its current capacity
    // TODO: Return the popped element
    if (empty())
    {
        std::cout << "Stack is empty!" << std::endl;
        return -1;
    }
    else
    {
        current_size--;
        int value = data[current_size];
        if (current_size * 4 < capacity && capacity > 10) resize(capacity / 2); // can't be less than 10
        return value;
    }
}

// Clear implementation
void ArrayStack::clear() {
    // TODO: Reset the stack to be empty (set current_size to 0)
    // TODO: No need to free memory, just logically clear the stack
    current_size = 0;
    resize(10);
}

// Size implementation
int ArrayStack::size() const {
    // TODO: Return the number of elements currently in the stack (current_size)
    return current_size;
}

// Top implementation
int ArrayStack::top() const {
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Return the element at the top of the stack without removing it
    if (empty())
    {
        std::cout << "Stack is empty!" << std::endl;
        return -1;
    }
    else return data[current_size-1];
}

// Empty implementation
bool ArrayStack::empty() const {
    // TODO: Return whether the stack is empty (current_size == 0)
    return current_size == 0;
}

// Print implementation
void ArrayStack::print() const {
    // TODO: Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
    if (empty()) std::cout << "| >" << std::endl;

    else
    {
        std::cout << "|" << data[0];
        for (int i = 1; i < current_size; i++) std::cout << ", " << data[i];
        std::cout << ">" << std::endl;
    }
}

// Resize implementation
void ArrayStack::resize(int new_capacity) {
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    if (new_capacity != capacity)
    {
        capacity = new_capacity;
        int* newData = new int[capacity];
        for (int i = 0; i < current_size; i++) newData[i] = data[i];

        delete[] data;
        data = newData;

        std::cout << "New capacity: " << capacity << std::endl;
    }
}




// Code THAT MUST BE DELETED
int main()
{
    ArrayStack* arr = new ArrayStack();
    
    arr->push(10);
    arr->push(20);
    arr->push(5);
    arr->print();
    std::cout << arr->pop() << "--" << arr->top() << std::endl;
    std::cout << "Size: " << arr->size() << std::endl;
    arr->clear();
    arr->print();
    std::cout << arr->pop() << "--" << arr->top() << std::endl;
    std::cout << "Size: " << arr->size() << std::endl;
}