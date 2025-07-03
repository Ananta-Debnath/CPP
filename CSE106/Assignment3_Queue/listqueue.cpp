#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    // TODO: Initialize front_node and rear_node
    // TODO: Initialize current_size to 0

    rear_node = front_node = nullptr;
    current_size = 0;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method

    clear();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    // TODO: Create a new node with the given item
    // TODO: Link the new node to the rear
    // TODO: Update the rear_node
    // TODO: Increment the current size

    if (empty())
    {
        front_node = rear_node = new Node(item);
    }
    else
    {
        rear_node->next = new Node(item);
        rear_node = rear_node->next;
    }
    current_size++;
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Store the data from the front node
    // TODO: Update the front pointer to the next node
    // TODO: Update the rear pointer if the queue becomes empty
    // TODO: Delete the old front node
    // TODO: Decrement current_size
    // TODO: Return the stored data

    if (empty())
    {
        cout << "Queue is empty!" << endl;
        return -1;
    }
    else
    {
        int item = front_node->data;
        Node* toDel = front_node;
        front_node = front_node->next;

        delete toDel;
        current_size--;
        if (empty()) rear_node = front_node;

        return item;
    }
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    // TODO: Traverse the linked list and delete each node
    // TODO: Reset front and rear pointer
    // TODO: Reset current_size to 0

    while(!empty()) dequeue();
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    // TODO: Return the current size (current_size)
    
    return current_size;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the front node without removing it

    if (empty())
    {
        cout << "Queue is empty!" << endl;
        return -1;
    }
    else
    {
        return front_node->data;
    }
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the back node without removing it

    if (empty())
    {
        cout << "Queue is empty!" << endl;
        return -1;
    }
    else
    {
        return rear_node->data;
    }
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    // TODO: Return whether front is nullptr

    return front_node == nullptr;
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // TODO: Traverse the linked list from front

    string str = "<";
    if (!empty())
    {
        str += to_string(front_node->data);
        for (Node* curr = front_node->next; curr != nullptr; curr = curr->next)
        {
            str += ", " + to_string(curr->data);
        }
    }
    str += "|";
    return str;
}
