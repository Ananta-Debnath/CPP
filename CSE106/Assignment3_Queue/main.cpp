#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" << endl;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

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
    
    int op;
    bool merged = false;
    int id, l;
    int* ts = new int[10001]; // ts -> timestamp

    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic
        cin >> op;
        cout << "Operation " << i << " ";

        switch (op)
        {
            case 1:
                cin >> id;
                cin >> ts[id];
                cout << "(Arrival " << id << " " << ts[id] << "): " << endl;
                
                if (merged)
                {
                    Q->enqueue(id);
                }
                else if (Q1->empty() && Q2->empty())
                {
                    if (randomQueue() == 1) Q1->enqueue(id);

                    else Q2->enqueue(id);
                }
                else if (Q1->empty()) Q1->enqueue(id);

                else if (Q2->empty()) Q2->enqueue(id);

                else
                {
                    if (ts[Q1->back()] < ts[Q2->back()]) Q1->enqueue(id);

                    else Q2->enqueue(id);
                }
                break;

            case 2:
                cin >> id;
                cin >> ts[id];
                cout << "(Leave " << id << " " << ts[id] << "): " << endl;

                if (merged)
                {
                    l = Q->size();
                    while (l--)
                    {
                        if (Q->front() == id) Q->dequeue();

                        else Q->enqueue(Q->dequeue());
                    }
                }
                else
                {
                    l = Q1->size();
                    while (l--)
                    {
                        if (Q1->front() == id) Q1->dequeue();

                        else Q1->enqueue(Q1->dequeue());
                    }

                    l = Q2->size();
                    while (l--)
                    {
                        if (Q2->front() == id) Q2->dequeue();

                        else Q2->enqueue(Q2->dequeue());
                    }
                }
                break;

            case 3:
                cout << "(Merge): " << endl;

                if (merged) cout << "Already merged!" << endl;

                else
                {
                    merged = true;
                    while (!Q1->empty() && !Q2->empty())
                    {
                        if (ts[Q1->front()] < ts[Q2->front()]) Q->enqueue(Q1->dequeue());

                        else Q->enqueue(Q2->dequeue());
                    }

                    while (!Q1->empty()) Q->enqueue(Q1->dequeue());

                    while (!Q2->empty()) Q->enqueue(Q2->dequeue());
                }
                break;

            case 4:
                cout << "(Split): " << endl;

                if (!merged) cout << "Queue not merged!" << endl;

                else
                {
                    merged = false;
                    while (!Q->empty())
                    {
                        Q1->enqueue(Q->dequeue());
                        if (!Q->empty()) Q2->enqueue(Q->dequeue());
                    }
                }
                break;

            case 5:
                cout << "(Departure): " << endl;

                if (merged) Q->dequeue();

                else if (Q1->empty() && Q2->empty()) cout << "Both queues are empty!" << endl;

                else if (Q1->empty()) Q2->dequeue();

                else if (Q2->empty()) Q1->dequeue();

                else if (randomQueue() == 1) Q1->dequeue();

                else Q2->dequeue();
        }


        cout << "Q1: " << Q1->toString() << endl;
        cout << "Q2: " << Q2->toString() << endl;
        cout << "Q : " << Q->toString() << endl;

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

    delete Q1;
    delete Q2;
    delete Q;
    delete ts;

    return 0;
}