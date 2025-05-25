#include <iostream>
#include <vector>
#include <random>
#include "queue.h"
using namespace std;

int randomQueue(int seed = -1)
{
    static std::mt19937 rng;
    static std::uniform_int_distribution<int> dist(1, 100);
    static bool initialized = false;

    if (seed != -1 && !initialized)
    {
        rng.seed(seed);
        initialized = true;
        return -1;
    }

    cout << "randomQueue() called" << endl;
    return (dist(rng) % 2) + 1;
}

int main()
{
    freopen("test_input_1.txt", "r", stdin); // Test Case 1
    // freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic

        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
    }

    return 0;
}